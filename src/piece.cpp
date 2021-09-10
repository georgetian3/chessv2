#include "constants.hpp"
#include "piece.hpp"


Piece::Piece() {
    setAcceptHoverEvents(true);
    setZValue(1);
    flashTimer.setInterval(200);
    connect(&flashTimer, SIGNAL(timeout()), this, SLOT(flash()));
}
const Ability& Piece::spell() const {
    return spell_;
}
void Piece::moved() {
    if (movesLeft_ > 0) {
        --movesLeft_;
    }
}
void Piece::skipped() {
    movesLeft_ = getStat("speed");
    usedAttack_ = false;
}
int Piece::movesLeft() const {
    return movesLeft_;
}
QString Piece::capitalizeFirst(QString text) const {
    text[0] = text[0].toUpper();
    return text;
}

bool Piece::inRange(Piece* piece) {
    if (!piece) {
        return false;
    }
    if ((coordinates_ - piece->coordinates_).manhattanLength() <= getStat("range")) {
        return true;
    }
    return false;
}

int Piece::getStat(const QString& stat) const {
    auto it = stats_.find(stat);
    if (it != stats_.end()) {
        return it->second;
    } else {
        return -1;
    }
}

QString Piece::info() const {
    QString info;
    info = name_ + '\n';
    for (const auto& [stat, value]: stats_) {
        info += capitalizeFirst(stat) + ": " + QString::number(value) + "\n";
    }
    info += "Moves left: " + QString::number(movesLeft_) + '\n';
    //info += QString::number(coordinates_.x()) + " "  + QString::number(coordinates_.y());
    return info;
}

bool Piece::playerPiece() const {
    return playerPiece_;
}






void Piece::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    //qDebug() << "hover enter";
    emit hoverEnter(this);
    QGraphicsItem::hoverEnterEvent(event);
}
void Piece::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    emit hoverLeave(this);
    QGraphicsItem::hoverLeaveEvent(event);
}


void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug() << "Clicked piece" << coordinates_.x() << coordinates_.y();
    emit clicked(this);
    QGraphicsItem::mousePressEvent(event);
}





const std::unordered_map<QString, int>& Piece::stats() const {
    return stats_;
}

void Piece::flash() {
    static int counter = 0;
    setVisible(!isVisible());
    counter++;
    if (counter == 5) {
        flashTimer.stop();
        counter = 0;
        show();
    }

}

void Piece::setStat(const QString& stat, int amount) {
    auto it = stats_.find(stat);
    if (it != stats_.end()) {
        (*it).second += amount;
        if ((*it).second < 0) {
            (*it).second = 0;
        }
        flashTimer.start();
    }
}

void Piece::consume(Consumable *consumable) {
    qDebug() << "Consuming" << consumable->stat() << consumable->amount();
    setStat(consumable->stat(), consumable->amount());
}

void Piece::useAttack(Piece *piece) {
    if (canUseAttack()) {
        piece->setStat("health", -stats_[QString("damage")]);
        usedAttack_ = true;
    }
}

bool Piece::canUseAttack() const {
    return !usedAttack_;
}

void Piece::useSpell(Piece *piece) {
    if (canUseSpell()) {
        spell_.perform(piece);
        setStat("energy", -spell_.cost());
    }
}

bool Piece::canUseSpell() const {
    return !usedSpell_ && spell_.cost() <= getStat("energy");
}
