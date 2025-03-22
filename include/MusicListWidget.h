//
// Created by cww on 25-2-28.
//

#ifndef MUSICLISTMANAGER_H
#define MUSICLISTMANAGER_H
#include <QWidget>
#include "Song.h"
class ListButton;
class QVBoxLayout;
class QPushButton;
class QScrollArea;

class MusicListWidget final : public QWidget {
    Q_OBJECT

public:
    explicit MusicListWidget(QWidget *parent);


Q_SIGNALS:
    void signalMusicListButtonClicked(const QString &playlistName);

    void signalMusicListButtonAdded(const QString &playlistName);

private Q_SLOTS:

    // expand icon
    void toggleExpand() const;

private:
    QPushButton *m_expandButton;
    QPushButton *m_addButton;
    QScrollArea *m_scrollArea;

    QWidget *m_buttonWidget;
    QVBoxLayout *m_buttonLayout;

    ListButton *m_localListButton;

    void createConnections();

    void handleMusicButtonClicked(const QString &name);

    // button from new
    void addButton();

    void newButton(const QString &playlistName);

    // buttons created by user from settings
    void initUserListButtons();
};


#endif //MUSICLISTMANAGER_H
