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

target.path = .
INSTALLS += target
