//
// Created by cww on 25-2-19.
//

#ifndef PLAYERUI_H
#define PLAYERUI_H
#include <QWidget>

class QGroupBox;
class QLabel;
class QPushButton;
class QSlider;

class PlayerWidget final : public QWidget {

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    void changeMusicName(const QString& name);
    void setButtonVisible(bool b);

    QPushButton *pushButtonPlay;
    QLabel *labelMusicFileName;
    QPushButton *pushButtonPre;
    QPushButton *pushButtonNext;
    QPushButton *volumeCtrlButton;
    QSlider *volumeSlider;

public Q_SLOTS:
    void setPlayButtonIcon(bool playStatus);
    void setVolumeCtrlButtonIcon(int volume);


};



#endif //PLAYERUI_H
