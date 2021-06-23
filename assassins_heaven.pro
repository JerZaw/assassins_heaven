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
        assetsmanager.cpp \
        fighting_game.cpp \
        game_jumping.cpp \
        highscores.cpp \
        main.cpp \
        menu.cpp \
        mind_game.cpp \
        rules.cpp

HEADERS += \
    Boost.h \
    Chronometer.hpp \
    Highscores.h \
    Rules.h \
    Shop.h \
    animatedsprite.h \
    arrow.h \
    assetsmanager.h \
    countdown.h \
    fighting_game_elements.h \
    fightinggameanimatedsprite.h \
    gameapps.h \
    jumping_game_elements.h \
    jumpingscene.h \
    mind_game_elements.h \
    mindgameanimatedsprite.h \
    movingbackground.h \
    movingplatform.h \
    platform.h \
    platformwithequation.h \
    read_textures.h \
    scoresavingelement.h \
    scoretable.h \
    smallelementcoin.h \
    stationarybackground.h \
    summary.h \
    target.h \
    taskelement.h \
    timedmovingplatform.h \
    timedplatform.h

