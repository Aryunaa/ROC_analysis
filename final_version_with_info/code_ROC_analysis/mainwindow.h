#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QStandardItemModel>
class QAction;
class QActionGroup;
class QLabel;
class QMenu;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    double minfunc(double * list);
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    double maxfunc(double * list);
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *csvModel;
};
#endif // MAINWINDOW_H
