//
// Created by cww on 25-2-28.
//

#ifndef MUSICLISTMANAGER_H
#define MUSICLISTMANAGER_H
#include <QWidget>
#include "Song.h"
class MusicListButton;
class QVBoxLayout;
class QPushButton;
class QScrollArea;
class QHBoxLayout;

// TODO reflector

class MusicListManager final : public QWidget {
    Q_OBJECT

public:
    explicit MusicListManager(QWidget *parent);

    static QMap<QString, MusicListButton *> m_userListMap;

    [[nodiscard]]static const QList<Song> &getSongListViaName(const QString &name) ;

    void handleMusicButtonClicked(const QString &name);

    void addButton();

    void newButton(const QString &playlistName);

    static void createNewTable(const QString &playlistName);

    MusicListButton *m_buttonLocalMusic;

private Q_SLOTS:
    // expand icon change
    void toggleExpand();

private:
    QPushButton *m_expandButton;
    QPushButton *m_addButton;
    QScrollArea *m_scrollArea;

    QWidget *m_buttonWidget;
    QHBoxLayout *m_buttonLayout;

    void createConnections();
};


#endif //MUSICLISTMANAGER_H
