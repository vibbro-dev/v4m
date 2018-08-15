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
    playercontrols.h \
    playlistmodel.h \
    videowidget.h \
    histogramwidget.h \
    double_player.h \
    music_discovery.h \
    v4m_music_path.h

SOURCES = main.cpp \
    player.cpp \
    playercontrols.cpp \
    playlistmodel.cpp \
    videowidget.cpp \
    histogramwidget.cpp \
    double_player.cpp \
    music_discovery.cpp \
    v4m_music_path.cpp

binary_resources.target = music.rcc
binary_resources.depends = resources/music.qrc
binary_resources.commands = rcc -binary $$binary_resources.depends  -o $$binary_resources.target

resource_clean.commands = rm -f $$binary_resources.target
clean.depends += resource_clean

PRE_TARGETDEPS += $$binary_resources.target

QMAKE_EXTRA_TARGETS += binary_resources resource_clean clean

target.path = .
INSTALLS += target
