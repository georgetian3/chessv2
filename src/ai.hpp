#ifndef AI_HPP
#define AI_HPP

#include <QtWidgets>
#include "square.hpp"
#include "piece.hpp"

class Board;



class AI: public QObject {
    Q_OBJECT
    const std::vector<std::vector<Square*>>& squares_;
    const std::vector<QPoint> moves = {
        QPoint(0, 1),
        QPoint(0, -1),
        QPoint(1, 0),
        QPoint(-1, 0)
    };


public:
    AI(const std::vector<std::vector<Square*>>& squares);

public slots:

    void run(int level);
    void algorithm(int level);

signals:

    void squareClicked(Square*);
    void attackClicked();
    void spellClicked();
    void selectClicked();
    void skipClicked();

};

#endif // AI_HPP
