#ifndef TEST_HPP
#define TEST_HPP

#include "chessv2.hpp"

#include <QtWidgets>

class Test: public QWidget {
    ChessV2 *chessV2 = nullptr;

public:
    Test() {

        setGeometry(0, 0, 500, 500);


        chessV2 = new ChessV2(this);
        chessV2->setGeometry(0, 0, 500, 500);
        QLabel *label = new QLabel("test", chessV2);


    }
};

#endif // TEST_HPP
