#ifndef MENU_HPP
#define MENU_HPP

#include "constants.hpp"
#include "imagebutton.hpp"
#include <QtWidgets>


class Menu: public QObject, public QGraphicsRectItem {

    Q_OBJECT

    QGraphicsTextItem *textItem;
    ImageButton attackButton_;
    ImageButton abilityButton_;
    ImageButton selectButton_;
    ImageButton skipButton_;
    QGraphicsPixmapItem *bg;

public:

    Menu(QGraphicsRectItem *parent = nullptr):
        attackButton_(ImageButton(":/res/img/attack.png", this)),
        abilityButton_(ImageButton(":/res/img/ability.png", this)),
        selectButton_(ImageButton(":/res/img/select.png", this)),
        skipButton_(ImageButton(":/res/img/skip.png", this)),
        QGraphicsRectItem(parent) {

        bg = new QGraphicsPixmapItem(QPixmap(":/res/img/scroll.png").scaled(400, 600), this);



        //abilityButton_.hide();
        //attackButton_.hide();
        //selectButton_.hide();
        //skipButton_.hide();

        QPoint offset(50, 50);

        selectButton_.setPos(offset);
        skipButton_.setPos(offset + QPoint(Constants::buttonSize, 0));
        attackButton_.setPos(offset + QPoint(Constants::buttonSize * 2, 0));
        abilityButton_.setPos(offset + QPoint(Constants::buttonSize * 3, 0));



        connect(&abilityButton_, SIGNAL(clicked()), this, SIGNAL(abilityClicked()));
        connect(&attackButton_,  SIGNAL(clicked()), this, SIGNAL(attackClicked()));
        connect(&selectButton_,  SIGNAL(clicked()), this, SIGNAL(selectClicked()));
        connect(&skipButton_,    SIGNAL(clicked()), this, SIGNAL(skipClicked()));

        textItem = new QGraphicsTextItem("test", this);
        textItem->setPos(offset + QPoint(0, Constants::buttonSize));
        setZValue(10);
    }



public slots:

    void showAbility(bool show) {
        abilityButton_.setEnabled(show);
        //abilityButton_.setVisible(show);
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
    void reset() {
        showAbility(false);
        showAttack(false);
        showSelect(false);
        showSkip(false);
        setText("");
    }


signals:

    void abilityClicked();
    void attackClicked();
    void selectClicked();
    void skipClicked();

};

#endif // MENU_HPP
