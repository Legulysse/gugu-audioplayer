# gugu::AudioPlayer 0.4.0-dev

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

A minimalist and lightweight audio player, written in C++, mainly based on SFML and ImGui.  
(less than 4 MB on disk, around 50 MB in RAM)  

Author : Legulysse  

## Quick Overview

The main feature of this audio player is the way it will randomly pick albums.  
(Any directory including one or more audio files will be considered as an album)  

The standard behaviour is to start the player, enter a root directory, and use "Parse and Run Playlist" to let the application scan this directory for albums.  
It will then randomly pick an album to play. Once finished, it will randomly pick another album.  
This behaviour will automatically loop once all albums have been played.  
The parser can be used for either a complete album collection, or using a subdirectory (like an artist directory) to only loop on the albums inside.  
  
The supported formats are .wav, .flac, .ogg, .mp3.  
  
![Screenshot](/Docs/version-0_3.png)

## Limitations

The application does not allow the selection of a specific album or track, it only relies on the automatic shuffle play of albums.  
  
More controls will be added in the future to remove those limitations.  

## Dependencies

- gugu::Engine
- SFML 2.6.x : used by the Engine.  
- PugiXml 1.11.4 : used by the Engine.  
- ImGui 1.85 (docking) : used by the Editor.  
- ImGui-SFML 2.3 : used for the ImGui integration.  
- Python 3.x : used for build and utility scripts.  
- Premake 5 alpha 16 : used by build scripts.  
