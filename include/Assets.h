//
// Created by cww on 25-2-19.
//
#pragma once
#include <QString>

// namespace Res {
//
// const QString trayIconSVG(":/images/icon.svg");
// const QString logoSVG(":/images/logo.svg");
// const QString playIconSVG(":/images/play.svg");
// const QString pauseIconSVG(":/images/pause.svg");
// const QString preIconSVG(":/images/pre.svg");
// const QString nextIconSVG(":/images/next.svg");
// const QString volumeSVG(":/images/high-volume.svg");
// const QString volumeMuteSVG(":/images/no-volume.svg");
// const QString upSVG(":/images/up.svg");
// const QString downSVG(":/images/down.svg");
// const QString addSVG(":/images/add.svg");
// const QString adddSVG(":/images/addd.svg");
// const QString nextPageSVG(":/images/nextpage.svg");
// const QString backPageSVG(":/images/backpage.svg");
// const QString removeSVG(":/images/remove.svg");
// const QString localSVG(":/images/local.svg");
// const QString musicListSVG(":/images/list.svg");
// const QString settingSVG(":/images/setting.svg");
//
// };

namespace Res {
    inline const auto TrayIconSVG      = QStringLiteral(":/images/icon.svg");
    inline const auto LogoSVG          = QStringLiteral(":/images/logo.svg");
    inline const auto PlayIconSVG      = QStringLiteral(":/images/play.svg");
    inline const auto PauseIconSVG     = QStringLiteral(":/images/pause.svg");
    inline const auto PreIconSVG       = QStringLiteral(":/images/pre.svg");
    inline const auto NextIconSVG      = QStringLiteral(":/images/next.svg");
    inline const auto VolumeSVG        = QStringLiteral(":/images/high-volume.svg");
    inline const auto VolumeMuteSVG    = QStringLiteral(":/images/no-volume.svg");
    inline const auto UpSVG            = QStringLiteral(":/images/up.svg");
    inline const auto DownSVG          = QStringLiteral(":/images/down.svg");
    inline const auto AddSVG           = QStringLiteral(":/images/add.svg");
    inline const auto AdddSVG          = QStringLiteral(":/images/addd.svg");
    inline const auto NextPageSVG      = QStringLiteral(":/images/nextpage.svg");
    inline const auto BackPageSVG      = QStringLiteral(":/images/backpage.svg");
    inline const auto RemoveSVG        = QStringLiteral(":/images/remove.svg");
    inline const auto LocalSVG         = QStringLiteral(":/images/local.svg");
    inline const auto MusicListSVG     = QStringLiteral(":/images/list.svg");
    inline const auto SettingSVG       = QStringLiteral(":/images/setting.svg");
}

namespace User {
    inline const auto LINUX_SETTINGS_PATH = QStringLiteral("../res/settings/init_linux.json");
    inline const auto WIN_SETTINGS_PATH = QStringLiteral("../res/settings/init.json");
    inline const auto PLAY_ALL_KEY = QStringLiteral("Play All");
    inline const auto LOCAL_LIST_KEY = QStringLiteral("Local");
}
