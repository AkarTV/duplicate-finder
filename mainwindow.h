#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDir"

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
    void on_dir1_set_button_clicked();

    void on_dir2_set_button_clicked();

    void on_find_equal_button_clicked();

    void on_clear_button_clicked();

private:
    Ui::MainWindow *ui;
    QString username;
    QDir dir1;
    QDir dir2;
};
#endif // MAINWINDOW_H
