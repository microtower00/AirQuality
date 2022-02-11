QT       += core gui network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0# Suppress logging output for release build.
#CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT
#CONFIG(release, debug|release): DEFINES += QT_NO_INFO_OUTPUT
#CONFIG(release, debug|release): DEFINES += QT_NO_WARNING_OUTPUT
SOURCES += \
    chartsviewer.cpp \
    cittaedit.cpp \
    coordinate.cpp \
    datedialog.cpp \
    tablechooser.cpp \
    dati.cpp \
    mychart.cpp \
    mychartview.cpp \
    airqualityretriever.cpp \
    chartschooser.cpp \
    startwindow.cpp\
    mylineseries.cpp \
    mypolarchart.cpp \
    mypolarseries.cpp \
    myscatterserie.cpp \
    mytableview.cpp \
    main.cpp \
    mybarseries.cpp \

HEADERS += \
    chartsviewer.h \
    cittaedit.h \
    coordinate.h \
    datedialog.h \
    tablechooser.h \
    dati.h \
    mychart.h \
    mychartview.h \
    airqualityretriever.h \
    chartschooser.h \
    startwindow.h \
    mylineseries.h \
    mypolarchart.h \
    mypolarseries.h \
    myscatterserie.h \
    mybarseries.h \
    mytableview.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
