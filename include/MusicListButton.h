//
// Created by cww on 25-3-6.
// All these button contain a List<Song>, which can be loaded from Database,
// and PlayList also contains a List<Song>, which can be added to here by Right-click Menu.
//

#ifndef MUSICLISTBUTTON_H
#define MUSICLISTBUTTON_H
#include <QPushButton>
#include "Song.h"


class MusicListButton final : public QPushButton {
    Q_OBJECT

public:
    explicit MusicListButton(const QString &name, QWidget *parent = nullptr);

    [[nodiscard]] const QList<Song> &getMusicList() const;

    void setMusicListFromSongs(const QList<Song> &list);


signals:
    void buttonClicked(const QString &listName);

private Q_SLOTS:
    void onButtonClicked() {
        emit buttonClicked(m_listName);
    }

private:
    QString m_listName;
    QList<Song> m_songs;
};


#endif //MUSICLISTBUTTON_H
