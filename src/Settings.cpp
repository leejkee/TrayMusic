//
// Created by cww on 25-2-28.
//
#include "Settings.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
Settings::Settings() {
    loadFromJson();
}


void Settings::loadFromJson() {
    QFile file(m_settingsPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file";
        return;
    }
    const QByteArray jsonData = file.readAll();
    file.close();
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qDebug() << "Failed to parse JSON";
        return;
    }
    QJsonObject json = jsonDoc.object();
    m_mp3Paths = json["MusicDirectory"].toVariant().toStringList();
    m_dbPath = json["DatabaseDirectory"].toString();
    m_volume = static_cast<float>(json["DefaultVolume"].toDouble());
};

void Settings::saveToJson() {
    QJsonObject jsonObj;
    jsonObj["MusicDirectory"] = QJsonArray::fromStringList(m_mp3Paths);
    jsonObj["DatabaseDirectory"] = QJsonValue(m_dbPath);
    jsonObj["DefaultVolume"] = QJsonValue(m_volume);
    const QJsonDocument doc(jsonObj);
    QFile file(m_settingsPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not write to JSON file:" << m_settingsPath;
        return;
    }
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}
void Settings::addMusicDirectory(const QString& path) {
    if (!m_mp3Paths.contains(path)) {
        m_mp3Paths.append(path);
        saveToJson();
    }
}

void Settings::removeMusicDirectory(const QString& path) {
    if (m_mp3Paths.removeOne(path)) {
        saveToJson();
    }
}