QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_person.cpp \
    add_video.cpp \
    central.cpp \
    details_video.cpp \
    edit_livres.cpp \
    edit_person.cpp \
    edit_video.cpp \
    livres.cpp \
    main.cpp \
    login.cpp \
    search_person.cpp \
    search_video.cpp

HEADERS += \
    add_person.h \
    add_video.h \
    central.h \
    details_video.h \
    edit_livres.h \
    edit_person.h \
    edit_video.h \
    livres.h \
    login.h \
    search_person.h \
    search_video.h

FORMS += \
    add_person.ui \
    add_video.ui \
    central.ui \
    details_video.ui \
    edit_livres.ui \
    edit_person.ui \
    edit_video.ui \
    livres.ui \
    login.ui \
    search_person.ui \
    search_video.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
