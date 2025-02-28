//
// Created by cww on 25-2-28.
//

#ifndef MUSICLISTMANAGER_H
#define MUSICLISTMANAGER_H
#include <QWidget>
class QVBoxLayout;
class QPushButton;
class QScrollArea;

class MusicListManager final : public QWidget {
    Q_OBJECT

public:
    explicit MusicListManager(QWidget *parent = nullptr);

signals:
    void playlistCreated(const QString &name); // 发送新歌单名

private slots:
    void toggleExpand();                         // 展开/收起
    void createPlaylist();                       // 新建歌单
    void addPlaylistButton(const QString &name); // 添加按钮到界面

private:
    QVBoxLayout *m_mainLayout;       // 主布局
    QPushButton *m_expandButton;     // 伸缩按钮
    QPushButton *m_addButton;        // 新建歌单按钮
    QWidget *m_buttonContainerWidget;      // 按钮容器
    QVBoxLayout *m_buttonLayout;     // 存放按钮
    QScrollArea *m_scrollArea;       // 滚动区域
    bool m_isExpanded;               // 是否展开
};


#endif //MUSICLISTMANAGER_H
