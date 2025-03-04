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
    // QPushButton *m_musicListManagerButton;

signals:
    void playlistCreated(const QString &name);

private slots:
    void toggleExpand();
    void createPlaylist();
    void addPlaylistButton(const QString &name);
    void removePlaylistButton(int index);

private:
    QVBoxLayout *m_mainLayout;
    QPushButton *m_expandButton;
    QPushButton *m_addButton;
    QWidget *m_buttonContainerWidget;
    QVector<QPushButton *> m_buttonsVector;
    QVBoxLayout *m_buttonLayout;
    QScrollArea *m_scrollArea;
};


#endif //MUSICLISTMANAGER_H
