# -------------------------------------------------
# Project created by QtCreator 2009-07-12T12:02:19
# -------------------------------------------------
TARGET = AgileIntelligence
TEMPLATE = app
INCLUDEPATH = /home/josh/bin/installations/opencv/include/opencv
LIBS += -L/home/josh/bin/installations/opencv/lib \
    -lcv \
    -lcxcore \
    -lcvaux \
    -lhighgui
SOURCES += main.cpp \
    mainwindow.cpp \
    Pixel.cpp \
    LatLon.cpp \
    Camera.cpp
HEADERS += mainwindow.h \
    Pixel.h \
    LatLon.h \
    Camera.h
FORMS += mainwindow.ui
