TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}
SOURCES += \
        game_jumping.cpp \
        highscores.cpp \
        main.cpp \
        menu.cpp \
        rules.cpp

HEADERS += \
    Chronometer.hpp \
    animatedsprite.h \
    game_elements.h \
    movingplatform.h \
    platform.h \
    scoretable.h \
    timedmovingplatform.h \
    timedplatform.h

