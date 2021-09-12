#include "constants.hpp"
#include "piece.hpp"

Piece::Piece() {
    //setAcceptHoverEvents(true);
    setZValue(1);
    flashTimer_.setInterval(200);
    connect(&flashTimer_, SIGNAL(timeout()), this, SLOT(flash()));
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
    movesLeft_ = stat("speed");
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
    if ((coordinates_ - piece->coordinates_).manhattanLength() <= stat("range")) {
        return true;
    }
    return false;
}

int Piece::stat(const QString& stat) const {
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




/*

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

*/



void Piece::flash() {
    static int counter = 0;
    setVisible(!isVisible());
    counter++;
    if (counter == 5) {
        flashTimer_.stop();
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
        flashTimer_.start();
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
    return spell_.cost() <= stat("energy");
}

Pawn::Pawn() {
    setImage(":/res/img/pawn_w.png");
    name_ = "Pawn";
    playerPiece_ = true;
    stats_ = {
        {"health", 10},
        {"damage", 5},
        {"energy", 100},
        {"speed", 5},
        {"range", 5},
    };
    spell_.setAmount(-1);
    spell_.setStat("range");
    spell_.setTarget(TargetType::enemy);
    spell_.setCost(50);
    movesLeft_ = stat("speed");
}

Rook::Rook() {
    setImage(":/res/img/rook_w.png");
    name_ = "Rook";
    playerPiece_ = true;
    stats_ = {
        {"health", 50},
        {"damage", 20},
        {"energy", 100},
        {"speed", 2},
        {"range", 3},
    };
    spell_.setAmount(-5);
    spell_.setStat("damage");
    spell_.setTarget(TargetType::enemy);
    spell_.setCost(50);
    movesLeft_ = stat("speed");
}

Knight::Knight() {
    setImage(":/res/img/knight_w.png");
    name_ = "Knight";
    playerPiece_ = true;
    stats_ = {
        {"health", 20},
        {"damage", 5},
        {"energy", 100},
        {"speed", 5},
        {"range", 3},
    };
    spell_.setAmount(-1);
    spell_.setStat("speed");
    spell_.setTarget(TargetType::enemy);
    spell_.setCost(50);
    movesLeft_ = stat("speed");
}

Bishop::Bishop() {
    setImage(":/res/img/bishop_w.png");
    name_ = "Bishop";
    playerPiece_ = true;
    stats_ = {
        {"health", 100},
        {"damage", 5},
        {"energy", 100},
        {"speed", 3},
        {"range", 3},
    };
    spell_.setAmount(10);
    spell_.setStat("health");
    spell_.setTarget(TargetType::ally);
    spell_.setCost(50);
    movesLeft_ = stat("speed");
}

Queen::Queen() {
    setImage(":/res/img/queen_w.png");
    name_ = "Queen";
    playerPiece_ = true;
    stats_ = {
        {"health", 10},
        {"damage", 100},
        {"energy", 100},
        {"speed", 3},
        {"range", 5},
    };
    spell_.setAmount(1);
    spell_.setStat("range");
    spell_.setTarget(TargetType::enemy);
    spell_.setCost(50);
    movesLeft_ = stat("speed");
}

King::King() {
    setImage(":/res/img/king_w.png");
    name_ = "King";
    playerPiece_ = true;
    stats_ = {
        {"health", 5},
        {"damage", 0},
        {"energy", 0},
        {"speed", 1},
        {"range", 1},
    };
    spell_.setTarget(TargetType::none);
    movesLeft_ = stat("speed");
}


Minion::Minion() {
    setImage(":/res/img/pawn_b.png");
    name_ = "Minion";
    playerPiece_ = false;
    stats_ = {
        {"health", 20},
        {"damage", 5},
        {"energy", 100},
        {"speed", 10},
        {"range", 5},
    };
    spell_.setTarget(TargetType::none);
    movesLeft_ = stat("speed");
}


Piece* buildPiece(PieceType pieceType) {
    switch (pieceType) {
        case PieceType::pawn:
            return new Pawn();
        case PieceType::rook:
            return new Rook();
        case PieceType::knight:
            return new Knight();
        case PieceType::bishop:
            return new Bishop();
        case PieceType::queen:
            return new Queen();
        case PieceType::king:
            return new King();
        case PieceType::minion:
            return new Minion();
        default:
            qDebug() << "buildPiece unknown piecetype";
            return nullptr;
    }
}
