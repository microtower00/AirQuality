QT       += core gui network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0# Suppress logging output for release build.
CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT
CONFIG(release, debug|release): DEFINES += QT_NO_INFO_OUTPUT
CONFIG(release, debug|release): DEFINES += QT_NO_WARNING_OUTPUT
SOURCES += \
    Charts/MyCharts/mychart.cpp \
    Charts/MyCharts/mypolarchart.cpp \
    Charts/MySeries/mybarseries.cpp \
    Charts/MySeries/mylineseries.cpp \
    Charts/MySeries/mypolarseries.cpp \
    Charts/MySeries/myscatterseries.cpp \
    Charts/chartschooser.cpp \
    Charts/mychartview.cpp \
    Model/dati.cpp \
    Table/mytableview.cpp \
    Table/tablechooser.cpp \
    Utilities/airqualityretriever.cpp \
    Utilities/cittaedit.cpp \
    Utilities/coordinate.cpp \
    Utilities/datedialog.cpp \
    Windows/dataviewer.cpp \
    Windows/startwindow.cpp\
    main.cpp

HEADERS += \
    Charts/MyCharts/mychart.h \
    Charts/MyCharts/mypolarchart.h \
    Charts/MySeries/mybarseries.h \
    Charts/MySeries/mylineseries.h \
    Charts/MySeries/mypolarseries.h \
    Charts/MySeries/myscatterseries.h \
    Charts/chartschooser.h \
    Charts/mychartview.h \
    Model/dati.h \
    Table/mytableview.h \
    Table/tablechooser.h \
    Utilities/airqualityretriever.h \
    Utilities/cittaedit.h \
    Utilities/coordinate.h \
    Utilities/datedialog.h \
    Windows/dataviewer.h \
    Windows/startwindow.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_ICONS = icona.ico
