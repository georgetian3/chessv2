#include "chessv2.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ChessV2 chessv2;
    chessv2.show();
    return a.exec();
}
