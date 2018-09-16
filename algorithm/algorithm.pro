#-------------------------------------------------
#
# Project created by QtCreator 2018-09-16T14:04:22
#
#-------------------------------------------------

QT       -= gui

TARGET   = algorithm
TEMPLATE = lib
CONFIG   += staticlib

DEFINES += ALGORITHM_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Algorithm.cpp \
    AlgorithmHelper.cpp \
    EmulatorEngine.cpp \
    VerificationEngine.cpp

HEADERS += \
    Algorithm.h \
    AlgorithmHelper.h \
    Config.h \
    DeviceConfig.h \
    EmulatorEngine.h \
    Interface.h \
    VerificationEngine.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$PWD/..

!contains(BUILD_WITH_EMULATOR, y) {
HEADERS += \
    $$OUT_PWD/../external/inc/arcsoft_module_errorcommon.h \
    $$OUT_PWD/../external/inc/arcsoft_verification.h \
    $$OUT_PWD/../external/inc/platform/amcomdef.h \
    $$OUT_PWD/../external/inc/platform/asvloffscreen.h \
    $$OUT_PWD/../external/inc/platform/merror.h

    message("Build with real algorithm.")
}
