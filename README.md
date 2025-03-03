## A Lightweight Music Player Using Qt Widget 6.8.2
[简体中文](README_cn.md)  
This project can serve as a reference if you:

* Are simply learning Qt Widget.
* Are looking for a lightweight offline music player, even for deployment on embedded devices.

## Dependencies

`TagLib`: A C++ library used to parse ID3 tag information from MP3 files and to obtain music file durations.

* [TagLib](https://github.com/taglib/taglib)

## Project Structure and Features

* **WindowManager**
    * [x] Manages the overall window layout.
* **Player**
    * [x] Manages the playback of individual music files.
* **PlayerWidget**
    * [x] Provides the UI for basic music player functions.
* **PlayList**
    * [x] Manages playlists, including user-defined playlists and local directory reading.
    * [x] Uses the TagLib API to read music durations.
* **ViewWidget**
    * [x] Displays the song list UI.
* **MusicListManager**
    * [x] Settings page UI.
* **Settings**
    * [x] Copies and reads configuration files.
* **DBManager**
    * [ ] Database CRUD operations (To be implemented).