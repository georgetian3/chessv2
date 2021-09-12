#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "consumable.hpp"
#include "piece.hpp"
#include "terrain.hpp"

// 实现棋盘上的方格

class Square: public QObject, public QGraphicsItem {

    Q_OBJECT

    QGraphicsPixmapItem unseenMask_{QGraphicsPixmapItem(QPixmap(":/res/img/cloud.png").scaled(Constants::squareSize, Constants::squareSize), this)};
    QGraphicsPixmapItem moveMask_{QGraphicsPixmapItem(this)};
    QPoint coordinates_;

    bool showOccupiable_ = false;
    Consumable *consumable_ = nullptr;
    Piece *piece_ = nullptr;
    Terrain *terrain_ = nullptr;

    bool playerVision_ = false;
    bool blocksVision_ = false;


    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override {};
    QRectF boundingRect() const override;
   // void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;


public:

    Square(QPoint coordinates = QPoint(0, 0), QGraphicsItem *parent = nullptr);

    QPoint coordinates() const;

    bool blocksVision() const;
    bool playerVision() const;
    void setPlayerVision(bool vision);

    bool occupiable() const;
    void showOccupiable(int show);


    Terrain* terrain() const;
    Piece* piece() const;
    Consumable* consumable() const;
    void setTerrain(Terrain *terrain);
    void setPiece(Piece *piece);
    void setConsumable(Consumable *consumable);


signals:

    void squareClicked(Square*);

};

#endif // SQUARE_HPP
