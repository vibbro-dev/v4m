TEMPLATE = lib
TARGET = v4miOS
CONFIG += debug

# QT += network \
#       xml \
#       multimedia \
#       multimediawidgets \
#       widgets \
#       docgallery
# 
# HEADERS = \
#     player.h \
#     playercontrols.h \
#     playlistmodel.h \
#     videowidget.h \
#     histogramwidget.h \
#     double_player.h \
#     music_discovery.h \
#     v4m_music_path.h

SOURCES = MediaQueryForIos.mm

target.path = .
INSTALLS += target
