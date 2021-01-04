#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comparison_binary.h"
#include "QFileDialog"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(qgetenv("USER").isEmpty())
        username = qgetenv("USERNAME"); //get OS username
    ui->equal_list->setStyleSheet( "QListWidget::item { border-bottom: 1px solid black; } " );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dir1_set_button_clicked()
{
    QString dir1_path = QFileDialog::getExistingDirectory(this, "Choose the directory", QString("C:/Users/%1/Desktop").arg(username) , QFileDialog::ReadOnly);
    dir1.setPath(dir1_path);
    ui->dir1_path_label->setText(dir1_path);
}

void MainWindow::on_dir2_set_button_clicked()
{
    QString dir2_path = QFileDialog::getExistingDirectory(this, "Choose the directory", QString("C:/Users/%1/Desktop").arg(username) , QFileDialog::ReadOnly);
    dir2.setPath(dir2_path);
    ui->dir2_path_label->setText(dir2_path);
}

#include "QDebug"
void MainWindow::on_find_equal_button_clicked()
{
    if(ui->dir1_path_label->text().isEmpty() || ui->dir2_path_label->text().isEmpty())
        QMessageBox::critical(this, "Doesn't choosed directory!", "Please set both directories");
    else
    {
        unsigned start_time = clock();
        Comparison_binary binary_list(dir1, dir2);
        QStringList list_of_equals = binary_list.get_equals();
        unsigned end_time = clock();
        unsigned search_time = end_time - start_time;
        qDebug()<<QString::number(search_time);
        if(list_of_equals.isEmpty())
            ui->result_label->setText("No equal files");
        else
        {
            QStringList::ConstIterator i = list_of_equals.constBegin();
            for( ; i != list_of_equals.constEnd(); ++i)
                ui->equal_list->addItem(*i);
            ui->result_label->setText(QString::number(binary_list.get_total_counter()) + " files found");
        }
    }
}

void MainWindow::on_clear_button_clicked()
{
    ui->equal_list->clear();
    ui->result_label->clear();
    ui->dir1_path_label->clear();
    ui->dir2_path_label->clear();
}
