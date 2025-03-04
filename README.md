### A Lightweight Music Player Using Qt Widget 6.8.2

[简体中文](README_cn.md)  
If you are looking for a reference project for the following purposes, this project may be useful:

- Learning **Qt Widget** development
- Finding a lightweight offline music player, even for deployment on **embedded devices**

### Screenshot

![Run](/doc/img/Running.png)

### Dependencies

**TagLib** – A C++ library for parsing MP3 **ID3 tag** information and retrieving music file durations.

- [TagLib](https://github.com/taglib/taglib)

### Project Structure & Features

- **WindowManager**
  - [x] Manages the overall window layout, window switching, and signal-slot connections

- **Player**
  - [x] Handles playback of individual music files

- **PlayerWidget**
  - [x] UI for basic music player functionalities

- **PlayList**
  - [x] Manages playlists, including **user-defined playlists** and **local directory scanning**
  - [x] Uses **TagLib API** to read music durations

- **ViewWidget**
  - [x] UI for displaying the song list

- **TopBarWidget**
  - [x] Manages the top bar, displaying the **logo**, **settings button**, and **back button**

- **MusicListManager**
  - [x] UI for the settings page

- **Settings**
  - [x] Reads and writes configuration files

- **DBManager**
  - [ ] Handles database operations (**CRUD**)  
