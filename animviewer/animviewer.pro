QT += core
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += opengl

TARGET = QOSGViewer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

DESTDIR = ../../bin

win32 {

    OSG_LIB_DIRECTORY = $$(OSG_BIN_PATH)
    OSG_INCLUDE_DIRECTORY = $$(OSG_INCLUDE_PATH)


    CONFIG(debug, debug|release) {

        TARGET = $$join(TARGET,,,_d)

        LIBS += -L$$OSG_LIB_DIRECTORY -losgd
        LIBS += -L$$OSG_LIB_DIRECTORY -losgViewerd
        LIBS += -L$$OSG_LIB_DIRECTORY -losgDBd
        LIBS += -L$$OSG_LIB_DIRECTORY -lOpenThreadsd
        LIBS += -L$$OSG_LIB_DIRECTORY -losgGAd
        LIBS += -L$$OSG_LIB_DIRECTORY -losgQt5d
        LIBS += -L$$OSG_LIB_DIRECTORY -losgAnimationd

        LIBS += -L../../lib -lQOSGViewerWidget_d

    } else {

        LIBS += -L$$OSG_LIB_DIRECTORY -losg
        LIBS += -L$$OSG_LIB_DIRECTORY -losgViewer
        LIBS += -L$$OSG_LIB_DIRECTORY -losgDB
        LIBS += -L$$OSG_LIB_DIRECTORY -lOpenThreads
        LIBS += -L$$OSG_LIB_DIRECTORY -losgGA
        LIBS += -L$$OSG_LIB_DIRECTORY -losgQt5
        LIBS += -L$$OSG_LIB_DIRECTORY -losgAnimation

        LIBS += -L../../lib -lQOSGViewerWidget
    }

    INCLUDEPATH += $$OSG_INCLUDE_DIRECTORY
}

unix {

    CONFIG(debug, debug|release) {

        TARGET = $$join(TARGET,,,_d)

        LIBS += -losgd
        LIBS += -losgViewerd
        LIBS += -losgDBd
        LIBS += -lOpenThreadsd
        LIBS += -losgGAd
        LIBS += -losgQt5d
        LIBS += -losgAnimationd

        LIBS += -L../../lib -lQOSGViewerWidget_d

    } else {

        LIBS +=  -losg
        LIBS +=  -losgViewer
        LIBS +=  -losgDB
        LIBS +=  -lOpenThreads
        LIBS +=  -losgGA
        LIBS +=  -losgQt5
        LIBS += -losgAnimation

        LIBS += -L../../lib -lQOSGViewerWidget
    }
}

INCLUDEPATH += ./include
INCLUDEPATH += ../qviewerwidget/include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)
FORMS += $$files(./forms/*.ui)

TRANSLATIONS += ./translations/QOSGViewer_ru.ts

RESOURCES += $$files(./resources/*.qrc)