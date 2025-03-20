//
// Created by cww on 25-2-28.
//
#ifndef SETTINGS_H
#define SETTINGS_H
#include <QObject>
#include <QStringList>
#include "Assets.h"

class Settings final : public QObject {
    Q_OBJECT

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


    [[nodiscard]] QStringList getLocalMusicDirectories() const { return m_localMusicPaths; }


    [[nodiscard]] QString getDatabaseDirectory() const { return m_dbPath; }


    [[nodiscard]] QStringList getUserMusicList() const { return m_userMusicList; }


    [[nodiscard]] float getDefaultVolume() const { return m_volume; }


Q_SIGNALS:
    void signalSettingsChanged();

public Q_SLOTS:
    void addMusicDirectory(const QString &path);

    void removeMusicDirectory(const QString &path);

private:
#if defined (__linux__)
    const QString m_settingsPath{Constants::LINUX_SETTINGS_PATH};
#elif defined (_WIN32)
    const QString m_settingsPath{User::WIN_SETTINGS_PATH};
#endif

    QString m_dbPath;
    QStringList m_localMusicPaths;
    QStringList m_userMusicList;
    float m_volume{};

    Settings() {
    }

    ~Settings() override = default;
};


#endif //SETTINGS_H
