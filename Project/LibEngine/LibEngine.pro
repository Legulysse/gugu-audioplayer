# ***    Paths  ***#

PATH_SOLUTION_ROOT = $$_PRO_FILE_PWD_/../..

INCLUDEPATH +=	$$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesEngine
INCLUDEPATH +=	$$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesSFML/include

VPATH += $$PATH_SOLUTION_ROOT/GuguEngine/version_current/EngineProject/Dev/SourcesEngine


#***  GuguEngine  ***#

#Auto begin  (Do not edit or duplicate ! Will be used by a script)

HEADERS +=  \
            Gugu/3D/ActorComponentMesh.h \
            Gugu/3D/BillboardAnim.h \
            Gugu/3D/BillboardAnimated.h \
            Gugu/3D/BillboardAnimGroup.h \
            Gugu/3D/Camera3D.h \
            Gugu/3D/Character.h \
            Gugu/3D/Level3D.h \
            Gugu/3D/OgreCommon.h \
            Gugu/3D/OgreRenderer.h \
            Gugu/Audio/MusicInstance.h \
            Gugu/Audio/MusicLayer.h \
            Gugu/Audio/SoundInstance.h \
            Gugu/Common.h \
            Gugu/Element/2D/ElementSFDrawable.h \
            Gugu/Element/2D/ElementSprite.h \
            Gugu/Element/2D/ElementSpriteAnimated.h \
            Gugu/Element/2D/ElementText.h \
            Gugu/Element/2D/ElementTile.h \
            Gugu/Element/Element.h \
            Gugu/Element/ElementComposite.h \
            Gugu/Element/Gui/ElementButton.h \
            Gugu/Element/Gui/ElementList.h \
            Gugu/Element/Gui/ElementListItem.h \
            Gugu/Element/UI/ElementUILayout.h \
            Gugu/Engine.h \
            Gugu/External/PugiXml/pugiconfig.hpp \
            Gugu/External/PugiXml/pugixml.hpp \
            Gugu/External/PugiXmlWrap.h \
            Gugu/External/TinyXml/tinystr.h \
            Gugu/External/TinyXml/tinyxml.h \
            Gugu/External/TinyXmlWrap.h \
            Gugu/Manager/ManagerAudio.h \
            Gugu/Manager/ManagerConfig.h \
            Gugu/Manager/ManagerNetwork.h \
            Gugu/Manager/ManagerResources.h \
            Gugu/Misc/Application.h \
            Gugu/Misc/BaseAnimation2D.h \
            Gugu/Misc/EventListener.h \
            Gugu/Misc/Logger.h \
            Gugu/Misc/Logger.tpp \
            Gugu/Misc/UDim.h \
            Gugu/Network/ClientInfo.h \
            Gugu/Network/EnumsNetwork.h \
            Gugu/Network/NetworkPacket.h \
            Gugu/Render/QSFMLCanvas.h \
            Gugu/Render/Renderer.h \
            Gugu/Resources/AnimSet.h \
            Gugu/Resources/Datasheet.h \
            Gugu/Resources/EnumsResources.h \
            Gugu/Resources/Font.h \
            Gugu/Resources/Image.h \
            Gugu/Resources/ImageSet.h \
            Gugu/Resources/Music.h \
            Gugu/Resources/Resource.h \
            Gugu/Resources/ResourceInfo.h \
            Gugu/Resources/Sound.h \
            Gugu/Resources/SoundCue.h \
            Gugu/Utility/Action.h \
            Gugu/Utility/Delegate.h \
            Gugu/Utility/DeltaTime.h \
            Gugu/Utility/FileInfo.h \
            Gugu/Utility/FixedFloat.h \
            Gugu/Utility/Hash.h \
            Gugu/Utility/Math.h \
            Gugu/Utility/Math.tpp \
            Gugu/Utility/Random.h \
            Gugu/Utility/SharedPtr.h \
            Gugu/Utility/SharedPtr.tpp \
            Gugu/Utility/SharedPtrImpl.h \
            Gugu/Utility/SharedPtrImpl.tpp \
            Gugu/Utility/Singleton.h \
            Gugu/Utility/State.h \
            Gugu/Utility/StateMachine.h \
            Gugu/Utility/System.h \
            Gugu/Utility/System.tpp \
            Gugu/Utility/Types.h \
            Gugu/Utility/WeakPtr.h \
            Gugu/Utility/WeakPtr.tpp \
            Gugu/Version.h \
            Gugu/Window/Camera.h \
            Gugu/Window/HandlerEvents.h \
            Gugu/Window/Window.h \
            Gugu/Window/WindowOgre.h \
            Gugu/World/Actor.h \
            Gugu/World/ActorComponent.h \
            Gugu/World/Grid/BaseGrid.h \
            Gugu/World/Grid/GridCell.h \
            Gugu/World/Grid/HexGrid.h \
            Gugu/World/Grid/SquareGrid.h \
            Gugu/World/Level.h \
            Gugu/World/World.h

SOURCES +=  \
            Gugu/3D/ActorComponentMesh.cpp \
            Gugu/3D/BillboardAnim.cpp \
            Gugu/3D/BillboardAnimated.cpp \
            Gugu/3D/BillboardAnimGroup.cpp \
            Gugu/3D/Camera3D.cpp \
            Gugu/3D/Character.cpp \
            Gugu/3D/Level3D.cpp \
            Gugu/3D/OgreRenderer.cpp \
            Gugu/Audio/MusicInstance.cpp \
            Gugu/Audio/MusicLayer.cpp \
            Gugu/Audio/SoundInstance.cpp \
            Gugu/Element/2D/ElementSFDrawable.cpp \
            Gugu/Element/2D/ElementSprite.cpp \
            Gugu/Element/2D/ElementSpriteAnimated.cpp \
            Gugu/Element/2D/ElementText.cpp \
            Gugu/Element/2D/ElementTile.cpp \
            Gugu/Element/Element.cpp \
            Gugu/Element/ElementComposite.cpp \
            Gugu/Element/Gui/ElementButton.cpp \
            Gugu/Element/Gui/ElementList.cpp \
            Gugu/Element/Gui/ElementListItem.cpp \
            Gugu/Element/UI/ElementUILayout.cpp \
            Gugu/Engine.cpp \
            Gugu/External/PugiXml/pugixml.cpp \
            Gugu/External/PugiXmlWrap.cpp \
            Gugu/External/TinyXml/tinystr.cpp \
            Gugu/External/TinyXml/tinyxml.cpp \
            Gugu/External/TinyXml/tinyxmlerror.cpp \
            Gugu/External/TinyXml/tinyxmlparser.cpp \
            Gugu/External/TinyXmlWrap.cpp \
            Gugu/Manager/ManagerAudio.cpp \
            Gugu/Manager/ManagerConfig.cpp \
            Gugu/Manager/ManagerNetwork.cpp \
            Gugu/Manager/ManagerResources.cpp \
            Gugu/Misc/Application.cpp \
            Gugu/Misc/BaseAnimation2D.cpp \
            Gugu/Misc/EventListener.cpp \
            Gugu/Misc/Logger.cpp \
            Gugu/Misc/UDim.cpp \
            Gugu/Network/ClientInfo.cpp \
            Gugu/Network/NetworkPacket.cpp \
            Gugu/Render/QSFMLCanvas.cpp \
            Gugu/Render/Renderer.cpp \
            Gugu/Resources/AnimSet.cpp \
            Gugu/Resources/Datasheet.cpp \
            Gugu/Resources/Font.cpp \
            Gugu/Resources/Image.cpp \
            Gugu/Resources/ImageSet.cpp \
            Gugu/Resources/Music.cpp \
            Gugu/Resources/Resource.cpp \
            Gugu/Resources/ResourceInfo.cpp \
            Gugu/Resources/Sound.cpp \
            Gugu/Resources/SoundCue.cpp \
            Gugu/Utility/DeltaTime.cpp \
            Gugu/Utility/FileInfo.cpp \
            Gugu/Utility/FixedFloat.cpp \
            Gugu/Utility/Hash.cpp \
            Gugu/Utility/Math.cpp \
            Gugu/Utility/Random.cpp \
            Gugu/Utility/State.cpp \
            Gugu/Utility/StateMachine.cpp \
            Gugu/Utility/System.cpp \
            Gugu/Window/Camera.cpp \
            Gugu/Window/HandlerEvents.cpp \
            Gugu/Window/Window.cpp \
            Gugu/Window/WindowOgre.cpp \
            Gugu/World/Actor.cpp \
            Gugu/World/ActorComponent.cpp \
            Gugu/World/Grid/BaseGrid.cpp \
            Gugu/World/Grid/GridCell.cpp \
            Gugu/World/Grid/HexGrid.cpp \
            Gugu/World/Grid/SquareGrid.cpp \
            Gugu/World/Level.cpp \
            Gugu/World/World.cpp

OTHER_FILES +=  \
            Gugu/3D/ActorComponentMesh.cpp \
            Gugu/3D/ActorComponentMesh.h \
            Gugu/3D/BillboardAnim.cpp \
            Gugu/3D/BillboardAnim.h \
            Gugu/3D/BillboardAnimated.cpp \
            Gugu/3D/BillboardAnimated.h \
            Gugu/3D/BillboardAnimGroup.cpp \
            Gugu/3D/BillboardAnimGroup.h \
            Gugu/3D/Camera3D.cpp \
            Gugu/3D/Camera3D.h \
            Gugu/3D/Character.cpp \
            Gugu/3D/Character.h \
            Gugu/3D/Level3D.cpp \
            Gugu/3D/Level3D.h \
            Gugu/3D/OgreCommon.h \
            Gugu/3D/OgreRenderer.cpp \
            Gugu/3D/OgreRenderer.h \
            Gugu/Audio/MusicInstance.cpp \
            Gugu/Audio/MusicInstance.h \
            Gugu/Audio/MusicLayer.cpp \
            Gugu/Audio/MusicLayer.h \
            Gugu/Audio/SoundInstance.cpp \
            Gugu/Audio/SoundInstance.h \
            Gugu/Common.h \
            Gugu/Element/2D/ElementSFDrawable.cpp \
            Gugu/Element/2D/ElementSFDrawable.h \
            Gugu/Element/2D/ElementSprite.cpp \
            Gugu/Element/2D/ElementSprite.h \
            Gugu/Element/2D/ElementSpriteAnimated.cpp \
            Gugu/Element/2D/ElementSpriteAnimated.h \
            Gugu/Element/2D/ElementText.cpp \
            Gugu/Element/2D/ElementText.h \
            Gugu/Element/2D/ElementTile.cpp \
            Gugu/Element/2D/ElementTile.h \
            Gugu/Element/Element.cpp \
            Gugu/Element/Element.h \
            Gugu/Element/ElementComposite.cpp \
            Gugu/Element/ElementComposite.h \
            Gugu/Element/Gui/ElementButton.cpp \
            Gugu/Element/Gui/ElementButton.h \
            Gugu/Element/Gui/ElementList.cpp \
            Gugu/Element/Gui/ElementList.h \
            Gugu/Element/Gui/ElementListItem.cpp \
            Gugu/Element/Gui/ElementListItem.h \
            Gugu/Element/UI/ElementUILayout.cpp \
            Gugu/Element/UI/ElementUILayout.h \
            Gugu/Engine.cpp \
            Gugu/Engine.h \
            Gugu/External/PugiXml/pugiconfig.hpp \
            Gugu/External/PugiXml/pugixml.cpp \
            Gugu/External/PugiXml/pugixml.hpp \
            Gugu/External/PugiXmlWrap.cpp \
            Gugu/External/PugiXmlWrap.h \
            Gugu/External/TinyXml/tinystr.cpp \
            Gugu/External/TinyXml/tinystr.h \
            Gugu/External/TinyXml/tinyxml.cpp \
            Gugu/External/TinyXml/tinyxml.h \
            Gugu/External/TinyXml/tinyxmlerror.cpp \
            Gugu/External/TinyXml/tinyxmlparser.cpp \
            Gugu/External/TinyXmlWrap.cpp \
            Gugu/External/TinyXmlWrap.h \
            Gugu/Manager/ManagerAudio.cpp \
            Gugu/Manager/ManagerAudio.h \
            Gugu/Manager/ManagerConfig.cpp \
            Gugu/Manager/ManagerConfig.h \
            Gugu/Manager/ManagerNetwork.cpp \
            Gugu/Manager/ManagerNetwork.h \
            Gugu/Manager/ManagerResources.cpp \
            Gugu/Manager/ManagerResources.h \
            Gugu/Misc/Application.cpp \
            Gugu/Misc/Application.h \
            Gugu/Misc/BaseAnimation2D.cpp \
            Gugu/Misc/BaseAnimation2D.h \
            Gugu/Misc/EventListener.cpp \
            Gugu/Misc/EventListener.h \
            Gugu/Misc/Logger.cpp \
            Gugu/Misc/Logger.h \
            Gugu/Misc/Logger.tpp \
            Gugu/Misc/UDim.cpp \
            Gugu/Misc/UDim.h \
            Gugu/Network/ClientInfo.cpp \
            Gugu/Network/ClientInfo.h \
            Gugu/Network/EnumsNetwork.h \
            Gugu/Network/NetworkPacket.cpp \
            Gugu/Network/NetworkPacket.h \
            Gugu/Render/QSFMLCanvas.cpp \
            Gugu/Render/QSFMLCanvas.h \
            Gugu/Render/Renderer.cpp \
            Gugu/Render/Renderer.h \
            Gugu/Resources/AnimSet.cpp \
            Gugu/Resources/AnimSet.h \
            Gugu/Resources/Datasheet.cpp \
            Gugu/Resources/Datasheet.h \
            Gugu/Resources/EnumsResources.h \
            Gugu/Resources/Font.cpp \
            Gugu/Resources/Font.h \
            Gugu/Resources/Image.cpp \
            Gugu/Resources/Image.h \
            Gugu/Resources/ImageSet.cpp \
            Gugu/Resources/ImageSet.h \
            Gugu/Resources/Music.cpp \
            Gugu/Resources/Music.h \
            Gugu/Resources/Resource.cpp \
            Gugu/Resources/Resource.h \
            Gugu/Resources/ResourceInfo.cpp \
            Gugu/Resources/ResourceInfo.h \
            Gugu/Resources/Sound.cpp \
            Gugu/Resources/Sound.h \
            Gugu/Resources/SoundCue.cpp \
            Gugu/Resources/SoundCue.h \
            Gugu/Utility/Action.h \
            Gugu/Utility/Delegate.h \
            Gugu/Utility/DeltaTime.cpp \
            Gugu/Utility/DeltaTime.h \
            Gugu/Utility/FileInfo.cpp \
            Gugu/Utility/FileInfo.h \
            Gugu/Utility/FixedFloat.cpp \
            Gugu/Utility/FixedFloat.h \
            Gugu/Utility/Hash.cpp \
            Gugu/Utility/Hash.h \
            Gugu/Utility/Math.cpp \
            Gugu/Utility/Math.h \
            Gugu/Utility/Math.tpp \
            Gugu/Utility/Random.cpp \
            Gugu/Utility/Random.h \
            Gugu/Utility/SharedPtr.h \
            Gugu/Utility/SharedPtr.tpp \
            Gugu/Utility/SharedPtrImpl.h \
            Gugu/Utility/SharedPtrImpl.tpp \
            Gugu/Utility/Singleton.h \
            Gugu/Utility/State.cpp \
            Gugu/Utility/State.h \
            Gugu/Utility/StateMachine.cpp \
            Gugu/Utility/StateMachine.h \
            Gugu/Utility/System.cpp \
            Gugu/Utility/System.h \
            Gugu/Utility/System.tpp \
            Gugu/Utility/Types.h \
            Gugu/Utility/WeakPtr.h \
            Gugu/Utility/WeakPtr.tpp \
            Gugu/Version.h \
            Gugu/Window/Camera.cpp \
            Gugu/Window/Camera.h \
            Gugu/Window/HandlerEvents.cpp \
            Gugu/Window/HandlerEvents.h \
            Gugu/Window/Window.cpp \
            Gugu/Window/Window.h \
            Gugu/Window/WindowOgre.cpp \
            Gugu/Window/WindowOgre.h \
            Gugu/World/Actor.cpp \
            Gugu/World/Actor.h \
            Gugu/World/ActorComponent.cpp \
            Gugu/World/ActorComponent.h \
            Gugu/World/Grid/BaseGrid.cpp \
            Gugu/World/Grid/BaseGrid.h \
            Gugu/World/Grid/GridCell.cpp \
            Gugu/World/Grid/GridCell.h \
            Gugu/World/Grid/HexGrid.cpp \
            Gugu/World/Grid/HexGrid.h \
            Gugu/World/Grid/SquareGrid.cpp \
            Gugu/World/Grid/SquareGrid.h \
            Gugu/World/Level.cpp \
            Gugu/World/Level.h \
            Gugu/World/World.cpp \
            Gugu/World/World.h

#Auto end  (Do not edit or duplicate ! Will be used by a script)


# ***    Config  ***#

TEMPLATE = lib

CONFIG += staticlib

DEFINES += GUGU_QT
DEFINES += SFML_STATIC
DEFINES += GLEW_STATIC
DEFINES += QT_NO_QT_INCLUDE_WARN

#QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -U__STRICT_ANSI__
QMAKE_CXXFLAGS_WARN_OFF += -Wunused-parameter

CONFIG(debug, debug|release) {
    # -- DEBUG
    TARGET = GuguEngine-s-d
    win32:DESTDIR = $$PATH_SOLUTION_ROOT/Libs
} else {
    # -- RELEASE
    TARGET = GuguEngine-s
    win32:DESTDIR = $$PATH_SOLUTION_ROOT/Libs
}
