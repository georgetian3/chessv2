#ifndef MENU_HPP
#define MENU_HPP

#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class Button: public QPushButton {

public:

    Button(QWidget *parent = nullptr): QPushButton(parent) {
        setMaximumWidth(200);
    }
    Button(const QString &text, QWidget *parent = nullptr): QPushButton(text, parent) {
        setMaximumWidth(200);
    }
};

class Menu: public QWidget {

    QSpacerItem *fill = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    QCheckBox *music = nullptr;
    QCheckBox *sound = nullptr;

    Button *newGame = nullptr;
    Button *import_ = nullptr;
    Button *export_ = nullptr;

    QVBoxLayout *vBox = nullptr;


public:
    Menu(QWidget *parent = nullptr): QWidget(parent) {
        QPalette palette;
        palette.setColor(QPalette::Background, QColor(0, 0, 0, 100));
        setAutoFillBackground(true);
        setPalette(palette);
        music = new QCheckBox("Music", this);
        sound = new QCheckBox("Sound", this);
        newGame = new Button("New Game", this);
        import_ = new Button("Import", this);
        export_ = new Button("Export", this);
        vBox = new QVBoxLayout(this);
        auto vSpace = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        vBox->addSpacerItem(vSpace);
        vBox->addWidget(music);
        vBox->addWidget(sound);
        vBox->addWidget(newGame);
        vBox->addWidget(import_);
        vBox->addWidget(export_);
        vBox->addSpacerItem(vSpace);

    }
};

#endif // MENU_HPP
