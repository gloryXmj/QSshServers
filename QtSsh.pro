QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += console

INCLUDEPATH += $$PWD/ \
               $$PWD/ssh/ \
               $$PWD/ssh/include/

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    SFTP_Libssh2.cpp \
    ssh_connect.cpp

HEADERS += \
    mainwindow.h \
    SFTP_Libssh2.h

FORMS += \
    mainwindow.ui

LIBS += -L$$PWD/ssh/ -llibssh2 \
        -L$$PWD/ssh/ -llibeay32

message($$PWD/ssh/)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
