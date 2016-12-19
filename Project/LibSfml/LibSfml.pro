# ***    Paths  ***#

PATH_SOLUTION_ROOT = $$_PRO_FILE_PWD_/../..

INCLUDEPATH +=	$$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/include
INCLUDEPATH +=	$$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/src
INCLUDEPATH +=	$$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/extlibs/headers
INCLUDEPATH +=	$$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/extlibs/headers/AL
INCLUDEPATH +=	$$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/extlibs/headers/jpeg
INCLUDEPATH +=	$$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/extlibs/headers/libsndfile/windows
INCLUDEPATH +=	$$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/extlibs/headers/libfreetype/windows

VPATH += $$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/include
VPATH += $$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/src


#***  Sfml  ***#

#Auto begin  (Do not edit or duplicate ! Will be used by a script)

HEADERS +=  \
            SFML/Audio/Export.hpp \
            SFML/Audio/Listener.hpp \
            SFML/Audio/Music.hpp \
            SFML/Audio/Sound.hpp \
            SFML/Audio/SoundBuffer.hpp \
            SFML/Audio/SoundBufferRecorder.hpp \
            SFML/Audio/SoundRecorder.hpp \
            SFML/Audio/SoundSource.hpp \
            SFML/Audio/SoundStream.hpp \
            SFML/Audio.hpp \
            SFML/Config.hpp \
            SFML/Graphics/BlendMode.hpp \
            SFML/Graphics/CircleShape.hpp \
            SFML/Graphics/Color.hpp \
            SFML/Graphics/ConvexShape.hpp \
            SFML/Graphics/Drawable.hpp \
            SFML/Graphics/Export.hpp \
            SFML/Graphics/Font.hpp \
            SFML/Graphics/Glyph.hpp \
            SFML/Graphics/Image.hpp \
            SFML/Graphics/PrimitiveType.hpp \
            SFML/Graphics/Rect.hpp \
            SFML/Graphics/RectangleShape.hpp \
            SFML/Graphics/RenderStates.hpp \
            SFML/Graphics/RenderTarget.hpp \
            SFML/Graphics/RenderTexture.hpp \
            SFML/Graphics/RenderWindow.hpp \
            SFML/Graphics/Shader.hpp \
            SFML/Graphics/Shape.hpp \
            SFML/Graphics/Sprite.hpp \
            SFML/Graphics/Text.hpp \
            SFML/Graphics/Texture.hpp \
            SFML/Graphics/Transform.hpp \
            SFML/Graphics/Transformable.hpp \
            SFML/Graphics/Vertex.hpp \
            SFML/Graphics/VertexArray.hpp \
            SFML/Graphics/View.hpp \
            SFML/Graphics.hpp \
            SFML/Main.hpp \
            SFML/Network/Export.hpp \
            SFML/Network/Ftp.hpp \
            SFML/Network/Http.hpp \
            SFML/Network/IpAddress.hpp \
            SFML/Network/Packet.hpp \
            SFML/Network/Socket.hpp \
            SFML/Network/SocketHandle.hpp \
            SFML/Network/SocketSelector.hpp \
            SFML/Network/TcpListener.hpp \
            SFML/Network/TcpSocket.hpp \
            SFML/Network/UdpSocket.hpp \
            SFML/Network.hpp \
            SFML/OpenGL.hpp \
            SFML/System/Clock.hpp \
            SFML/System/Err.hpp \
            SFML/System/Export.hpp \
            SFML/System/InputStream.hpp \
            SFML/System/Lock.hpp \
            SFML/System/Mutex.hpp \
            SFML/System/NonCopyable.hpp \
            SFML/System/Sleep.hpp \
            SFML/System/String.hpp \
            SFML/System/Thread.hpp \
            SFML/System/ThreadLocal.hpp \
            SFML/System/ThreadLocalPtr.hpp \
            SFML/System/Time.hpp \
            SFML/System/Utf.hpp \
            SFML/System/Vector2.hpp \
            SFML/System/Vector3.hpp \
            SFML/System.hpp \
            SFML/Window/Context.hpp \
            SFML/Window/ContextSettings.hpp \
            SFML/Window/Event.hpp \
            SFML/Window/Export.hpp \
            SFML/Window/GlResource.hpp \
            SFML/Window/Joystick.hpp \
            SFML/Window/Keyboard.hpp \
            SFML/Window/Mouse.hpp \
            SFML/Window/Sensor.hpp \
            SFML/Window/Touch.hpp \
            SFML/Window/VideoMode.hpp \
            SFML/Window/Window.hpp \
            SFML/Window/WindowHandle.hpp \
            SFML/Window/WindowStyle.hpp \
            SFML/Window.hpp \
            SFML/Audio/ALCheck.hpp \
            SFML/Audio/AudioDevice.hpp \
            SFML/Audio/SoundFile.hpp \
            SFML/Graphics/GLCheck.hpp \
            SFML/Graphics/GLExtensions.hpp \
            SFML/Graphics/ImageLoader.hpp \
            SFML/Graphics/RenderTextureImpl.hpp \
            SFML/Graphics/RenderTextureImplDefault.hpp \
            SFML/Graphics/RenderTextureImplFBO.hpp \
            SFML/Graphics/stb_image/stb_image.h \
            SFML/Graphics/stb_image/stb_image_write.h \
            SFML/Graphics/TextureSaver.hpp \
            SFML/Network/SocketImpl.hpp \
            SFML/Network/Win32/SocketImpl.hpp \
            SFML/System/Win32/ClockImpl.hpp \
            SFML/System/Win32/MutexImpl.hpp \
            SFML/System/Win32/SleepImpl.hpp \
            SFML/System/Win32/ThreadImpl.hpp \
            SFML/System/Win32/ThreadLocalImpl.hpp \
            SFML/Window/GlContext.hpp \
            SFML/Window/glext/glext.h \
            SFML/Window/glext/wglext.h \
            SFML/Window/InputImpl.hpp \
            SFML/Window/JoystickImpl.hpp \
            SFML/Window/JoystickManager.hpp \
            SFML/Window/SensorImpl.hpp \
            SFML/Window/SensorManager.hpp \
            SFML/Window/VideoModeImpl.hpp \
            SFML/Window/Win32/InputImpl.hpp \
            SFML/Window/Win32/JoystickImpl.hpp \
            SFML/Window/Win32/SensorImpl.hpp \
            SFML/Window/Win32/WglContext.hpp \
            SFML/Window/Win32/WindowImplWin32.hpp \
            SFML/Window/WindowImpl.hpp

SOURCES +=  \
            SFML/Audio/ALCheck.cpp \
            SFML/Audio/AudioDevice.cpp \
            SFML/Audio/Listener.cpp \
            SFML/Audio/Music.cpp \
            SFML/Audio/Sound.cpp \
            SFML/Audio/SoundBuffer.cpp \
            SFML/Audio/SoundBufferRecorder.cpp \
            SFML/Audio/SoundFile.cpp \
            SFML/Audio/SoundRecorder.cpp \
            SFML/Audio/SoundSource.cpp \
            SFML/Audio/SoundStream.cpp \
            SFML/Graphics/BlendMode.cpp \
            SFML/Graphics/CircleShape.cpp \
            SFML/Graphics/Color.cpp \
            SFML/Graphics/ConvexShape.cpp \
            SFML/Graphics/Font.cpp \
            SFML/Graphics/GLCheck.cpp \
            SFML/Graphics/GLExtensions.cpp \
            SFML/Graphics/Image.cpp \
            SFML/Graphics/ImageLoader.cpp \
            SFML/Graphics/RectangleShape.cpp \
            SFML/Graphics/RenderStates.cpp \
            SFML/Graphics/RenderTarget.cpp \
            SFML/Graphics/RenderTexture.cpp \
            SFML/Graphics/RenderTextureImpl.cpp \
            SFML/Graphics/RenderTextureImplDefault.cpp \
            SFML/Graphics/RenderTextureImplFBO.cpp \
            SFML/Graphics/RenderWindow.cpp \
            SFML/Graphics/Shader.cpp \
            SFML/Graphics/Shape.cpp \
            SFML/Graphics/Sprite.cpp \
            SFML/Graphics/Text.cpp \
            SFML/Graphics/Texture.cpp \
            SFML/Graphics/TextureSaver.cpp \
            SFML/Graphics/Transform.cpp \
            SFML/Graphics/Transformable.cpp \
            SFML/Graphics/Vertex.cpp \
            SFML/Graphics/VertexArray.cpp \
            SFML/Graphics/View.cpp \
            SFML/Main/MainAndroid.cpp \
            SFML/Main/MainWin32.cpp \
            SFML/Network/Ftp.cpp \
            SFML/Network/Http.cpp \
            SFML/Network/IpAddress.cpp \
            SFML/Network/Packet.cpp \
            SFML/Network/Socket.cpp \
            SFML/Network/SocketSelector.cpp \
            SFML/Network/TcpListener.cpp \
            SFML/Network/TcpSocket.cpp \
            SFML/Network/UdpSocket.cpp \
            SFML/Network/Win32/SocketImpl.cpp \
            SFML/System/Clock.cpp \
            SFML/System/Err.cpp \
            SFML/System/Lock.cpp \
            SFML/System/Mutex.cpp \
            SFML/System/Sleep.cpp \
            SFML/System/String.cpp \
            SFML/System/Thread.cpp \
            SFML/System/ThreadLocal.cpp \
            SFML/System/Time.cpp \
            SFML/System/Win32/ClockImpl.cpp \
            SFML/System/Win32/MutexImpl.cpp \
            SFML/System/Win32/SleepImpl.cpp \
            SFML/System/Win32/ThreadImpl.cpp \
            SFML/System/Win32/ThreadLocalImpl.cpp \
            SFML/Window/Context.cpp \
            SFML/Window/GlContext.cpp \
            SFML/Window/GlResource.cpp \
            SFML/Window/Joystick.cpp \
            SFML/Window/JoystickManager.cpp \
            SFML/Window/Keyboard.cpp \
            SFML/Window/Mouse.cpp \
            SFML/Window/Sensor.cpp \
            SFML/Window/SensorManager.cpp \
            SFML/Window/Touch.cpp \
            SFML/Window/VideoMode.cpp \
            SFML/Window/Win32/InputImpl.cpp \
            SFML/Window/Win32/JoystickImpl.cpp \
            SFML/Window/Win32/SensorImpl.cpp \
            SFML/Window/Win32/VideoModeImpl.cpp \
            SFML/Window/Win32/WglContext.cpp \
            SFML/Window/Win32/WindowImplWin32.cpp \
            SFML/Window/Window.cpp \
            SFML/Window/WindowImpl.cpp

OTHER_FILES +=  \
            SFML/Audio/Export.hpp \
            SFML/Audio/Listener.hpp \
            SFML/Audio/Music.hpp \
            SFML/Audio/Sound.hpp \
            SFML/Audio/SoundBuffer.hpp \
            SFML/Audio/SoundBufferRecorder.hpp \
            SFML/Audio/SoundRecorder.hpp \
            SFML/Audio/SoundSource.hpp \
            SFML/Audio/SoundStream.hpp \
            SFML/Audio.hpp \
            SFML/Config.hpp \
            SFML/Graphics/BlendMode.hpp \
            SFML/Graphics/CircleShape.hpp \
            SFML/Graphics/Color.hpp \
            SFML/Graphics/ConvexShape.hpp \
            SFML/Graphics/Drawable.hpp \
            SFML/Graphics/Export.hpp \
            SFML/Graphics/Font.hpp \
            SFML/Graphics/Glyph.hpp \
            SFML/Graphics/Image.hpp \
            SFML/Graphics/PrimitiveType.hpp \
            SFML/Graphics/Rect.hpp \
            SFML/Graphics/RectangleShape.hpp \
            SFML/Graphics/RenderStates.hpp \
            SFML/Graphics/RenderTarget.hpp \
            SFML/Graphics/RenderTexture.hpp \
            SFML/Graphics/RenderWindow.hpp \
            SFML/Graphics/Shader.hpp \
            SFML/Graphics/Shape.hpp \
            SFML/Graphics/Sprite.hpp \
            SFML/Graphics/Text.hpp \
            SFML/Graphics/Texture.hpp \
            SFML/Graphics/Transform.hpp \
            SFML/Graphics/Transformable.hpp \
            SFML/Graphics/Vertex.hpp \
            SFML/Graphics/VertexArray.hpp \
            SFML/Graphics/View.hpp \
            SFML/Graphics.hpp \
            SFML/Main.hpp \
            SFML/Network/Export.hpp \
            SFML/Network/Ftp.hpp \
            SFML/Network/Http.hpp \
            SFML/Network/IpAddress.hpp \
            SFML/Network/Packet.hpp \
            SFML/Network/Socket.hpp \
            SFML/Network/SocketHandle.hpp \
            SFML/Network/SocketSelector.hpp \
            SFML/Network/TcpListener.hpp \
            SFML/Network/TcpSocket.hpp \
            SFML/Network/UdpSocket.hpp \
            SFML/Network.hpp \
            SFML/OpenGL.hpp \
            SFML/System/Clock.hpp \
            SFML/System/Err.hpp \
            SFML/System/Export.hpp \
            SFML/System/InputStream.hpp \
            SFML/System/Lock.hpp \
            SFML/System/Mutex.hpp \
            SFML/System/NonCopyable.hpp \
            SFML/System/Sleep.hpp \
            SFML/System/String.hpp \
            SFML/System/Thread.hpp \
            SFML/System/ThreadLocal.hpp \
            SFML/System/ThreadLocalPtr.hpp \
            SFML/System/Time.hpp \
            SFML/System/Utf.hpp \
            SFML/System/Vector2.hpp \
            SFML/System/Vector3.hpp \
            SFML/System.hpp \
            SFML/Window/Context.hpp \
            SFML/Window/ContextSettings.hpp \
            SFML/Window/Event.hpp \
            SFML/Window/Export.hpp \
            SFML/Window/GlResource.hpp \
            SFML/Window/Joystick.hpp \
            SFML/Window/Keyboard.hpp \
            SFML/Window/Mouse.hpp \
            SFML/Window/Sensor.hpp \
            SFML/Window/Touch.hpp \
            SFML/Window/VideoMode.hpp \
            SFML/Window/Window.hpp \
            SFML/Window/WindowHandle.hpp \
            SFML/Window/WindowStyle.hpp \
            SFML/Window.hpp \
            SFML/Audio/ALCheck.cpp \
            SFML/Audio/ALCheck.hpp \
            SFML/Audio/AudioDevice.cpp \
            SFML/Audio/AudioDevice.hpp \
            SFML/Audio/Listener.cpp \
            SFML/Audio/Music.cpp \
            SFML/Audio/Sound.cpp \
            SFML/Audio/SoundBuffer.cpp \
            SFML/Audio/SoundBufferRecorder.cpp \
            SFML/Audio/SoundFile.cpp \
            SFML/Audio/SoundFile.hpp \
            SFML/Audio/SoundRecorder.cpp \
            SFML/Audio/SoundSource.cpp \
            SFML/Audio/SoundStream.cpp \
            SFML/Graphics/BlendMode.cpp \
            SFML/Graphics/CircleShape.cpp \
            SFML/Graphics/Color.cpp \
            SFML/Graphics/ConvexShape.cpp \
            SFML/Graphics/Font.cpp \
            SFML/Graphics/GLCheck.cpp \
            SFML/Graphics/GLCheck.hpp \
            SFML/Graphics/GLExtensions.cpp \
            SFML/Graphics/GLExtensions.hpp \
            SFML/Graphics/Image.cpp \
            SFML/Graphics/ImageLoader.cpp \
            SFML/Graphics/ImageLoader.hpp \
            SFML/Graphics/RectangleShape.cpp \
            SFML/Graphics/RenderStates.cpp \
            SFML/Graphics/RenderTarget.cpp \
            SFML/Graphics/RenderTexture.cpp \
            SFML/Graphics/RenderTextureImpl.cpp \
            SFML/Graphics/RenderTextureImpl.hpp \
            SFML/Graphics/RenderTextureImplDefault.cpp \
            SFML/Graphics/RenderTextureImplDefault.hpp \
            SFML/Graphics/RenderTextureImplFBO.cpp \
            SFML/Graphics/RenderTextureImplFBO.hpp \
            SFML/Graphics/RenderWindow.cpp \
            SFML/Graphics/Shader.cpp \
            SFML/Graphics/Shape.cpp \
            SFML/Graphics/Sprite.cpp \
            SFML/Graphics/stb_image/stb_image.h \
            SFML/Graphics/stb_image/stb_image_write.h \
            SFML/Graphics/Text.cpp \
            SFML/Graphics/Texture.cpp \
            SFML/Graphics/TextureSaver.cpp \
            SFML/Graphics/TextureSaver.hpp \
            SFML/Graphics/Transform.cpp \
            SFML/Graphics/Transformable.cpp \
            SFML/Graphics/Vertex.cpp \
            SFML/Graphics/VertexArray.cpp \
            SFML/Graphics/View.cpp \
            SFML/Main/MainAndroid.cpp \
            SFML/Main/MainWin32.cpp \
            SFML/Network/Ftp.cpp \
            SFML/Network/Http.cpp \
            SFML/Network/IpAddress.cpp \
            SFML/Network/Packet.cpp \
            SFML/Network/Socket.cpp \
            SFML/Network/SocketImpl.hpp \
            SFML/Network/SocketSelector.cpp \
            SFML/Network/TcpListener.cpp \
            SFML/Network/TcpSocket.cpp \
            SFML/Network/UdpSocket.cpp \
            SFML/Network/Win32/SocketImpl.cpp \
            SFML/Network/Win32/SocketImpl.hpp \
            SFML/System/Clock.cpp \
            SFML/System/Err.cpp \
            SFML/System/Lock.cpp \
            SFML/System/Mutex.cpp \
            SFML/System/Sleep.cpp \
            SFML/System/String.cpp \
            SFML/System/Thread.cpp \
            SFML/System/ThreadLocal.cpp \
            SFML/System/Time.cpp \
            SFML/System/Win32/ClockImpl.cpp \
            SFML/System/Win32/ClockImpl.hpp \
            SFML/System/Win32/MutexImpl.cpp \
            SFML/System/Win32/MutexImpl.hpp \
            SFML/System/Win32/SleepImpl.cpp \
            SFML/System/Win32/SleepImpl.hpp \
            SFML/System/Win32/ThreadImpl.cpp \
            SFML/System/Win32/ThreadImpl.hpp \
            SFML/System/Win32/ThreadLocalImpl.cpp \
            SFML/System/Win32/ThreadLocalImpl.hpp \
            SFML/Window/Context.cpp \
            SFML/Window/GlContext.cpp \
            SFML/Window/GlContext.hpp \
            SFML/Window/glext/glext.h \
            SFML/Window/glext/wglext.h \
            SFML/Window/GlResource.cpp \
            SFML/Window/InputImpl.hpp \
            SFML/Window/Joystick.cpp \
            SFML/Window/JoystickImpl.hpp \
            SFML/Window/JoystickManager.cpp \
            SFML/Window/JoystickManager.hpp \
            SFML/Window/Keyboard.cpp \
            SFML/Window/Mouse.cpp \
            SFML/Window/Sensor.cpp \
            SFML/Window/SensorImpl.hpp \
            SFML/Window/SensorManager.cpp \
            SFML/Window/SensorManager.hpp \
            SFML/Window/Touch.cpp \
            SFML/Window/VideoMode.cpp \
            SFML/Window/VideoModeImpl.hpp \
            SFML/Window/Win32/InputImpl.cpp \
            SFML/Window/Win32/InputImpl.hpp \
            SFML/Window/Win32/JoystickImpl.cpp \
            SFML/Window/Win32/JoystickImpl.hpp \
            SFML/Window/Win32/SensorImpl.cpp \
            SFML/Window/Win32/SensorImpl.hpp \
            SFML/Window/Win32/VideoModeImpl.cpp \
            SFML/Window/Win32/WglContext.cpp \
            SFML/Window/Win32/WglContext.hpp \
            SFML/Window/Win32/WindowImplWin32.cpp \
            SFML/Window/Win32/WindowImplWin32.hpp \
            SFML/Window/Window.cpp \
            SFML/Window/WindowImpl.cpp \
            SFML/Window/WindowImpl.hpp

#Auto end  (Do not edit or duplicate ! Will be used by a script)


# ***    Config  ***#

TEMPLATE = lib

CONFIG += staticlib

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
    TARGET = SFML-s-d
    win32:DESTDIR = $$PATH_SOLUTION_ROOT/Libs
} else {
    # -- RELEASE
    TARGET = SFML-s
    win32:DESTDIR = $$PATH_SOLUTION_ROOT/Libs
}
