#include "menu.hpp"
#include "QFont"

Menu::Menu(QGraphicsItem *parent): QGraphicsItem(parent) {

    setZValue(1000);

    QPoint offset(80, 50);

    selectButton_.setPos(offset);
    skipButton_.setPos(offset + QPoint(Constants::buttonSize, 0));
    attackButton_.setPos(offset + QPoint(Constants::buttonSize * 2, 0));
    spellButton_.setPos(offset + QPoint(Constants::buttonSize * 3, 0));

    textItem_ = new QGraphicsSimpleTextItem("test", this);
    textItem_->setPos(offset + QPoint(0, Constants::buttonSize));

    QFont font;
    font.setFamily("Times New Roman");
    font.setPointSize(24);
    textItem_->setFont(font);

    connect(&spellButton_,  SIGNAL(clicked()), this, SIGNAL(spellClicked()));
    connect(&attackButton_, SIGNAL(clicked()), this, SIGNAL(attackClicked()));
    connect(&selectButton_, SIGNAL(clicked()), this, SIGNAL(selectClicked()));
    connect(&skipButton_,   SIGNAL(clicked()), this, SIGNAL(skipClicked()));

}

QRectF Menu::boundingRect() const {
    return background_.boundingRect();
}

void Menu::showSpell(bool show) {
    spellButton_.setVisible(show);
}
void Menu::showAttack(bool show) {
    attackButton_.setVisible(show);
}
void Menu::showSelect(bool show) {
    selectButton_.setVisible(show);
}
void Menu::showSkip(bool show) {
    skipButton_.setVisible(show);
}
void Menu::setText(const QString& text) {
    textItem_->setText(text);
    update();
}
void Menu::appendText(const QString& text) {
    setText(textItem_->text() + text);
    update();
}
void Menu::reset() {
    showSpell(false);
    showAttack(false);
    showSelect(false);
    showSkip(false);
    setText("");
}

