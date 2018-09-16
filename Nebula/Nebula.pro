#-------------------------------------------------
#
# Project created by QtCreator 2018-09-16T16:22:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nebula
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

INCLUDEPATH += $$PWD/..

SOURCES += main.cpp

FORMS +=                         \
    ../designer/LegacyDefault.ui \
    ../designer/LegacyDevice.ui  \
    ../designer/Default.ui       \
    ../designer/Devices.ui       \
    ../designer/AboutDialog.ui

RESOURCES +=                     \
    ../resource/Pictures.qrc

RC_ICONS = "../icon.ico"


win32:CONFIG(release, debug|release):                 \
    LIBS +=                                           \
        -L$$OUT_PWD/../ui/release/        -lui        \
        -L$$OUT_PWD/../core/release/      -lcore      \
        -L$$OUT_PWD/../remote/release/    -lremote    \
        -L$$OUT_PWD/../algorithm/release/ -lalgorithm \
        -L$$OUT_PWD/../utils/release/     -lutils     \

else:win32:CONFIG(debug, debug|release): \
    LIBS +=                                           \
        -L$$OUT_PWD/../ui/debug/        -lui          \
        -L$$OUT_PWD/../core/debug/      -lcore        \
        -L$$OUT_PWD/../remote/debug/    -lremote      \
        -L$$OUT_PWD/../algorithm/debug/ -lalgorithm   \
        -L$$OUT_PWD/../utils/debug/     -lutils       \
        -L$$OUT_PWD/../core/debug/      -lcore        \
        -L$$OUT_PWD/../algorithm/debug/ -lalgorithm   \
        -L$$OUT_PWD/../remote/debug/    -lremote      \
        -L$$OUT_PWD/../ui/debug/        -lui          \
        -L$$OUT_PWD/../utils/debug/     -lutils       \

else:unix:                                            \
    LIBS +=                                           \
        -L$$OUT_PWD/../ui/        -lui                \
        -L$$OUT_PWD/../core/      -lcore              \
        -L$$OUT_PWD/../remote/    -lremote            \
        -L$$OUT_PWD/../algorithm/ -lalgorithm         \
        -L$$OUT_PWD/../utils/     -lutils             \

INCLUDEPATH +=         \
    $$PWD/../ui        \
    $$PWD/../core      \
    $$PWD/../remote    \
    $$PWD/../algorithm \
    $$PWD/../utils     \

DEPENDPATH +=          \
    $$PWD/../ui        \
    $$PWD/../core      \
    $$PWD/../remote    \
    $$PWD/../algorithm \
    $$PWD/../utils     \

win32-g++:CONFIG(release, debug|release):             \
    PRE_TARGETDEPS +=                                 \
        $$OUT_PWD/../ui/release/libui.a               \
        $$OUT_PWD/../core/release/libcore.a           \
        $$OUT_PWD/../remote/release/libremote.a       \
        $$OUT_PWD/../algorithm/release/libalgorithm.a \
        $$OUT_PWD/../utils/release/libutils.a         \

else:win32-g++:CONFIG(debug, debug|release):          \
    PRE_TARGETDEPS +=                                 \
        $$OUT_PWD/../ui/debug/libui.a                 \
        $$OUT_PWD/../core/debug/libcore.a             \
        $$OUT_PWD/../remote/debug/libremote.a         \
        $$OUT_PWD/../algorithm/debug/libalgorithm.a   \
        $$OUT_PWD/../utils/debug/libutils.a           \

else:win32:!win32-g++:CONFIG(release, debug|release): \
    PRE_TARGETDEPS +=                                 \
        $$OUT_PWD/../ui/release/libui.a               \
        $$OUT_PWD/../core/release/libcore.a           \
        $$OUT_PWD/../remote/release/libremote.a       \
        $$OUT_PWD/../algorithm/release/libalgorithm.a \
        $$OUT_PWD/../utils/release/libutils.a         \

else:win32:!win32-g++:CONFIG(debug, debug|release):   \
    PRE_TARGETDEPS +=                                 \
        $$OUT_PWD/../ui/debug/libui.a                 \
        $$OUT_PWD/../core/debug/libcore.a             \
        $$OUT_PWD/../remote/debug/libremote.a         \
        $$OUT_PWD/../algorithm/debug/libalgorithm.a   \
        $$OUT_PWD/../utils/debug/libutils.a           \

else:unix:                                            \
    PRE_TARGETDEPS +=                                 \
        $$OUT_PWD/../ui/libui.a                       \
        $$OUT_PWD/../core/libcore.a                   \
        $$OUT_PWD/../remote/libremote.a               \
        $$OUT_PWD/../algorithm/libalgorithm.a         \
        $$OUT_PWD/../utils/libutils.a                 \


LIBS += -L$$PWD/../external/lib/ -larcsoft_verification

INCLUDEPATH += $$PWD/../external/inc
DEPENDPATH  += $$PWD/../external/inc
