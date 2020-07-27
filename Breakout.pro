QMAKE_CXX=clang++

CONFIG += c++14

QT += core widgets multimedia

HEADERS += \
    ball.H \
    ballset.H \
    brick.H \
    brickset.H \
    gamemain.H \
    global.H \
    levelmaker.H \
    paddle.H \
    particlesystem.H \
    player.H \
    powerup.H \
    random.H \
    spritesheet.H \
    statemachine.H \
    singleton.H \
    states.H \
    audio.H \
    font.H \
    util.H

DISTFILES += \
    README.md

SOURCES += \
    ball.C \
    ballset.C \
    brick.C \
    brickset.C \
    gamemain.C \
    global.C \
    levelmaker.C \
    main.C \
    paddle.C \
    particlesystem.C \
    player.C \
    powerup.C \
    random.C \
    spritesheet.C \
    states.C \
    audio.C \
    font.C \
    util.C

RESOURCES += \
    multimedia.qrc
