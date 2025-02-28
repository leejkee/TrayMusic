//
// Created by cww on 25-2-28.
//
#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <QStringList>
#include <QString>

class Settings {

public:
    const QString m_settingsPath{":/settings/init.json"};
    Settings();
    void loadFromJson();
    void saveToJson();
    void addMusicDirectory(const QString &path);
    void removeMusicDirectory(const QString &path);

    [[nodiscard]] QStringList getMusicDirectories() const { return m_mp3Paths; }
    [[nodiscard]] QString getDatabaseDirectory() const { return m_dbPath; }
    [[nodiscard]] float getDefaultVolume() const{return m_volume;}

private:
    QString m_dbPath;
    QStringList m_mp3Paths;
    float m_volume;
};



#endif //SETTINGS_H
