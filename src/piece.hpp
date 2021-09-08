#ifndef PIECE_HPP
#define PIECE_HPP

#include "entity.hpp"
#include "imagebutton.hpp"
#include <QtWidgets>
#include <unordered_map>

enum class PieceType {pawn, rook, knight, bishop, queen, king, minion};

class Piece: public Entity {

    Q_OBJECT

    QString capitalizeFirst(QString text) const {
        text[0] = text[0].toUpper();
        return text;
    }



protected:

    bool selected_ = false;

    int z_ = 1;
    QString spellDescription_;
    std::unordered_map<QString, int> stats_ = {
        {"health", 100},
        {"damage", 20},
        {"energy", 100},
        {"speed", 5},
        {"range", 3},
    };




    bool playerPiece_ = true;

/*
    void showActions() {

        if (!square || !square->piece()) {
            qDebug() << "Removing buttons";
            removeItem(attackButton);
            removeItem(abilityButton);
            return;
        }
        qDebug() << "Adding buttons";
        qDebug() << square->pos();
        attackButton->setPos((square->pos() + QPoint(0, 1)) * Constants::squareSize -
                            QPointF(attackButton->boundingRect().width() / 2, attackButton->boundingRect().height() / 2));
        abilityButton->setPos((square->pos() + QPoint(1, 1)) * Constants::squareSize -
                             QPointF(abilityButton->boundingRect().width() / 2, abilityButton->boundingRect().height() / 2));
        addItem(attackButton);
        addItem(abilityButton);


    }
 */

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

public:

    Piece();


    bool inRange(Piece* piece);
    QString info() const;
    bool playerPiece() const;
    int getStat(const QString& stat) const;


    const std::unordered_map<QString, int>& stats() const;

    void showSelected(bool show);

    void useAttack(Piece *piece) {
        piece->setStat("health", -1 * stats_["damage"]);
    }
    void useSpell(Piece *piece) {
        ;
    }
    void setStat(const QString& stat, int amount);

public slots:


signals:

    void hoverEnter(Piece*);
    void hoverLeave(Piece*);
    void clicked(Piece*);


};


class Pawn: public Piece {
public:
    Pawn() {
        setImage(":/res/img/pawn_w.png");
        name_ = "Pawn";
        playerPiece_ = true;
    }
};

class Rook: public Piece {
public:
    Rook() {
        setImage(":/res/img/rook_w.png");
        name_ = "Rook";
        playerPiece_ = true;
    }
};
class Knight: public Piece {
public:
    Knight() {
        setImage(":/res/img/knight_w.png");
        name_ = "Knight";
        playerPiece_ = true;
    }
};
class Bishop: public Piece {
public:
    Bishop() {
        setImage(":/res/img/bishop_w.png");
        name_ = "Bishop";
        playerPiece_ = true;
    }
};
class Queen: public Piece {
public:
    Queen() {
        setImage(":/res/img/queen_w.png");
        name_ = "Queen";
        playerPiece_ = true;
    }
};
class King: public Piece {
public:
    King() {
        setImage(":/res/img/king_w.png");
        name_ = "King";
        playerPiece_ = true;
    }

};

class Minion: public Piece {
public:
    Minion() {
        setImage(":/res/img/pawn_b.png");
        name_ = "Minion";
        playerPiece_ = false;
    }
};

inline Piece* buildPiece(PieceType pieceType) {
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

#endif // PIECE_HPP
