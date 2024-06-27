#ifndef NEWGAME_H
#define NEWGAME_H

#include <QWidget>

namespace Ui {
class newgame;
}

class newgame : public QWidget
{
    Q_OBJECT

public:
    explicit newgame(QWidget *parent = nullptr);
    Ui::newgame *ui;
    ~newgame();

private slots:

//private:

};

#endif // NEWGAME_H
