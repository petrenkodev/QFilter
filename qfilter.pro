TEMPLATE = app
TARGET = qfilter
QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += \
#    c++11 \
#    debug_and_release

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d
} else {
    BUILD_FLAG = release
}

PROJECT_ROOT_PATH = $${PWD}/
BIN_PATH = $${PROJECT_ROOT_PATH}/bin/$${BUILD_FLAG}/
BUILD_PATH = $${PROJECT_ROOT_PATH}/build/$${BUILD_FLAG}/$${TARGET}/
RCC_DIR = $${BUILD_PATH}/rcc/
UI_DIR = $${BUILD_PATH}/ui/
MOC_DIR = $${BUILD_PATH}/moc/
OBJECTS_DIR = $${BUILD_PATH}/obj/

DESTDIR = $${BIN_PATH}/

SOURCES += \
    src/main.cpp \
    src/dialogs/mainwindow.cpp \
    src/dialogs/editdialog.cpp \
    src/dialogs/settingdialog.cpp \
    src/dialogs/aboutdialog.cpp \
    src/dialogs/manualdialog.cpp \
    src/models/wagonmodel.cpp \
    src/data/abstractrepository.cpp \
    src/data/sqliterepository.cpp \
    src/data/wagon.cpp \
    src/data/settings.cpp

HEADERS += \
    src/dialogs/mainwindow.h \
    src/dialogs/editdialog.h \
    src/dialogs/settingdialog.h \
    src/dialogs/aboutdialog.h \
    src/dialogs/manualdialog.h \
    src/models/wagonmodel.h \
    src/data/abstractrepository.h \
    src/data/sqliterepository.h \
    src/data/wagon.h \
    src/data/settings.h

FORMS += \
    src/dialogs/aboutdialog.ui \
    src/dialogs/editdialog.ui \
    src/dialogs/mainwindow.ui \
    src/dialogs/manualdialog.ui \
    src/dialogs/settingdialog.ui

RESOURCES += \
    src/resources/qfilter.qrc

OTHER_FILES += \
    .gitignore \
    README.md \
    qfilter.rc

#win32 {
#    RC_FILE += qfilter.rc
#    #RC_CODEPAGE =
#    #RC_ICONS = qfilter.ico
#}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/resources/manual.html
