//
// Created by cww on 25-2-22.
//

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QWidget>

#include "Player.h"
#include "Settings.h"

class MusicListManager;
class QGridLayout;
class QHBoxLayout;
class PlayerWidget;

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
