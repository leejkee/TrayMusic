//
// Created by cww on 25-2-23.
//

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QStringList>


class PlayList {
public:
    static PlayList *instance()
    {
    static PlayList playListInstance;
    return &playListInstance;
    }

    void getCurrentMusicName();
    void getCurrentMusicPath();

private:
    QStringList::iterator m_currentIt;
    QStringList m_musicList;
    QString m_currentMusic;
};



#endif //PLAYLIST_H
