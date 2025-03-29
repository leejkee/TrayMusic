# A Very Simple Music Player Using Qt Widget 6.8.2

[**简体中文**](README_cn.md)
## Tips:
- This project is for learning and communication purposes only
- The song icons used in this project are AI-generated.

This project can serve as a reference if you have the following goals:
- Just learning Qt Widget
- Looking for a lightweight offline music player that can even be deployed to embedded devices

## Screenshot (Windows 11)
![Run](/doc/img/run_04.png)

## Dependencies
- `TagLib`: A C++ library for parsing ID3 tag information of MP3 files and obtaining music file duration
  - This project uses its music duration parsing functionality. Some Linux distributions may already have this library installed. Windows users should compile from source or use the pre-compiled dll provided in this project's `3rdParty` folder
- [TagLib's repository address](https://github.com/taglib/taglib)

## Project Structure

### MainWindow
- [x] System tray support

### WindowManager
- [x] Manages overall layout, window switching, and signal-slot connections between objects
- [x] Initializes data cache management objects

### Player
- [x] Single music file playback

### PlayerWidget
- [x] Music playback UI components

### ViewWidget
- [x] List display UI, shows song list and provides some playback control UI

### TopBarWidget
- [x] Top bar displaying logo, settings button, and back button

### MusicListWidget
- [x] Left sidebar UI for switching playlists

### LocalMusicSettingsWidget
- [x] Local music directory settings page with real-time updates during local music playback

### Data Cache Classes

#### PlayList
- [x] Manages currently loaded playlists

#### MusicListCache
- [x] Provides data read/write interfaces for other data-using classes

#### Settings
- [x] Reads configuration files including:
  - Local music directory list
  - User playlist name list
  - Database file directory
  - Player default settings

#### DBManager
- [x] Provides read/write interfaces for user data