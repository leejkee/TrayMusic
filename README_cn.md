## 一个轻量级音乐播放器 使用Qt Widget 6.8.2
如果你有以下目的，这个项目可以作为你的参考
- 仅仅学习Qt Widget
- 希望寻找一款轻量级的离线音乐播放器，甚至将其部署到嵌入式设备
## 运行截图(Windows 11)
![Run](/doc/img/run.png)
## 依赖
`TabLig` 一个用来解析Mp3文件的ID3标签信息，以及获取音乐文件时长的C++库
- [TagLib](https://github.com/taglib/taglib)

## 项目结构和功能
- MainWindow
- [x] 系统托盘支持
- WindowManager
- [x] 管理整体窗口布局，管理窗口切换，管理信号和槽的连接
- Player
- [x] 管理单个音乐文件的播放
- PlayerWidget
- [x] 音乐播放器基本功能的UI
- PlayList
- [x] 管理歌单，包含用户自定义歌单，本地目录读取
- [x] 使用了TabLib的API读取音乐时长
- ViewWidget
- [x] 显示歌曲列表UI
- TopBarWidget
- [x] 管理顶栏，显示logo,设置按钮，返回按钮
- MusicListManager
- [x] 设置页面UI
- Settings
- [x] 复制读取配置文件
- SettingsWidget
- [x] 复制添加本地音乐目录，跟随添加和删除操作更新播放列表
- DBManager
- [ ] 增删查改数据库，读取用户数据，将用户修改保存到数据库
