## 一个轻量级音乐播放器 使用Qt Widget 6.8.2
如果你有以下目的，这个项目可以作为你的参考
- 仅仅学习Qt Widget
- 希望寻找一款轻量级的离线音乐播放器，甚至将其部署到嵌入式设备
## 运行截图(Windows 11)
![Run](/doc/img/run_03.png)
## 依赖
`TabLig` 一个用来解析Mp3文件的ID3标签信息，以及获取音乐文件时长的C++库
- [TagLib](https://github.com/taglib/taglib)

## 项目结构和功能
- Assets
- [x] 存储常量
- MainWindow
- [x] 系统托盘支持
- WindowManager
- [x] 管理整体窗口布局，管理窗口切换，管理信号和槽的连接
- Player
- [x] 管理单个音乐文件的播放
- PlayerWidget
- [x] 音乐播放器基本功能的UI
- PlayList
- [x] 管理当前被加载的歌单，包含用户自定义歌单，本地目录读取
- [x] 使用了TabLib的API读取音乐时长
- ViewWidget
- [x] 主界面UI，显示歌曲列表，或者被切换到其他设置界面
- TopBarWidget
- [x] 管理顶栏，显示logo,设置按钮，返回按钮
- MusicListWidget
- [x] 左侧边区域UI绘制，控制的是播放列表的切换功能
- MusicListCache
- [x] 缓存全部列表的数据，从本地目录加载本地文件，从数据加载用户歌单
- [x] 为其他需要加载歌曲信息的组件提供数据来源，只需提交歌单名称即可查询(PlayList, ViewWidget)
- Settings
- [x] 读取配置文件，包括本地音乐目录列表，用户歌单名称列表，数据库文件目录，播放器默认设置
- LocalMusicSettingsWidget
- [x] 本地音乐目录管理，可以添加目录，删除目录，并且实时更新界面，如果当前加载的是本地列表 
- DBManager
- [ ] 增删查改数据库，读取用户数据，将用户修改保存到数据库
