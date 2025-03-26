//
// Created by cww on 25-3-12.
//

#ifndef SONG_H
#define SONG_H
#include <QString>
#include <utility>

class Song {
public:
    Song() = default;

    Song(const Song &song) = default;

    Song(QString fullName, QString path, const int duration): m_fullName(std::move(fullName)), m_path(std::move(path)), m_duration(duration) {}

    explicit Song(const QString &songFilePath);

    [[nodiscard]] int getDuration() const {
        return m_duration;
    }

    [[nodiscard]] QString getFullName() const {
        return m_fullName;
    }

    [[nodiscard]] QString getPath() const {
        return m_path;
    }

    static QString removeSuffix(const QString &str);



private:
    QString m_fullName;
    QString m_path;
    int m_duration{};



    ///
    /// @param path should be the @m_path
    /// @return the length of this music(Format: 00:00)
    static int musicLength(const QString &path);
};
#endif //SONG_H
