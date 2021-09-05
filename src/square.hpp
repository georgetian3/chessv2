#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "gamestate.hpp"
#include "consumable.hpp"
#include "piece.hpp"
#include "terrain.hpp"
#include <iostream>
#include <QtWidgets>

enum class TerrainType {grass, rock, bush};
enum class PieceType {pawn, rook, knight, bishop, queen, king};

class Square: public QObject, public QGraphicsItem {

    Q_OBJECT

    QPixmap fog;
    QPixmap moveMask = QPixmap(Constants::squareSize, Constants::squareSize);
    QPixmap fogMask = QPixmap(Constants::squareSize, Constants::squareSize);
    const QPoint position_;

    bool movable_ = false;
    Consumable *consumable = nullptr;
    Piece *piece_ = nullptr;
    Terrain *terrain_ = nullptr;

    int playerVision_ = 2; // 0: never warded, 1: previously warded, 2: currently warded
    int enemyVision;


public:

    Square(QPoint position, QGraphicsItem *parent = nullptr): position_(position), QGraphicsItem(parent) {
        moveMask.fill(QColor(255, 0, 0, 100));
        fogMask.fill(QColor(0, 0, 0, 100));
        fog = QPixmap(":/res/img/placeholder.png");
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        emit squareClicked(this);
        QGraphicsItem::mousePressEvent(event);
    }

    QRectF boundingRect() const override {
        return QRectF(0, 0, Constants::squareSize, Constants::squareSize);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override {
        if (playerVision_ == 0) {
            painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, fog);
            return;
        }
        painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, terrain_->pix);
        if (piece_) {
            painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, piece_->pix);
        } else if (consumable) {
            painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, consumable->pix);
        }
        if (playerVision_ == 1) {
            painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, fogMask);
        }
        if (movable_) {
            painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, moveMask);
        }

    }



    QPoint getPos() const {
        return position_;
    }



    bool movable() const {
        return movable_;
    }

    bool setMovable(bool movable) {
        movable_ = movable;
    }

    bool movePieceTo(Square* newSquare) {
        if (newSquare->piece_) {
            return false;
        }
        newSquare->piece_ = piece_;
        piece_ = nullptr;
        return true;
    }

    int playerVision() const {
        return playerVision_;
    }
    void setPlayerVision(int value) {
        if (value < 0) {
            playerVision_ = 0;
        } else if (value > 2) {
            playerVision_ = 2;
        } else {
            playerVision_ = value;
        }
    }

    bool getPiece() const {
        return piece_;
    }

    bool occupiable() const  {
        return !static_cast<bool>(piece_) && terrain_->occupiable();
    }

    void setTerrain(TerrainType terrainType) {
        switch (terrainType) {
            case TerrainType::grass:
                terrain_ = new Grass();
                break;
            case TerrainType::rock:
                terrain_ = new Rock();
                break;
            default:
                break;
        }
    }

    void setPiece(PieceType pieceType) {

    }

signals:

    void squareClicked(Square*);

};

#endif // SQUARE_HPP
