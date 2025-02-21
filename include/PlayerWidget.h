//
// Created by cww on 25-2-19.
//

#ifndef PLAYERUI_H
#define PLAYERUI_H
#include <QWidget>

#include "MainWindow.h"

class QGroupBox;
class QLabel;
class QSlider;
class QPushButton;
class QToolButton;

class VolumeWidget final : public QWidget {
public:
    explicit VolumeWidget(QWidget *parent = nullptr);
    QSlider *sliderV;
    QLabel *labelVolume;
    QPushButton *buttonMute;
};

class PlayerWidget final : public QWidget {
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    void changeMusicName(const QString& name);
    void setButtonVisible(bool b);
    void show();

    QPushButton *pushButtonPlay;
    QLabel *labelMusicFileName;
    QPushButton *pushButtonPre;
    QPushButton *pushButtonNext;
    VolumeWidget *volumeWidget;
    QPushButton *pushButtonVolume;
    QMenu *menuVolume;

public Q_SLOTS:
    void setPlayButtonIcon(bool playStatus);
    void setVolumeCtrlButtonIcon(int volume);
};




#endif //PLAYERUI_H
