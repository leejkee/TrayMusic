//
// Created by cww on 25-2-25.
//

#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include "Song.h"


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

    void saveSongToTable(const QString &tableName, const Song &song);

    // db operate; only functions about "User Music List" call these functions
    // QStringList readListFromDB(const QString& listName);
    // void saveListToDB(const QStringList& list, const QString& tableName);
    // db operate

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
