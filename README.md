# gugu::AudioPlayer 0.4.1-post

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
![No AI](https://img.shields.io/badge/No%20AI-gray)

A minimalist and lightweight audio player, written in C++, mainly based on SFML and ImGui.  
(less than 4 MB on disk, around 50 MB in RAM)  

Author : Legulysse  

## Quick Overview

The goal of this project is to provide a lightweight audioplayer for offline music play.  
Its main feature is the album shuffle (true shuffle, play all albums once before looping).  

- The user needs to fill the root directory of the local music library, then hit the "Parse and Run Playlist" button.  
- The audioplayer will shuffle all music albums found and play them one by one until all albums are played, before shuffling again.  
- Each album tracks will be played sequentially.  
- Any directory including one or more audio files will be considered as an album.  
- Supported formats : wav, flac, ogg, mp3.  
  
![Screenshot](/Docs/version-0_3.png)

## Dependencies

- [gugu::Engine](https://github.com/Legulysse/gugu-engine)


