#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialogmainbuttons.h>
#include <misc.h>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Start_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButtonEject_clicked();

private:
    Ui::MainWindow *ui;

    Misc *deviceInfoList;
    QStringListModel *deviceInfoListModel;

    DialogMainButtons *dialog_StartJob;
    DialogMainButtons *dialog_StopJob;
    DialogMainButtons *dialog_eject;
};

#endif // MAINWINDOW_H
