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

// TODO reflector
class ButtonWidget final : public QWidget {
    Q_OBJECT

public:
    explicit ButtonWidget(QWidget *parent = nullptr);





Q_SIGNALS:
    // signal to viewWidget to show the List
    void songsReady(const QString &);

public Q_SLOTS:
    void handleMusicButtonClicked(const QString &name);

private:
    QVBoxLayout *m_layout;
    void createButton(const QString &playlistName);

};

class MusicListManager final : public QWidget {
    Q_OBJECT

public:
    explicit MusicListManager(QWidget *parent);

    [[nodiscard]]static const QList<Song> &getSongListViaName(const QString &name) ;
    void addButton();

    void initUserListButton();

    MusicListButton *m_buttonLocalMusic;
    ButtonWidget *m_buttonWidget;

private Q_SLOTS:
    void toggleExpand();

private:
    QPushButton *m_expandButton;
    QPushButton *m_addButton;
    QScrollArea *m_scrollArea;

    static QMap<QString, MusicListButton *> m_userListMap;
    void createConnections();
};


#endif //MUSICLISTMANAGER_H
