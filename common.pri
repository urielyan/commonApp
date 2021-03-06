include(userManager/usermanager.pri)
include(navButton/navButton.pri)

INCLUDEPATH += $$PWD

#使在release下也能够输入日志
DEFINES += QT_MESSAGELOGCONTEXT
HEADERS += \
    $$PWD/DataBase.h \
    $$PWD/includes.h \
    $$PWD/SystemSettings.h \
    $$PWD/Test.h \
    $$PWD/widget.h \
    $$PWD/MainWindow.h \
    $$PWD/Settings.h \
    $$PWD/MessageHandle.h \
    $$PWD/App.h \
    $$PWD/ChatServer.h \
    $$PWD/LogWidget.h

SOURCES += \
    $$PWD/DataBase.cpp \
    $$PWD/SystemSettings.cpp \
    $$PWD/widget.cpp \
    $$PWD/MainWindow.cpp \
    $$PWD/Settings.cpp \
    $$PWD/App.cpp \
    $$PWD/ChatServer.cpp \
    $$PWD/LogWidget.cpp

FORMS += \
    $$PWD/LogWidget.ui
