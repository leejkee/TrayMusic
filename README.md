### A Lightweight Music Player Using Qt Widget 6.8.2

[**简体中文**](README_cn.md)  

If you have any of the following goals, this project can serve as a reference:
- Learning **Qt Widget** development.
- Looking for a **lightweight offline music player**, even for deployment on **embedded devices**.

## Running Screenshot (Windows 11)
![Run](/doc/img/run_02.png)

## Dependencies
`TagLib` - A C++ library for parsing ID3 tag information from MP3 files and retrieving the duration of audio files.
- [TagLib](https://github.com/taglib/taglib)

## Project Structure & Features

### **Assets**
- [x] Stores constants

### **MainWindow**
- [x] System tray support

### **WindowManager**
- [x] Manages overall window layout
- [x] Handles window switching
- [x] Manages signal-slot connections

### **Player**
- [x] Controls the playback of a single music file

### **PlayerWidget**
- [x] UI for basic music player functionality

### **PlayList**
- [x] Manages the currently loaded playlist, including user-defined playlists and local directory scanning
- [x] Uses **TagLib** API to read music duration

### **ViewWidget**
- [x] Main UI for displaying the song list or switching to other settings pages

### **TopBarWidget**
- [x] Manages the top bar
- [x] Displays the **logo, settings button, and back button**

### **MusicListWidget**
- [x] UI for the **left-side** playlist panel
- [x] Controls playlist switching

### **MusicListCache**
- [x] Caches all playlists' data
- [x] Loads local music files from directories and user playlists from the database
- [x] Provides song data for components like **PlayList** and **ViewWidget**, allowing them to query songs by playlist name

### **Settings**
- [x] Reads configuration files, including:
  - Local music directory list
  - User-created playlist names
  - Database file location
  - Default player settings

### **LocalMusicSettingsWidget**
- [x] Manages local music directories
- [x] Allows users to **add, remove, and update directories** in real-time
- [x] Automatically updates the UI when the current view is the local music list

### **DBManager**
- [ ] Handles **CRUD (Create, Read, Update, Delete) operations** on the database
- [x] Reads and stores user data

