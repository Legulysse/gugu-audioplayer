# ***    Paths  ***#

PATH_SOLUTION_ROOT = $$_PRO_FILE_PWD_/../..

INCLUDEPATH +=	$$PATH_SOLUTION_ROOT/Sources \
				$$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesEngine \
				$$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/include

DEPENDPATH +=   $$PATH_SOLUTION_ROOT/Sources \
                $$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesEngine \
                $$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/include

VPATH +=	$$PATH_SOLUTION_ROOT/Sources

# ***    Files  ***#

SOURCES +=  main.cpp
OTHER_FILES +=  main.cpp
RC_FILE = $$PATH_SOLUTION_ROOT/Project/app.rc

# ***    Config  ***#

TEMPLATE = app

DEFINES += GUGU_QT
DEFINES += SFML_STATIC
DEFINES += GLEW_STATIC
DEFINES += UNICODE
DEFINES += _UNICODE
DEFINES += QT_NO_QT_INCLUDE_WARN

CONFIG += qt
QT = core widgets

#QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -U__STRICT_ANSI__
QMAKE_CXXFLAGS_WARN_OFF += -Wunused-parameter

CONFIG(debug, debug|release) {
	# -- DEBUG
    POST_TARGETDEPS +=  $$PATH_SOLUTION_ROOT/Libs/libAudioPlayer-s-d.a \
                        $$PATH_SOLUTION_ROOT/Libs/libGuguEngine-s-d.a \
                        $$PATH_SOLUTION_ROOT/Libs/libSFML-s-d.a

    QMAKE_LIBDIR += -L $$PATH_SOLUTION_ROOT/Libs
    LIBS += -lAudioPlayer-s-d \
            -lGuguEngine-s-d \
            -lSFML-s-d

    QMAKE_LIBDIR += $$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/extlibs/libs-mingw/x86
    LIBS += -ljpeg \
            -lfreetype \
            -lglew \
            -lgdi32 \
            -lopengl32 \
            -lopenal32 \
            -lsndfile \
            -lws2_32 \
            -lwinmm

    TARGET = GuguAudioPlayerDebug
	win32:DESTDIR = $$PATH_SOLUTION_ROOT/Version
} else {
	# -- RELEASE
    POST_TARGETDEPS +=  $$PATH_SOLUTION_ROOT/Libs/libAudioPlayer-s.a \
                        $$PATH_SOLUTION_ROOT/Libs/libGuguEngine-s.a \
                        $$PATH_SOLUTION_ROOT/Libs/libSFML-s.a

    QMAKE_LIBDIR += -L $$PATH_SOLUTION_ROOT/Libs
    LIBS += -lAudioPlayer-s \
            -lGuguEngine-s \
            -lSFML-s

    QMAKE_LIBDIR += $$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/extlibs/libs-mingw/x86
    LIBS += -ljpeg \
            -lfreetype \
            -lglew \
            -lgdi32 \
            -lopengl32 \
            -lopenal32 \
            -lsndfile \
            -lws2_32 \
            -lwinmm

    TARGET = GuguAudioPlayer
	win32:DESTDIR = $$PATH_SOLUTION_ROOT/Version
}
