//
// Created by cww on 25-2-28.
//

#ifndef MUSICLISTMANAGER_H
#define MUSICLISTMANAGER_H
#include <QWidget>
class MusicListButton;
class QVBoxLayout;
class QPushButton;
class QScrollArea;

class ButtonWidget final : public QWidget {
    Q_OBJECT

public:
    explicit ButtonWidget(QWidget *parent = nullptr);

    void addButton();

    void initUserListButton();

private:
    QVBoxLayout *m_layout;
};

class MusicListManager final : public QWidget {
    Q_OBJECT

public:
    explicit MusicListManager(QWidget *parent);

private Q_SLOTS:
    void toggleExpand();


private:
    MusicListButton *m_buttonLocalMusic;
    QPushButton *m_expandButton;
    QPushButton *m_addButton;
    QScrollArea *m_scrollArea;
    ButtonWidget *m_buttonWidget;

    void createConnections();
};


#endif //MUSICLISTMANAGER_H
