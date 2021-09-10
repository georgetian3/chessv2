#include "ai.hpp"
#include "board.hpp"

#include <cmath>

AI::AI(const std::vector<std::vector<Square*>>& squares):squares_(squares) {

}

void AI::algorithm(int level) {
    QPoint target1(Constants::boardWidth / 2 - 1, 0);
    QPoint target2(Constants::boardWidth / 2, 0);

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
                if (std::min(dist(piece->coordinates(), target1), dist(piece->coordinates(), target2)) <
                    std::min(dist(closest->coordinates(), target1), dist(closest->coordinates(), target2))) {
                    closest = piece;
                }
            }
        }
    }
    qDebug() << "closest" << closest->coordinates();

    std::vector<Piece*> aiPieces;

    //Piece *moveCloser = nullptr;
    //int deltaX, deltaY;
    for (int i = 0; i < Constants::boardWidth; i++) {
        for (int j = 0; j < Constants::boardHeight; j++) {
            Piece *piece = squares_[i][j]->piece();
            if (piece && !piece->playerPiece()) {
                aiPieces.push_back(piece);
                if (piece->inRange(closest)) {
                    qDebug() << "AI attacking" << i << j;
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

    qDebug() << "Finding movable piece";

    Piece* selectedPiece = nullptr;

    RandomInt randomPiece(0, aiPieces.size() - 1);

    while (!selectedPiece) {
        Piece *piece = aiPieces[randomPiece.get()];
        for (const auto& move: moves) {
            if (onBoard(piece->coordinates() + move)) {
                selectedPiece = piece;
                break;
            }
        }
    }


    emit squareClicked(squares_[selectedPiece->coordinates().x()][selectedPiece->coordinates().y()]);
    emit selectClicked();
    Sleep(1000);

    qDebug() << "Moving piece";

    while (selectedPiece->movesLeft()) {
        std::vector<QPoint> newCoords;
        for (const auto& move: moves) {
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

    qDebug() << "AI SKIPPING";
    emit skipClicked();
    qDebug() << "AI FINISHED -----------------------------";

}

void AI::run(int level) {
    qDebug() << "AI RUNNING ------------------------------------";
    QThread* runThread = QThread::create(&AI::algorithm, this, level);
    runThread->start();


}
