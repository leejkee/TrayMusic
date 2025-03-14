//
// Created by cww on 25-3-14.
//
#include "Song.h"
#include "taglib/fileref.h"

Song::Song(const QString &file) {
    if (const QFileInfo fileInfo(file); fileInfo.exists() && fileInfo.isFile()) {
        path = fileInfo.absoluteFilePath();
        name = removeSuffix(path);
        duration = musicLength(path);
    } else {
        path = "";
        name = "";
        duration = 0;
    }
}

QString Song::removeSuffix(const QString &str) {
    const auto s = str.right(str.size() - str.lastIndexOf("/") - 1);
    return s.left(s.indexOf("."));
}

int Song::musicLength(const QString &path) {
#if defined(_WIN32)
    const std::wstring tg_path = path.toStdWString();
#elif defined(__linux__)
    const std::string tg_path = path.toStdString();
#endif
    if (const TagLib::FileRef f(tg_path.c_str()); !f.isNull() && f.audioProperties()) {
        const TagLib::AudioProperties *properties = f.audioProperties();
        return properties->lengthInSeconds();
    }
    return {};
}
