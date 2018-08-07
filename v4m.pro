TEMPLATE = app
TARGET = v4m

QT += network \
      xml \
      multimedia \
      multimediawidgets \
      widgets

HEADERS = \
    player.h \
    frequency_player.h \
    playercontrols.h \
    playlistmodel.h \
    videowidget.h \
    histogramwidget.h \
    double_player.h
SOURCES = main.cpp \
    player.cpp \
    frequency_player.cpp \
    playercontrols.cpp \
    playlistmodel.cpp \
    videowidget.cpp \
    histogramwidget.cpp \
    double_player.cpp

target.path = .
INSTALLS += target
