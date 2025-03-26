//
// Created by cww on 25-2-19.
//
#ifndef ICONWIDGET_H
#define ICONWIDGET_H
#include "Song.h"
#include <QStyledItemDelegate>

class QListView;
class QStringListModel;
class QLabel;
class QPainter;
class BetterButton;

class PlayListDelegate final : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit PlayListDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {
    }

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;


Q_SIGNALS:
    void playButtonClicked(const QModelIndex &index);

};


class ViewWidget final : public QWidget {
    Q_OBJECT

public:
    explicit ViewWidget(QWidget *parent = nullptr);

Q_SIGNALS:
    void signalViewDoubleClicked(int index);

    void signalPlayAllClicked(const QString &name);

private Q_SLOTS:
    void showContextMenu(const QPoint &pos);

    void handleAction(int index);

public Q_SLOTS:
    void viewDoubleClick(const QModelIndex &index);

    void updateCurrentIndex(int index);

    void showMusicList(const QString &listName) const;

    ///
    /// init function
    /// This function will set the default string list (Local Music List) for ViewWidget
    void setDefaultList() const;

    /// @brief Refreshes the view widget to reflect changes in the local music path.
    ///
    /// This function is intended to be called when the local music path has been updated
    /// while the local music is currently being displayed by the view widget. It ensures
    /// that the view widget is updated to reflect the new path, such as updating the displayed
    /// information or reloading the music file.
    ///
    /// @note This function should only be called when the view widget is actively displaying
    ///       local music.
    void refreshForLocalMusic() const;

private:
    QLabel *m_labelName;
    QListView *m_playListView;
    QStringListModel *m_playListModel;
    BetterButton *m_playAllButton;
    PlayListDelegate *m_viewItemDelegate;

    void createConnections();
};


#endif //ICONWIDGET_H
