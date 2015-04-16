#include "dialogmainbuttons.h"
#include "ui_dialogmainbuttons.h"

DialogMainButtons::DialogMainButtons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMainButtons)
{
    ui->setupUi(this);
}

DialogMainButtons::~DialogMainButtons()
{
    delete ui;
}
