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
    QPushButton *pushButtonLoadFile;
    QCheckBox* showIconCheckBox;

    QAction* minimizeAction;
    QAction* maximizeAction;
    QAction* restoreAction;
    QAction* quitAction;
    QSystemTrayIcon *systemTrayIcon;
    QMenu *trayIconMenu;

    QGroupBox *musicPlayerGroupBox;
    QPushButton *pushButtonPlay;
    QLabel *labelSongName;
    QPushButton *pushButtonPre;
    QPushButton *pushButtonNext;
    QPushButton *pushButtonSetVolume;
    const QString trayIconSVG;
    const QString playIconSVG;
    const QString pauseIconSVG;
    const QString preIconSVG;
    const QString nextIconSVG;


private:
    void createIconGroupBox();
    void createMusicPlayerGroupBox();
    void createActions(QWidget *parent);
    void createTrayIconMenu(QWidget *parent);
};

#endif