//
// Created by cww on 25-3-6.
//

#ifndef MUSICLISTBUTTON_H
#define MUSICLISTBUTTON_H
#include <QPushButton>


class MusicListButton final : public QPushButton {
  public:
    explicit MusicListButton(QWidget *parent = nullptr);

    [[nodiscard]] QStringList getMusicList() const;

    void setMusicList(const QStringList &list);

private:
      QStringList *m_list;
};



#endif //MUSICLISTBUTTON_H
