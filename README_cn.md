## 一个极其简单的音乐播放器 使用Qt Widget 6.8.2实现
Tips:
- 本项目仅供学习交流
- 本项目使用的歌曲图标为AI生成。
 
如果你有以下目的，这个项目可以作为你的参考
- 仅仅学习Qt Widget
- 希望寻找一款轻量级的离线音乐播放器，甚至将其部署到嵌入式设备
## 运行截图
- Windows 11
  ![Run](/doc/img/run_06.png)
- Arch Linux (Plasma 6.3.3 X11 Theme: Breeze)  
  ![Run](/doc/img/run_05.png)

## 依赖
- `TabLig` 一个用来解析Mp3文件的ID3标签信息，以及获取音乐文件时长的C++库
  - 本项目使用了其中解析音乐时长的功能，部分linux发行版或许已经安装了该库，Windows
  用户请自行选择从源码编译，或者使用本项目`3rdParty`提供的编译好的dll
- [TagLib的源仓库地址](https://github.com/taglib/taglib)

## 项目结构

- MainWindow
  - [x] 系统托盘支持
- WindowManager
  - [x] 管理整体布局，管理窗口切换，管理各对象之间的信号槽的连接
  - [x] 初始化管理数据缓存的对象
- Player
  - [x] 单个音乐文件的播放
- PlayerWidget
  - [x] 音乐播放部分的UI
- ViewWidget
  - [x] 列表显示部分UI，显示歌曲列表，提供部分播放控制UI
- TopBarWidget
  - [x] 顶栏，显示logo,设置按钮，返回按钮
- MusicListWidget
  - [x] 左侧边栏UI，实现切换歌曲播放列表 
- LocalMusicSettingsWidget
  - [x] 本地音乐目录设置页面，并且实现了在播放本地音乐时的实时更新

- 数据缓存类
  - PlayList
    - [x] 管理当前被加载的歌单
  - MusicListCache
    - [x] 为其他数据使用类提供数据读写接口
  - Settings
    - [x] 读取配置文件，包括本地音乐目录列表，用户歌单名称列表，数据库文件目录，播放器默认设置
  - DBManager
    - [x] 提供读写用户数据的接口
