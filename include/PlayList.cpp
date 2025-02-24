//
// Created by cww on 25-2-23.
//
#include "PlayList.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

void PlayList::initDB(const QString& dbname) {
  if (m_db.isOpen()) {
    return;
  }
  m_db = QSqlDatabase::addDatabase("QSQLITE", dbname);
  if (!m_db.open()) {
    qDebug() << "Failed to open database" << m_db.lastError().text();
    return;
  }
}

void PlayList::saveListToDB(const QStringList& list, const QString& tableName) {
  if (!m_db.isOpen()) {
    qDebug() << "Failed to open database" << m_db.lastError().text();
    return;
  }
  if (! (m_db.tables().contains(tableName)) ) {
    qDebug() << "Table " << tableName << " not found";
    return;
  }
  // create table and add list to table
  QString queryCreateTable{QString("CREATE TABLE %1 ("
  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
  "path TEXT NOT NULL,"
  "name TEXT,"
  "artist TEXT,"
  "album TEXT,"
  "duration INTEGER)").arg(tableName)};

  QSqlQuery query;
  query.exec(queryCreateTable);

  query.prepare(QString("INSERT INTO %1 (song_path) VALUES (?)").arg(tableName));

  // 插入每个路径到表中
  for (const QString& songPath : list) {
    query.addBindValue(songPath);
    if (!query.exec()) {
      qDebug() << "Error inserting song:" << query.lastError();
      return;  // 如果插入失败，退出函数
    }
  }

  qDebug() << "Songs successfully saved to the table " << tableName;



}

void PlayList::loadMusicFromDirectory(const QString& path) {

}