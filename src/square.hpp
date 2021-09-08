#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "gamestate.hpp"
#include "consumable.hpp"
#include "piece.hpp"
#include "terrain.hpp"
#include <iostream>
#include <QtWidgets>



enum class VisionType {unseen, seen, visible};


class Square: public QObject, public QGraphicsItem {

    Q_OBJECT

    QGraphicsPixmapItem unseenMask_ = QGraphicsPixmapItem(QPixmap(":/res/img/cloud.png").scaled(Constants::squareSize, Constants::squareSize), this);
    QGraphicsPixmapItem seenMask_ = QGraphicsPixmapItem(this);
    QGraphicsPixmapItem moveMask_ = QGraphicsPixmapItem(this);
    const QPoint coordinates_;

    bool showOccupiable_ = false;
    Consumable *consumable_ = nullptr;
    Piece *piece_ = nullptr;
    Terrain *terrain_ = nullptr;

    VisionType playerVision_ = VisionType::seen;
    VisionType enemyVision_;
    bool blocksVision_ = false;


    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override;

    QRectF boundingRect() const override {
        return QRectF(0, 0, Constants::squareSize, Constants::squareSize);
    }


public:

    Square(QPoint coordinates, QGraphicsItem *parent = nullptr);

    QPoint coordinates() const;
    VisionType playerVision() const;
    void setPlayerVision(VisionType visionType);



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
