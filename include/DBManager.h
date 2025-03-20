//
// Created by cww on 25-2-25.
//

#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include "Song.h"

class DatabaseInitializationError final : public std::runtime_error {
public:
    explicit DatabaseInitializationError(const QString& message) : std::runtime_error(message.toStdString()) {}
};

class DBManager {
public:
    static DBManager &instance() {
        static DBManager instance;
        return instance;
    }

    DBManager(const DBManager &) = delete;

    DBManager &operator=(const DBManager &) = delete;
    void initDB(const QString &dbName);

    void createTable(const QString &tableName) const;

    [[nodiscard]] QList<Song> getMusicList(const QString &tableName) const;

    void insertSongToTable(const QString &tableName, const Song &song) const;

    void delViaName(const QString &tableName, const QString &songName) const;

private:
    DBManager() {
    }
    ~DBManager() {
        if (m_db.isOpen()) {
            m_db.close();
        }
    }
    QSqlDatabase m_db;
};


#endif //DBMANAGER_H
