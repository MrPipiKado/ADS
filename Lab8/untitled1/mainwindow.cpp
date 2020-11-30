#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    delete [] arr;
    arr = new BOOK[arg1];
    size = arg1;
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setColumnCount(arg1);
}

void MainWindow::on_pushButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,
            tr("Open File"),"/home/user/ADS/Lab8", "Text file(*.txt)");
    if (!file.isEmpty())
    {
        QFile FILE(file);
        if(FILE.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream input(&FILE);
            QString tmp_str;
                ui->tableWidget->clear();
                ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                ui->tableWidget->setColumnCount(2);
                ui->tableWidget->setRowCount(size);
                for(int i = 0; i<size; ++i)
                {
                    input>>tmp_str;
                    arr[i].name=(tmp_str);
                    arr[i].price=rand()%100;
                    ui->tableWidget->setItem(i, 0,new QTableWidgetItem(arr[i].name));
                    ui->tableWidget->setItem(i, 1,new QTableWidgetItem(QString::number(arr[i].price)));
                }
            }
        FILE.close();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString log = " ";
    int i = 0;
    for(;i<size;++i)
    {
        log+=arr[i].name;
        log+=" ";
        if(ui->lineEdit->text()==arr[i].name)
        {
            ui->label->setText(QString::number(arr[i].price));
            ui->textEdit->setText(log);
            return;
        }
    }
    ui->label->setText("Not found");
                ui->textEdit->setText(log);
}
