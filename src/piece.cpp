#include "constants.hpp"
#include "piece.hpp"


Piece::Piece() {
    info_ = "<center><b>Test</b><center><br>test";
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
    return info;
}

bool Piece::playerPiece() const {
    return playerPiece_;
}

void Piece::showRange(bool show) {
    //qDebug() << "Showing Range" << show;
    rangePoints.clear();

    int range = stats_["range"];

    QPoint start(0, range + 1);
    QPoint startPoint = start;
    QPoint endPoint;
    QPoint dx(1, 0);
    QPoint dy(0, -1);
    bool dodx = true;
    do {
        endPoint = startPoint + (dodx ? dx : dy);

        if (onBoard(coordinates_ + startPoint) && onBoardOffset(coordinates_ + endPoint) ||
            onBoardOffset(coordinates_ + startPoint) && onBoard(coordinates_ + endPoint)) {
            rangePoints.push_back(startPoint);
            rangePoints.push_back(endPoint);
        }

        startPoint = endPoint;

        if (startPoint == QPoint(range + 1, 0)) {

            dx = QPoint(-1, 0);
            dodx = true;
            continue;
        } else if (startPoint == QPoint(0, -range)) {
            dy = QPoint(0, 1);
            dodx = false;
            continue;
        } else if (startPoint == (QPoint(-range, 0))) {
            dx = QPoint(1, 0);
            dodx = false;
            continue;
        }

        dodx = !dodx;
        if (abs(startPoint.x()) > 4 || abs(startPoint.y()) > 4) {
            break;
        }

    } while (startPoint != start);

    for (auto& point: rangePoints) {
        //qDebug() << point;
        point *= Constants::squareSize;
    }




    showRange_ = show;
    update();
}



void Piece::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    //showRange(true);
    emit hoverEnter(this);
}
void Piece::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //showRange(false);
    emit hoverLeave(this);
}


void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Clicked piece" << coordinates_.x() << coordinates_.y();
    emit clicked(this);
    QGraphicsItem::mousePressEvent(event);
}


void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem* item, QWidget* widget) {

    Entity::paint(painter, item, widget);
    //painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, image_);
    if (showRange_) {
        QPen pen(QColor(0, 200, 255));
        pen.setWidth(10);
        painter->setPen(pen);
        painter->drawLines(rangePoints);
    }
    if (false/*showStats_*/) {
        qDebug() << "painting stats";
        int oldZ = zValue();
        setZValue(4);
        qDebug() << "info" << info();
        painter->drawText(10, -Constants::squareSize, Constants::squareSize, 100, Qt::TextWordWrap, info());
        setZValue(oldZ);
    }
    if (selected_) {
        painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, mask_);
    }
}



const std::unordered_map<QString, int>& Piece::stats() const {
    return stats_;
}

void Piece::showSelected(bool value) {
    selected_ = value;
}
