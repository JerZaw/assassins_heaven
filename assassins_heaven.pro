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
        fighting_game.cpp \
        game_jumping.cpp \
        highscores.cpp \
        main.cpp \
        menu.cpp \
        mind_game.cpp \
        rules.cpp

HEADERS += \
    Chronometer.hpp \
    animatedsprite.h \
    arrow.h \
    countdown.h \
    fighting_game_elements.h \
    fightinggameanimatedsprite.h \
    jumping_game_elements.h \
    mind_game_elements.h \
    mindgameanimatedsprite.h \
    movingplatform.h \
    platform.h \
    platformwithequation.h \
    scoretable.h \
    smallelementcoin.h \
    summary.h \
    targetplatform.h \
    taskelement.h \
    timedmovingplatform.h \
    timedplatform.h

