include(userManager/usermanager.pri)

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/DataBase.h \
    $$PWD/includes.h \
    $$PWD/SystemSettings.h \
    $$PWD/Test.h \
    $$PWD/widget.h \
    $$PWD/MainWindow.h

SOURCES += \
    $$PWD/DataBase.cpp \
    $$PWD/SystemSettings.cpp \
    $$PWD/widget.cpp \
    $$PWD/MainWindow.cpp

FORMS +=
