#ifndef DIALOGMAINBUTTONS_H
#define DIALOGMAINBUTTONS_H

#include <QDialog>

namespace Ui {
class DialogMainButtons;
}

class DialogMainButtons : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMainButtons(QWidget *parent = 0);
    ~DialogMainButtons();

private:
    Ui::DialogMainButtons *ui;
};

#endif // DIALOGMAINBUTTONS_H
