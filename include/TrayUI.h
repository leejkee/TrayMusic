#ifndef TRAYUI_H
#define TRAYUI_H
#include <QMediaPlayer>

class QGroupBox;
class QLabel;
class QComboBox;
class QCheckBox;
class QMenu;
class QAction;
class QSystemTrayIcon;
class QWidget;
class QMainWindow;
class QMediaPlayer;
class QPushButton;
class TrayUI {
public:
    TrayUI();
    void setupUI(QMainWindow *parent);


    QGroupBox* iconGroupBox;
    QLabel* iconLabel;
    QComboBox* iconComboBox;
    QCheckBox* showIconCheckBox;
    QGroupBox *musicPlayerGroupBox;
    QAction* minimizeAction;
    QAction* maximizeAction;
    QAction* restoreAction;
    QAction* quitAction;
    QSystemTrayIcon *systemTrayIcon;
    QMenu *trayIconMenu;

    QPushButton *pushButtonPlay;
    QLabel *labelSongName;
    QPushButton *pushButtonLoadFile;

private:
    void createIconGroupBox();
    void createMusicPlayerGroupBox();
    void createActions(QWidget *parent);
    void createTrayIconMenu(QWidget *parent);
};

#endif