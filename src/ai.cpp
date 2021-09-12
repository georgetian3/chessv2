#include "ai.hpp"
#include "randomint.hpp"

#include <cmath>

AI::AI(const std::vector<std::vector<Square*>>& squares):squares_(squares) {}

void AI::algorithm(int level) {

    // 寻找离目标方格最近的白色棋子，存到`closest`中
    Piece *closest = nullptr;
    for (int i = 0; i < Constants::boardWidth; i++) {
        for (int j = 0; j < Constants::boardHeight; j++) {
            if (squares_[i][j]->piece()) {
                Piece *piece = squares_[i][j]->piece();
                if (!piece->playerPiece()) {
                    continue;
                }
                if (!closest) {
                    closest = piece;
                    continue;
                }
                if (std::min(dist(piece->coordinates(), Constants::target1), dist(piece->coordinates(), Constants::target2)) <
                    std::min(dist(closest->coordinates(), Constants::target1), dist(closest->coordinates(), Constants::target2))) {
                    closest = piece;
                }
            }
        }
    }

    std::vector<Piece*> aiPieces;

    // 若closest在一个黑色棋子的视野范围内，则让黑色棋子攻击closest，并结束这个回合

    for (int i = 0; i < Constants::boardWidth; i++) {
        for (int j = 0; j < Constants::boardHeight; j++) {
            Piece *piece = squares_[i][j]->piece();
            if (piece && !piece->playerPiece()) {
                aiPieces.push_back(piece);
                if (piece->inRange(closest)) {
                    //qDebug() << "AI attacking" << i << j;
                    emit squareClicked(squares_[i][j]);
                    emit selectClicked();
                    emit squareClicked(squares_[closest->coordinates().x()][closest->coordinates().y()]);
                    emit attackClicked();
                    Sleep(2000);
                    emit skipClicked();
                    return;
                }
            }
        }
    }

    // 否则，任意选中一个可移动的黑色棋子...

    Piece* selectedPiece = nullptr;

    RandomInt randomPiece(0, static_cast<int>(aiPieces.size()) - 1);

    while (!selectedPiece) {
        Piece *piece = aiPieces[randomPiece.get()];
        for (const auto& move: moves_) {
            if (onBoard(piece->coordinates() + move)) {
                selectedPiece = piece;
                break;
            }
        }
    }


    emit squareClicked(squares_[selectedPiece->coordinates().x()][selectedPiece->coordinates().y()]);
    emit selectClicked();
    Sleep(1000);

    // ...并随机地移动它，直到用掉所有步骤

    while (selectedPiece->movesLeft()) {
        std::vector<QPoint> newCoords;
        for (const auto& move: moves_) {
            QPoint newCoord = selectedPiece->coordinates() + move;
            if (onBoard(newCoord) && squares_[newCoord.x()][newCoord.y()]->occupiable()) {
                newCoords.push_back(newCoord);
            }
        }
        RandomInt randomMove(0, newCoords.size() - 1);
        QPoint newCoord = newCoords[randomMove.get()];
        emit squareClicked(squares_[newCoord.x()][newCoord.y()]);
        Sleep(1000);
    }

    emit skipClicked();

}

void AI::run(int level) {

    QThread* runThread = QThread::create(&AI::algorithm, this, level);
    runThread->start();


}
