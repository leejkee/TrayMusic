//
// Created by cww on 25-2-22.
//

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#include <QWidget>


class MusicListManager;
class QGridLayout;
class QHBoxLayout;
class PlayerWidget;
class QListWidget;
class ViewWidget;
class QStackedWidget;
class Player;
class Settings;
class QPushButton;
class TopBarWidget;
class SettingsWidget;


class WindowManager final : public QWidget{
public:
    explicit WindowManager(QWidget *parent);
    ~WindowManager() override;

private:

    QStackedWidget *m_stackedWidget;
    ViewWidget* m_viewWidget;
    PlayerWidget* m_bottomWidget;
    MusicListManager* m_leftWidget;
    SettingsWidget *m_settingsWidget;
    TopBarWidget *m_topBarWidget;
    Player *m_player;
    Settings *m_settings;

    QHBoxLayout *m_viewLayout;
    void createConnections();

public slots:
    void showMainWidget();

    void showSettingsWidget();
};




#endif //WINDOWMANAGER_H
