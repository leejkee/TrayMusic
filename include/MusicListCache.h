//
// Created by cww on 25-3-16.
//

#ifndef MUSICLISTCACHE_H
#define MUSICLISTCACHE_H
#include "Song.h"

class MusicListCache {
public:
    static MusicListCache &instance() {
        static MusicListCache instance;
        return instance;
    };

    /// This function must be called first
    /// This function should be called after calling function DBManager::initDB() and Settings::loadFromJson()
    void load();

    MusicListCache(const MusicListCache &other) = delete;

    MusicListCache &operator=(const MusicListCache &other) = delete;

    [[nodiscard]] QList<Song> getSongListByName(const QString &listName) const;

    /// @brief Retrieves a list of song names from the specified playlist.
    /// @param listName The name of the playlist from which to retrieve song names.
    /// @return A list containing the names of all songs in the playlist. Returns an empty list if the playlist is not found or an error occurs.
    [[nodiscard]] QStringList getSongNameListByName(const QString &listName) const;

    void insert(const QString &list);

    void del(const QString &list);

    void reloadLocalMusicList();

private:
    MusicListCache() {
    }

    QMap<QString, QList<Song> > m_ListMap{};

};


#endif //MUSICLISTCACHE_H
