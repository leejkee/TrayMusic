//
// Created by cww on 25-2-22.
//

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QPushButton>
#include <QWidget>

#include "Player.h"
#include "Settings.h"

class MusicListManager;
class QGridLayout;
class QHBoxLayout;
class PlayerWidget;
class QListWidget;


class SettingsWidget final: public QWidget {

public:
    explicit SettingsWidget(QWidget *parent = nullptr);

private:
    QPushButton *addBtn;
    QPushButton *removeBtn;
    QListWidget *listWidget;
};

class WindowManager final : public QWidget{
public:
    explicit WindowManager(const Settings *settings, QWidget *parent);

    ~WindowManager() override;


private:
    QWidget* m_mainWidget;
    PlayerWidget* m_buttonWidget;
    MusicListManager* m_leftWidget;
    QWidget *m_switchWidget;

    QHBoxLayout *m_viewLayout;
    Player *m_player;
    void createConnections();
    void showMainWidget();
    void showOtherWidget(QWidget *widget);
    void setBottomWidget(QWidget *widget);
};





#endif //WINDOWMANAGER_H
