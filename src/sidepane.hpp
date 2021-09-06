#ifndef SIDEPANE_HPP
#define SIDEPANE_HPP


#include "piece.hpp"
#include <QtWidgets>

class SidePane: public QGraphicsScene {

    Q_OBJECT

    QGraphicsRectItem *rect;
    QGraphicsTextItem *text;
    QGraphicsPixmapItem bg;

public:
    SidePane() {
        QPixmap bg1 = QPixmap(150, 300);
        bg1.fill(QColor(255, 255, 0));
        QGraphicsPixmapItem *pix = addPixmap(bg1);


        text = new QGraphicsTextItem("");
        addItem(text);


    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        qDebug() << "Clicked sidepane";
    }

public slots:

    void setText(const QString& newText) {
        text->setPlainText(newText);
    }


    void onPieceClick(Piece* piece) {
        text->setHtml(piece->info());
    }

};

#endif // SIDEPANE_HPP
