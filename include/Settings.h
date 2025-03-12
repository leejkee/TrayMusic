//
// Created by cww on 25-2-28.
//
#ifndef SETTINGS_H
#define SETTINGS_H
#include <QStringList>
#include <QString>

class Settings {
public:
    static Settings &instance() {
        static Settings settingsInstance;
        return settingsInstance;
    }

    Settings(const Settings &) = delete;

    Settings &operator=(const Settings &) = delete;

    Settings(Settings &&) = delete;

    Settings &operator=(Settings &&) = delete;

    void loadFromJson();

    void saveToJson();

    void addMusicDirectory(const QString &path);

    void removeMusicDirectory(const QString &path);


    [[nodiscard]] QStringList getLocalMusicDirectories() const { return m_localMusicPaths; }


    [[nodiscard]] QString getDatabaseDirectory() const { return m_dbPath; }


    [[nodiscard]] QStringList getUserMusicList() const { return m_userMusicList; }


    [[nodiscard]] float getDefaultVolume() const { return m_volume; }

private:
#if defined (__linux__)
    const QString m_settingsPath{"../res/settings/init_linux.json"};
#elif defined (_WIN32)
    const QString m_settingsPath{"../res/settings/init.json"};
#endif

    QString m_dbPath;
    QStringList m_localMusicPaths;
    QStringList m_userMusicList;
    float m_volume{};

    Settings() {
    }

    ~Settings() = default;
};


#endif //SETTINGS_H
