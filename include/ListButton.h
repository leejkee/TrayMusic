//
// Created by cww on 25-3-6.
//

#ifndef MUSICLISTBUTTON_H
#define MUSICLISTBUTTON_H
#include <QPushButton>


class ListButton final : public QPushButton {
    Q_OBJECT

public:
    explicit ListButton(const QString &name, QWidget *parent = nullptr);

signals:
    void signalButtonClicked(const QString &listName);

private Q_SLOTS:
    void onButtonClicked() {
        emit signalButtonClicked(m_listName);
    }

private:
    QString m_listName;
};


#endif //MUSICLISTBUTTON_H
