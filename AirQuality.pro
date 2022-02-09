QT       += core gui network positioning charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0# Suppress logging output for release build.
#CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT
#CONFIG(release, debug|release): DEFINES += QT_NO_INFO_OUTPUT
#CONFIG(release, debug|release): DEFINES += QT_NO_WARNING_OUTPUT
SOURCES += \
    Controller/chartsviewer.cpp \
    Controller/tablechooser.cpp \
    Model/dati.cpp \
    View/mychart.cpp \
    View/mychartview.cpp \
    Controller/airqualityretriever.cpp \
    Controller/chartschooser.cpp \
    Controller/startwindow.cpp\
    View/mylineseries.cpp \
    View/mypolarchart.cpp \
    View/mypolarseries.cpp \
    View/myscatterserie.cpp \
    View/mytableview.cpp \
    main.cpp \
    View/mybarseries.cpp \

HEADERS += \
    Controller/chartsviewer.h \
    Controller/tablechooser.h \
    Model/dati.h \
    View/mychart.h \
    View/mychartview.h \
    Controller/airqualityretriever.h \
    Controller/chartschooser.h \
    Controller/startwindow.h \
    View/mylineseries.h \
    View/mypolarchart.h \
    View/mypolarseries.h \
    View/myscatterserie.h \
    View/mybarseries.h \
    View/mytableview.h \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
