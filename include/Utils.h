//
// Created by cww on 25-3-25.
//

#ifndef UTILS_H
#define UTILS_H
#include <QFile>
#include <QDebug>
#include <QRandomGenerator>


namespace Tools {

    inline QString readQSS(const QString &qssPath) {
        if (QFile file(qssPath); file.open(QFile::ReadOnly)) {
            QString qss = QString::fromUtf8(file.readAll()).trimmed();
            file.close();
            return std::move(qss);  // 避免不必要的拷贝
        }
        qWarning() << "Failed to load QSS file:" << qssPath;
        return {};
    }

    template <class T>
    T getRandomItem(const QList<T> &list) {
        if (!list.isEmpty()) {
            static QList<T> savedList = list;
            if (savedList.isEmpty()) {
                savedList = list;
            }
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, savedList.size() - 1);
            auto num = dis(gen);
            auto item = savedList.at(num);
            savedList.remove(num);
            return item;
        }
        qDebug() << "getRandomItem" << "list is empty";
        return {};
    }
}


#endif //UTILS_H
