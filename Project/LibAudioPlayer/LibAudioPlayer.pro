# ***    Paths  ***#

PATH_SOLUTION_ROOT = $$_PRO_FILE_PWD_/../..

INCLUDEPATH +=	$$PATH_SOLUTION_ROOT/Sources \
                $$PATH_SOLUTION_ROOT/GuguEngine/version_current/Dev/SourcesEngine \
                $$PATH_SOLUTION_ROOT/GuguEngine/version_current/Dev/SourcesSFML/include

VPATH +=	$$PATH_SOLUTION_ROOT/Sources \
            $$PATH_SOLUTION_ROOT/GuguEngine/version_current/Dev/SourcesEngine \
            $$PATH_SOLUTION_ROOT/GuguEngine/version_current/Dev/SourcesSFML/include


# ***    Files  ***#

SOURCES +=  Window/MainWindow.cpp \
            Dialog/DialogAbout.cpp

HEADERS  += Window/MainWindow.h \
            Dialog/DialogAbout.h

OTHER_FILES +=  Window/MainWindow.h \
                Window/MainWindow.cpp \
                Dialog/DialogAbout.h \
                Dialog/DialogAbout.cpp


# ***    Config  ***#

TEMPLATE = lib

CONFIG += staticlib

DEFINES += GUGU_QT
DEFINES += SFML_STATIC
DEFINES += GLEW_STATIC
DEFINES += UNICODE
DEFINES += _UNICODE
DEFINES += QT_NO_QT_INCLUDE_WARN

#QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -U__STRICT_ANSI__
QMAKE_CXXFLAGS_WARN_OFF += -Wunused-parameter

CONFIG(debug, debug|release) {
    # -- DEBUG
    TARGET = AudioPlayer-s-d
    win32:DESTDIR = $$PATH_SOLUTION_ROOT/Libs
} else {
    # -- RELEASE
    TARGET = AudioPlayer-s
    win32:DESTDIR = $$PATH_SOLUTION_ROOT/Libs
}
