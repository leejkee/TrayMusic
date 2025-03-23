//
// Created by cww on 25-2-19.
//

#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H
#include <QWidget>

class QGroupBox;
class QLabel;
class QSlider;
class QPushButton;

class VolumeWidget final : public QWidget {
public:
    explicit VolumeWidget(QWidget *parent = nullptr);

    void loadDefaultSetting() const;

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
    static QString convertSecondsToTime(int seconds);

    QPushButton *m_pushButtonPlay;
    QLabel *m_labelMusicFileName;
    QPushButton *m_pushButtonPre;
    QPushButton *m_pushButtonNext;
    VolumeWidget *m_volumeWidget;
    QPushButton *m_pushButtonVolume;
    QMenu *m_menuVolume;
    ProgressBarWidget *m_progressWidget;

private:
    void createConnections();

    void setButtonVisible(bool b);

    void showVolumeSlider();

public Q_SLOTS:
    void setPlayButtonIcon(bool playStatus);

    void setVolumeCtrlButtonIcon(int volume);
};


#endif
