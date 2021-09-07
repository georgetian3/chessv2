QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    chessv2.cpp \
    entity.cpp \
    gamestate.cpp \
    main.cpp \
    piece.cpp \
    square.cpp

HEADERS += \
    board.hpp \
    chessv2.hpp \
    constants.hpp \
    consumable.hpp \
    entity.hpp \
    gamestate.hpp \
    imagebutton.hpp \
    rangemarker.hpp \
    sidepane.hpp \
    sidepane.hpp \
    menu.hpp \
    piece.hpp \
    randomint.hpp \
    square.hpp \
    terrain.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
