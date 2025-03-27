//
// Created by cww on 25-3-16.
//

#ifndef MUSICLISTCACHE_H
#define MUSICLISTCACHE_H
#include "Song.h"
#include <QHash>
#include <QPixmap>

class MusicListCache {
public:
    static MusicListCache &instance() {
        static MusicListCache instance;
        return instance;
    };

    /// This function must be called first
    /// This function should be called after calling function DBManager::initDB() and Settings::loadFromJson()
    void initCache();

    MusicListCache(const MusicListCache &other) = delete;

    MusicListCache &operator=(const MusicListCache &other) = delete;

    [[nodiscard]] QList<Song> getSongListByName(const QString &listName) const;

    /// @brief Retrieves a list of song names from the specified playlist.
    /// @param listName The name of the playlist from which to retrieve song names.
    /// @return A list containing the names of all songs in the playlist. Returns an empty list if the playlist is not found or an error occurs.
    [[nodiscard]] QStringList getSongNameListByName(const QString &listName) const;

    /// @param path local music paths in settings
    /// @return Song structure
    static QList<Song> getSongListFromDirectories(const QStringList &path);


    void reloadLocalMusicList();

    void insertList(const QString &list);

    void delList(const QString &list);

    [[nodiscard]] const QPixmap &getLogo(qsizetype index) const;


    /// Returns a unique random index from the available set.
    ///
    /// This function generates a random index from the range [0, size-1] without repetition
    /// until all indices have been used. Once all numbers have been used, the function
    /// reshuffles the list and starts over.
    ///
    /// @return A unique random index within the valid range.
    [[nodiscard]] qsizetype getRandomIndex() const;

private:
    MusicListCache() {}
    QHash<QString, QList<Song> > m_ListMap{};
    QVector<QPixmap> m_logos{};
};


#endif //MUSICLISTCACHE_H
