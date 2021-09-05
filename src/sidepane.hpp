#ifndef SIDEPANE_HPP
#define SIDEPANE_HPP

#include <QtWidgets>

class SidePane: public QGraphicsScene {

    QGraphicsRectItem *rect;
    QGraphicsTextItem *text;
public:
    SidePane() {
        rect = new QGraphicsRectItem(0, 0, 150, 150);
        addItem(rect);

        text = new QGraphicsTextItem("");
        addItem(text);
    }

public slots:

    void setText(const QString& newText) {
        text->setPlainText(newText);
    }


};

#endif // SIDEPANE_HPP
