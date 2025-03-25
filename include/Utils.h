//
// Created by cww on 25-3-25.
//

#ifndef UTILS_H
#define UTILS_H
#include <QFile>
#include <QDebug>

namespace Tools {

    inline QString readQSS(const QString &qssPath) {
        if (QFile file(qssPath); file.open(QFile::ReadOnly)) {
            QString qss = QString::fromUtf8(file.readAll()).trimmed();
            return std::move(qss);  // 避免不必要的拷贝
        }
        qWarning() << "Failed to load QSS file:" << qssPath;
        return {};
    }
}


#endif //UTILS_H
