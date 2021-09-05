
#include "chessv2.hpp"
#include "test.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ChessV2 chessv2;
    chessv2.show();

    //Test test;
    //test.show();
    return a.exec();
}
