QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ability.cpp \
    ai.cpp \
    board.cpp \
    chessv2.cpp \
    consumable.cpp \
    entity.cpp \
    imagebutton.cpp \
    main.cpp \
    menu.cpp \
    piece.cpp \
    randomint.cpp \
    square.cpp \
    terrain.cpp

HEADERS += \
    ability.hpp \
    ai.hpp \
    board.hpp \
    chessv2.hpp \
    constants.hpp \
    consumable.hpp \
    entity.hpp \
    imagebutton.hpp \
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
