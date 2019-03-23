#-------------------------------------------------
#
# Project created by QtCreator 2018-12-22T01:19:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ENZYME_RUN
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-Enzyme-Desktop_Qt_5_11_2_GCC_64bit-Release/release/ -lEnzyme
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-Enzyme-Desktop_Qt_5_11_2_GCC_64bit-Release/debug/ -lEnzyme
else:unix: LIBS += -L$$PWD/../build-Enzyme-Desktop_Qt_5_11_2_GCC_64bit-Release/ -lEnzyme

INCLUDEPATH += $$PWD/../Enzyme
DEPENDPATH += $$PWD/../build-Enzyme-Desktop_Qt_5_11_2_GCC_64bit-Release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../lib/x86_64-linux-gnu/release/ -lutil-2.27
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../lib/x86_64-linux-gnu/debug/ -lutil-2.27
else:unix: LIBS += -L$$PWD/../../../lib/x86_64-linux-gnu/ -lutil-2.27

INCLUDEPATH += $$PWD/../../../lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../lib/x86_64-linux-gnu

