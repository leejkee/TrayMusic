//
// Created by cww on 25-3-12.
//

#ifndef SONG_H
#define SONG_H
#include <QString>

struct Song{
    QString name;
    QString path;
    int duration{};

    Song() = default;
    Song(QString name, QString path, const int duration) : name(std::move(name)), path(std::move(path)), duration(duration) {}
};
#endif //SONG_H
