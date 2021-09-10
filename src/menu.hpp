#ifndef MENU_HPP
#define MENU_HPP

#include "constants.hpp"
#include "imagebutton.hpp"
#include <QtWidgets>


class Menu: public QObject, public QGraphicsRectItem {

    Q_OBJECT

    QGraphicsTextItem *textItem;
    ImageButton attackButton_;
    ImageButton spellButton_;
    ImageButton selectButton_;
    ImageButton skipButton_;
    QGraphicsPixmapItem *bg;

public:

    Menu(QGraphicsRectItem *parent = nullptr):
        attackButton_(ImageButton(":/res/img/attack.png", this)),
        spellButton_(ImageButton(":/res/img/ability.png", this)),
        selectButton_(ImageButton(":/res/img/select.png", this)),
        skipButton_(ImageButton(":/res/img/skip.png", this)),
        QGraphicsRectItem(parent) {

        setZValue(1000);

        bg = new QGraphicsPixmapItem(QPixmap(":/res/img/scroll.png").scaled(400, 600), this);



        //spellButton_.hide();
        //attackButton_.hide();
        //selectButton_.hide();
        //skipButton_.hide();

        QPoint offset(80, 50);

        selectButton_.setPos(offset);
        skipButton_.setPos(offset + QPoint(Constants::buttonSize, 0));
        attackButton_.setPos(offset + QPoint(Constants::buttonSize * 2, 0));
        spellButton_.setPos(offset + QPoint(Constants::buttonSize * 3, 0));



        connect(&spellButton_,  SIGNAL(clicked()), this, SIGNAL(spellClicked()));
        connect(&attackButton_, SIGNAL(clicked()), this, SIGNAL(attackClicked()));
        connect(&selectButton_, SIGNAL(clicked()), this, SIGNAL(selectClicked()));
        connect(&skipButton_,   SIGNAL(clicked()), this, SIGNAL(skipClicked()));

        textItem = new QGraphicsTextItem("test", this);
        textItem->setPos(offset + QPoint(0, Constants::buttonSize));

        QFont font;
        font.setFamily("Times New Roman");
        font.setPointSize(24);

        textItem->setFont(font);

    }



public slots:

    void showSpell(bool show) {
        spellButton_.setEnabled(show);
        //spellButton_.setVisible(show);
    }
    void showAttack(bool show) {
        attackButton_.setEnabled(show);
        //attackButton_.setVisible(show);
    }
    void showSelect(bool show) {
        selectButton_.setEnabled(show);
        //selectButton_.setVisible(show);
    }
    void showSkip(bool show) {
        skipButton_.setEnabled(show);
        //skipButton_.setVisible(show);
    }
    void setText(const QString& text) {
        textItem->setPlainText(text);

    }
    void appendText(const QString& text) {
        textItem->setPlainText(textItem->toPlainText() + text);
    }
    void reset() {
        showSpell(false);
        showAttack(false);
        showSelect(false);
        showSkip(false);
        setText("");
    }

signals:

    void spellClicked();
    void attackClicked();
    void selectClicked();
    void skipClicked();

};

#endif // MENU_HPP
