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

    QStackedWidget *m_stackedWidget;
    ViewWidget* m_viewWidget;
    PlayerWidget* m_bottomWidget;
    MusicListManager* m_leftWidget;
    SettingsWidget *m_settingsWidget;
    TopBarWidget *m_topBarWidget;
    Player *m_player;

    QHBoxLayout *m_viewLayout;
    void createConnections();

public slots:
    void showMainWidget();

    void showSettingsWidget();
};





#endif //WINDOWMANAGER_H
