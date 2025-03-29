//
// Created by cww on 25-2-22.
//

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#include <QWidget>


class QSplitter;
class MusicListWidget;
class QGridLayout;
class PlayerWidget;
class QListWidget;
class ViewWidget;
class QStackedWidget;
class Player;
class Settings;
class QPushButton;
class TopBarWidget;
class LocalMusicSettingsWidget;


class WindowManager final : public QWidget{
public:
    explicit WindowManager(QWidget *parent);
    ~WindowManager() override;

private:
    QStackedWidget *m_stackedWidget;
    ViewWidget* m_viewWidget;
    PlayerWidget* m_bottomWidget;
    MusicListWidget* m_leftWidget;
    LocalMusicSettingsWidget *m_settingsWidget;
    TopBarWidget *m_topBarWidget;
    Player *m_player;
    QSplitter *m_leftViewSplitter;
    void createConnections();

public slots:
    void showMainWidget();

    void showSettingsWidget();

};




#endif //WINDOWMANAGER_H
