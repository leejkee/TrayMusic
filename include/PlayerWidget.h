//
// Created by cww on 25-2-19.
//

#ifndef PLAYERUI_H
#define PLAYERUI_H
#include <QWidget>

class QGroupBox;
class QLabel;
class QSlider;
class QPushButton;
class QToolButton;

class VolumeWidget final : public QWidget {
public:
    explicit VolumeWidget(QWidget *parent = nullptr);
    QSlider *m_sliderV;
    QLabel *m_labelVolume;
    QPushButton *m_buttonMute;
};

class ProgressBarWidget final : public QWidget {
    Q_OBJECT
public:
    explicit ProgressBarWidget(QWidget *parent = nullptr);

    QSlider *m_sliderP;
    QLabel *m_labelLeft;
    QLabel *m_labelRight;
    bool m_isUpdatingSlider;


public Q_SLOTS:
    void updateLabelR();

    void updateSliderPosition(qint64 position);

    void updateLabelL(qint64 duration);
};

class PlayerWidget final : public QWidget {
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    void changeMusicName(const QString& name);
    void setButtonVisible(bool b);
    void show();

    QPushButton *m_pushButtonPlay;
    QLabel *m_labelMusicFileName;
    QPushButton *m_pushButtonPre;
    QPushButton *m_pushButtonNext;
    VolumeWidget *m_volumeWidget;
    QPushButton *m_pushButtonVolume;
    QMenu *m_menuVolume;
    ProgressBarWidget *m_progressWidget;

public Q_SLOTS:
    void setPlayButtonIcon(bool playStatus);
    void setVolumeCtrlButtonIcon(int volume);
};




#endif //PLAYERUI_H
