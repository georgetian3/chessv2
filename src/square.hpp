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
    const QPoint position_;

    bool highlight_ = false;
    Consumable *consumable = nullptr;
    Piece *piece_ = nullptr;
    Terrain *terrain_ = nullptr;

    VisionType playerVision_ = VisionType::visible;
    VisionType enemyVision;
    bool blocksVision_ = false;


public:

    Square(QPoint position, QGraphicsItem *parent = nullptr): position_(position), QGraphicsItem(parent) {
        moveMask.fill(QColor(255, 0, 0, 100));
        fogMask.fill(QColor(0, 0, 0, 100));
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        qDebug() << "Clicked square" << position_.x() << position_.y();
        emit squareClicked(this);
        QGraphicsItem::mousePressEvent(event);
    }

    QRectF boundingRect() const override {
        return QRectF(0, 0, Constants::squareSize, Constants::squareSize);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override {
        if (playerVision_ == VisionType::unseen) {
            painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, fog);
            return;
        }
        painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, terrain_->img());
        if (piece_) {
            painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, piece_->img());
        } else if (consumable) {
            painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, consumable->img());
        }
        if (playerVision_ == VisionType::seen) {
            painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, fogMask);
        }
        if (highlight_) {
            painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, moveMask);
        }

    }



    QPoint getPos() const {
        return position_;
    }

    void highlight(bool value) {
        highlight_ = value;
    }
    bool highlighted() const {
        return highlight_;
    }
    bool movePieceTo(Square* newSquare) {
        if (newSquare->piece_) {
            return false;
        }
        newSquare->piece_ = piece_;
        piece_ = nullptr;
        return true;
    }

    VisionType playerVision() const {
        return playerVision_;
    }
    void setPlayerVision(VisionType visionType) {
        playerVision_ = visionType;
    }

    bool inRange(Square* square) {
        if (!piece_) {
            return false;
        }
        if ((position_ - square->position_).manhattanLength() <= piece_->getStat("range")) {
            return true;
        }
        return false;
    }

    bool occupiable() const  {
        //qDebug() << "Square" << position_ << !piece_ << terrain_->occupiable();
        return !piece_ && terrain_->occupiable();
    }

    bool blocksVision() const {
        return blocksVision_;
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
        blocksVision_ |= terrain_->blocksVision();
    }
    Terrain* terrain() const {
        return terrain_;
    }
    void setPiece(PieceType pieceType) {
        switch (pieceType) {
            case PieceType::pawn:
                piece_ = new Pawn();
                break;
            case PieceType::rook:
                piece_ = new Rook();
                break;
            case PieceType::knight:
                piece_ = new Knight();
                break;
            case PieceType::bishop:
                piece_ = new Bishop();
                break;
            case PieceType::queen:
                piece_ = new Queen();
                break;
            case PieceType::king:
                piece_ = new King();
                break;
            case PieceType::minion:
                piece_ = new Minion();
                break;
            default:
                qDebug() << "Square::setPiece - unrecognized piece";
        }
        blocksVision_ |= piece_->blocksVision();

    }
    Piece* piece() const {
        return piece_;
    }

signals:

    void squareClicked(Square*);

};

#endif // SQUARE_HPP
