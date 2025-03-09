//
// Created by cww on 25-3-6.
// All these button contain a List<Song>, which can be loaded from Database,
// and PlayList also contains a List<Song>, which can be added to here by Right-click Menu.
//

#ifndef MUSICLISTBUTTON_H
#define MUSICLISTBUTTON_H
#include <QPushButton>
#include "PlayList.h"


class MusicListButton final : public QPushButton {
public:
    explicit MusicListButton(QWidget *parent = nullptr);

    [[nodiscard]] QList<Song> &getMusicList();

    void setMusicList(const QList<Song> &list);

    void initListFromDB(const QList<Song> &list);

    static QList<MusicListButton *> &getMusicListButtons() {
        return buttons;
    }

private:
    // songs from DB
    QList<Song> songs;
    static QList<MusicListButton *> buttons;
};


#endif //MUSICLISTBUTTON_H
