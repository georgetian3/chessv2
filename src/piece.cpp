#include "constants.hpp"
#include "piece.hpp"


Piece::Piece() {
    setAcceptHoverEvents(true);
    setZValue(1);
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
    info += QString::number(coordinates_.x()) + " "  + QString::number(coordinates_.y());
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
    qDebug() << "Clicked piece" << coordinates_.x() << coordinates_.y();
    emit clicked(this);
    QGraphicsItem::mousePressEvent(event);
}





const std::unordered_map<QString, int>& Piece::stats() const {
    return stats_;
}

void Piece::showSelected(bool value) {
    selected_ = value;
}

void Piece::setStat(const QString& stat, int amount) {
    auto it = stats_.find(stat);
    if (it != stats_.end()) {
        (*it).second += amount;
        if ((*it).second < 0) {
            (*it).second = 0;
        }
    }
}
