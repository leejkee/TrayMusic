//
// Created by cww on 25-2-25.
//

#include "DBManager.h"
#include <QSqlError>
#include <QSqlQuery>



void DBManager::initDB(const QString &dbName) {
    if (m_db.isOpen()) {
        return;
    }
    m_db = QSqlDatabase::addDatabase("QSQLITE", dbName);
    if (!m_db.open()) {
        qDebug() << "Failed to open database" << m_db.lastError().text();
        return;
    }
}

void DBManager::createTable(const QString &tableName) {
    if (!m_db.isOpen()) {
        qDebug() << "Database is not open" << m_db.lastError().text();
        return;
    }
    if (m_db.tables().contains(tableName)) {
        qDebug() << "Table " << tableName << " exists.";
        return;
    }
    qDebug() << "Table " << tableName << " created.";
    const QString COLUMN_ID = "id";
    const QString COLUMN_PATH = "path";
    const QString COLUMN_NAME = "name";
    const QString COLUMN_DURATION = "duration";
    // create table and add list to table
    const QString queryCreateTable{
        QString("CREATE TABLE IF NOT EXISTS %1 ("
            "%2 INTEGER PRIMARY KEY AUTOINCREMENT,"
            "%3 TEXT NOT NULL,"
            "%4 TEXT,"
            "%5 INTEGER)")
        .arg(tableName, COLUMN_ID, COLUMN_PATH, COLUMN_NAME, COLUMN_DURATION)
    };
    QSqlQuery query(m_db);
if (!query.exec(queryCreateTable)) {
    qDebug() << "Failed to create table:" << query.lastError().text();
} else {
    qDebug() << "Table created successfully!";
}
    query.exec(queryCreateTable);
}
