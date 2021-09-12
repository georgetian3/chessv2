#ifndef MENU_HPP
#define MENU_HPP

#include "constants.hpp"
#include "imagebutton.hpp"

// 菜单：显示“选择”、“跳过”、“攻击”、“技能”按钮，以及棋子的属性

class Menu: public QObject, public QGraphicsItem {

    Q_OBJECT

    QGraphicsSimpleTextItem *textItem_;
    ImageButton attackButton_{ImageButton(":/res/img/attack.png", this)};
    ImageButton spellButton_{ImageButton(":/res/img/ability.png", this)};
    ImageButton selectButton_{ImageButton(":/res/img/select.png", this)};
    ImageButton skipButton_{ImageButton(":/res/img/skip.png", this)};
    QGraphicsPixmapItem background_{QGraphicsPixmapItem(QPixmap(":/res/img/scroll.png").scaled(400, 600), this)};

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override {}
    QRectF boundingRect() const override;

public:

    Menu(QGraphicsItem *parent = nullptr);

public slots:

    void showSpell(bool show);
    void showAttack(bool show);
    void showSelect(bool show);
    void showSkip(bool show);
    void setText(const QString& text);
    void appendText(const QString& text);
    void reset();

signals:

    void spellClicked();
    void attackClicked();
    void selectClicked();
    void skipClicked();

};

#endif // MENU_HPP
