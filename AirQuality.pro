QT       += core gui network positioning charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/airqualityretriever.cpp \
    Controller/chartschooser.cpp \
    Model/dati.cpp \
    View/dataviewer.cpp \
    View/mychartview.cpp \
    main.cpp \
    Controller/startwindow.cpp

HEADERS += \
    Controller/airqualityretriever.h \
    Controller/chartschooser.h \
    Model/dati.h \
    View/dataviewer.h \
    Controller/startwindow.h \
    View/mychartview.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
