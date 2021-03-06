QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    csv.cpp \
    csvlistmodel.cpp \
    download.cpp \
    main.cpp \
    mainwindow.cpp \
    shareddata.cpp \
    students.cpp \
    urldialog.cpp

HEADERS += \
    csv.h \
    csvlistmodel.h \
    download.h \
    mainwindow.h \
    shareddata.h \
    students.h \
    urldialog.h

FORMS += \
    mainwindow.ui \
    urldialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
