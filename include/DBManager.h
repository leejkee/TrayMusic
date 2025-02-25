//
// Created by cww on 25-2-25.
//

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

class DBManager {


public:
    explicit DBManager(const QString& dbName);
    void initDB(const QString& dbName);
    void createTable(const QString& tableName);
    ~DBManager() {
      if (m_db.isOpen()) {
        m_db.close();
      }
    }
    // db operate; only functions about "User Music List" call these functions
    // QStringList readListFromDB(const QString& listName);
    // void saveListToDB(const QStringList& list, const QString& tableName);
    // db operate

private:
      QSqlDatabase m_db;
};



#endif //DBMANAGER_H
