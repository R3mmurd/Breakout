#  This file is part of Breakout game.
#  Copyright (C) 2020 by Alejandro J. Mujica

#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#  Any user request of this software, write to

#  Alejandro Mujica

#  aledrums@gmail.com


QMAKE_CXX=clang++

CONFIG += c++14

QT += core widgets multimedia

HEADERS += \
    ball.H \
    brick.H \
    bricks.H \
    gamemain.H \
    global.H \
    levelmaker.H \
    paddle.H \
    particlesystem.H \
    player.H \
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
    brick.C \
    bricks.C \
    gamemain.C \
    global.C \
    levelmaker.C \
    main.C \
    paddle.C \
    particlesystem.C \
    player.C \
    random.C \
    spritesheet.C \
    states.C \
    audio.C \
    font.C \
    util.C

RESOURCES += \
    multimedia.qrc
