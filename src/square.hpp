#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "gamestate.hpp"
#include "consumable.hpp"
#include "piece.hpp"
#include "terrain.hpp"
#include <iostream>
#include <QtWidgets>

enum class TerrainType {grass, rock, bush};

enum class VisionType {unseen, seen, visible};


class Square: public QObject, public QGraphicsItem {

    Q_OBJECT

    QPixmap fog = QPixmap(":/res/img/fog.png");
    QPixmap moveMask = QPixmap(Constants::squareSize, Constants::squareSize);
    QPixmap fogMask = QPixmap(Constants::squareSize, Constants::squareSize);
    const QPoint coordinates_;

    bool showOccupiable_ = false;
    Consumable *consumable = nullptr;
    Piece *piece_ = nullptr;
    Terrain *terrain_ = nullptr;

    VisionType playerVision_ = VisionType::visible;
    VisionType enemyVision_;
    bool blocksVision_ = false;


    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;


public:

    Square(QPoint coordinates, QGraphicsItem *parent = nullptr);

    QPoint coordinates() const;
    //void setCoordinates(const QPoint& coordinates);

    VisionType playerVision() const;
    void setPlayerVision(VisionType visionType);



    bool occupiable() const;
    void showOccupiable(int show);

    bool blocksVision() const;
    void updateBlocksVision();

    void setTerrain(Terrain *terrain);
    Terrain* terrain() const;
    void setPiece(Piece *piece);
    Piece* piece() const;

signals:

    void squareClicked(Square*);

};

#endif // SQUARE_HPP
