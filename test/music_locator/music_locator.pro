TEMPLATE = app
TARGET = music_locator

QT += core

INCLUDEPATH += ../..

HEADERS = ../../music_discovery.h
SOURCES = main.cpp \
          ../../music_discovery.cpp \
          ../../v4m_music_path.cpp

target.path = .
INSTALLS += target
