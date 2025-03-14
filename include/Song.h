//
// Created by cww on 25-3-12.
//

#ifndef SONG_H
#define SONG_H
#include <QDir>
#include <QString>

class Song {
public:
    Song() = default;

    Song(const Song &song) = default;

    Song(QString name, QString path, const int duration) : name(std::move(name)), path(std::move(path)),
                                                           duration(duration) {
    }

    explicit Song(const QString &file);

    [[nodiscard]] int getDuration() const {
        return duration;
    }

    [[nodiscard]] QString getName() const {
        return name;
    }

    [[nodiscard]] QString getPath() const {
        return path;
    }

    static QString removeSuffix(const QString &str);

    static int musicLength(const QString &path);

private:
    QString name;
    QString path;
    int duration{};
};
#endif //SONG_H
