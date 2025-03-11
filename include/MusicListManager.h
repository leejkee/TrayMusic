//
// Created by cww on 25-2-28.
//

#ifndef MUSICLISTMANAGER_H
#define MUSICLISTMANAGER_H
#include <QWidget>

#include "PlayList.h"
class MusicListButton;
class QVBoxLayout;
class QPushButton;
class QScrollArea;

class ButtonWidget final : public QWidget {
    Q_OBJECT

public:
    explicit ButtonWidget(QWidget *parent = nullptr);

    void addButton();



Q_SIGNALS:
    void playlistCreated(const QString &name);

private:
    QVBoxLayout *m_layout;
    MusicListButton *m_localMusicButton;
};

class MusicListManager final : public QWidget {
    Q_OBJECT

public:
    explicit MusicListManager(const QStringList &list, QWidget *parent = nullptr);
    ButtonWidget *m_buttonWidget;

private Q_SLOTS:
    void toggleExpand();


private:
    MusicListButton *m_buttonLocalMusic;
    QPushButton *m_expandButton;
    QPushButton *m_addButton;
    QScrollArea *m_scrollArea;

    void createConnections();
};


#endif //MUSICLISTMANAGER_H
