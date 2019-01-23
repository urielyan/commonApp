#SOURCES += UserManager.cpp \
#    Login.cpp \
#    UserData.cpp \
#    AlterPasswdDialog.cpp \
#    AddUserDialog.cpp

#HEADERS  += UserManager.h \
#    Login.h \
#    UserData.h \
#    AlterPasswdDialog.h \
#    AddUserDialog.h

#FORMS    += UserManager.ui \
#    Logingin.ui \
#    AlterPasswdDialog.ui \
#    AddUserDialog.ui

QT += sql

INCLUDEPATH += $$PWD

SOURCES += $$PWD/UserManager.cpp \
    $$PWD/Login.cpp \
    $$PWD/UserData.cpp \
    $$PWD/AlterPasswdDialog.cpp \
    $$PWD/AddUserDialog.cpp \
    $$PWD/LoginSettings.cpp

HEADERS  += $$PWD/UserManager.h \
    $$PWD/Login.h \
    $$PWD/UserData.h \
    $$PWD/AlterPasswdDialog.h \
    $$PWD/AddUserDialog.h \
    $$PWD/LoginSettings.h

FORMS    += $$PWD/UserManager.ui \
    $$PWD/Logingin.ui \
    $$PWD/AlterPasswdDialog.ui \
    $$PWD/AddUserDialog.ui
