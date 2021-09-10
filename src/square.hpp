#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "gamestate.hpp"
#include "consumable.hpp"
#include "piece.hpp"
#include "terrain.hpp"
#include <iostream>
#include <QtWidgets>



//enum class VisionType {unseen, seen, visible};


class Square: public QObject, public QGraphicsItem {

    Q_OBJECT

    QGraphicsPixmapItem unseenMask_ = QGraphicsPixmapItem(QPixmap(":/res/img/cloud.png").scaled(Constants::squareSize, Constants::squareSize), this);
    QGraphicsPixmapItem moveMask_ = QGraphicsPixmapItem(this);
    QPoint coordinates_;

    bool showOccupiable_ = false;
    Consumable *consumable_ = nullptr;
    Piece *piece_ = nullptr;
    Terrain *terrain_ = nullptr;

    bool playerVision_ = false;
    //VisionType enemyVision_;
    bool blocksVision_ = false;


    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

    QRectF boundingRect() const override;


public:

    Square(QPoint coordinates = QPoint(0, 0), QGraphicsItem *parent = nullptr);

    QPoint coordinates() const;
    bool playerVision() const;
    void setPlayerVision(bool vision);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    bool occupiable() const;
    void showOccupiable(int show);

    bool blocksVision() const;

    void setTerrain(Terrain *terrain);
    Terrain* terrain() const;
    void setPiece(Piece *piece);
    Piece* piece() const;
    void setConsumable(Consumable *consumable);
    Consumable* consumable() const;

signals:

    void squareClicked(Square*);

};

#endif // SQUARE_HPP
