//
// Created by cww on 25-2-28.
//
#ifndef SETTINGS_H
#define SETTINGS_H
#include <QLabel>
#include <QStringList>
#include <QString>

class Settings {
public:

#if defined (__linux__)
    const QString m_settingsPath{"../res/settings/init_linux.json"};
#elif defined (_WIN32)
    const QString m_settingsPath{"../res/settings/init.json"};
#endif

    Settings();

    void loadFromJson();

    void saveToJson();

    void addMusicDirectory(const QString &path);

    void removeMusicDirectory(const QString &path);


    [[nodiscard]] QStringList getMusicDirectories() const { return m_mp3Paths; }


    [[nodiscard]] QString getDatabaseDirectory() const { return m_dbPath; }


    [[nodiscard]] QStringList getUserMusicList() const { return m_userMusicList; }


    [[nodiscard]] float getDefaultVolume() const { return m_volume; }

private:
    QString m_dbPath;
    QStringList m_mp3Paths;
    QStringList m_userMusicList;
    float m_volume;
};


#endif //SETTINGS_H
