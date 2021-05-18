QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arinc429widget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    arinc429widget.h \
    mainwindow.h

FORMS += \
    arinc429widget.ui \
    mainwindow.ui

RESOURCES += \
    resources.qrc

# Set Icon application on macOS
macx {
    ICON = decode.icns
}

#set Icon application on Windows
win32 {
    RC_ICONS = decode.ico
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../A429Library/build/release/ -lA429Library
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../A429Library/build/debug/ -lA429Library
else:unix: LIBS += -L$$PWD/../A429Library/build/ -lA429Library

INCLUDEPATH += $$PWD/../A429Library
DEPENDPATH += $$PWD/../A429Library

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../A429Library/build/release/libA429Library.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../A429Library/build/debug/libA429Library.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../A429Library/build/release/A429Library.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../A429Library/build/debug/A429Library.lib
else:unix: PRE_TARGETDEPS += $$PWD/../A429Library/build/libA429Library.a
