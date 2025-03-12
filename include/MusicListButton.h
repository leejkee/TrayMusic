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
public:
    static QMap<QString, MusicListButton *> buttonMap;

    explicit MusicListButton(const QString &name, QWidget *parent = nullptr);

    [[nodiscard]] QList<Song> &getMusicList();

    void setMusicListFromSongs(const QList<Song> &list);

    /// Read QList<Song> from Database by the specified table.
    /// @param tableName
    void setMusicListFromDB(const QString &tableName);

private:
    QList<Song> songs;
};


#endif //MUSICLISTBUTTON_H
