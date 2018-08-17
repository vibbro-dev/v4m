TEMPLATE = app
TARGET = v4m
CONFIG += debug

QT += network \
      xml \
      multimedia \
      multimediawidgets \
      widgets

HEADERS = \
    player.h \
    frequency_player.h \
    playercontrols.h \
    frequency_player_controls.h \
    playlistmodel.h \
    videowidget.h \
    histogramwidget.h \
    double_player.h \
    music_discovery.h \
    v4m_music_path.h

SOURCES = main.cpp \
    player.cpp \
    frequency_player.cpp \
    playercontrols.cpp \
    frequency_player_controls.cpp \
    playlistmodel.cpp \
    videowidget.cpp \
    histogramwidget.cpp \
    double_player.cpp \
    music_discovery.cpp \
    v4m_music_path.cpp

music_resources.target = music.rcc
music_resources.depends = resources/music.qrc
music_resources.commands = rcc -binary $$music_resources.depends  -o $$music_resources.target

frequencies_resources.target = frequencies.rcc
frequencies_resources.depends = resources/frequencies.qrc
frequencies_resources.commands = rcc -binary $$frequencies_resources.depends  -o $$frequencies_resources.target

resource_clean.commands = rm -f $$music_resources.target $$frequencies_resources.target
clean.depends += resource_clean

PRE_TARGETDEPS += $$music_resources.target $$frequencies_resources.target

QMAKE_EXTRA_TARGETS += music_resources frequencies_resources resource_clean clean

target.path = .
INSTALLS += target
