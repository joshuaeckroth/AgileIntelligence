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
    -lhighgui \
    -lgdal1.5.0
SOURCES += main.cpp \
    mainwindow.cpp \
    Pixel.cpp \
    LatLon.cpp \
    Camera.cpp \
    RenderArea.cpp \
    ProcessingController.cpp \
    CaptureThread.cpp \
    CameraView.cpp \
    AreaOfInterest.cpp \
    AreaOfInterestReader.cpp \
    Hypothesis.cpp \
    Query1.cpp \
    State.cpp \
    HypothesisObjectInMotion.cpp
HEADERS += mainwindow.h \
    Pixel.h \
    LatLon.h \
    Camera.h \
    RenderArea.h \
    ProcessingController.h \
    CaptureThread.h \
    CameraView.h \
    AreaOfInterest.h \
    AreaOfInterestReader.h \
    Hypothesis.h \
    Query1.h \
    State.h \
    HypothesisObjectInMotion.h
FORMS += mainwindow.ui
