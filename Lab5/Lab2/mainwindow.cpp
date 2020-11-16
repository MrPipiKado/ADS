#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(0));

    ui->input_1->clear();
    ui->input_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->setRowCount(1);

    ui->input_2->clear();
    ui->input_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->setRowCount(1);

    arr = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->input_1->setColumnCount(arg1);
    delete [] arr;
    arr = new double[arg1];
}


void MainWindow::on_pushButton_clicked()
{
    bool ok = true;
    if(!arr)
    {
        ui->statusbar->showMessage("Fill Grid");
        return;
    }

    for(int i = 0; i<ui->spinBox->text().toInt(); ++i)
    {
        QTableWidgetItem *item1(ui->input_1->item(0,i));
        if (!item1)
        {
            ui->statusbar->showMessage("Fill Grid");
            return;
        }
        ui->input_1->item(0,i)->text().toDouble(&ok);
        if(!ok)
        {
            ui->statusbar->showMessage(QString("Can not convert item at %1 row to double").arg(i+1));
            return;
        }
        arr[i] = ui->input_1->item(0, i)->text().toDouble();
    }
    size = ui->spinBox->text().toInt();
    ui->statusbar->showMessage("Grid saved");
}
#include <vector>
void MainWindow::on_pushButton_2_clicked()
{
    for (int i = 0; i < size; i++)
    {
       if(arr[i]<0)
           arr[i] = sin(arr[i]);
    }
        ui->input_2->setRowCount(1);
            ui->input_2->setColumnCount(size);
    for(int i = 0; i<size; ++i)
    {
        ui->input_2->setItem(0, i,new QTableWidgetItem(QString::number(arr[i], 'f', 1)));
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    size = ui->spinBox->text().toInt();
    for(int i = 0; i<size; ++i)
    {
        arr[i] = rand() % 25 + (rand() % 10) / 10. - 5;
    }

    ui->input_1->clear();
    ui->input_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->setColumnCount(size);
    ui->input_1->setRowCount(1);
    for(int i = 0; i<size; ++i)
    {
        ui->input_1->setItem(0, i,new QTableWidgetItem(QString::number(arr[i], 'f', 1)));
    }
}

void swap(double & a, double & b)
{
    double tmp = a;
    a=b;
    b=tmp;
}
QString quickSort(double arr[], int first, int last, int size)
{
    QString log = "";
    if (first == last) {
        return log;
    }
    double m = arr[(first + last) / 2];
    for (int i = 0; i<size; ++i)
        log +=QString::number(arr[i], 'f', 1) + " ";
    log+="   " + QString::number(m, 'f', 1) + "\n";
    int begin = first, end = last;
    while (begin <= end) {
        while (arr[begin] < m) {
            begin++;
        }
        while (arr[end] > m){
            end--;
        }
        if (begin <= end) {
            swap(arr[begin], arr[end]);
            begin++;
            end--;
        }
    }
    for (int i = 0; i<size; ++i)
        log +=QString::number(arr[i], 'f', 1) + " ";
    log+="   " + QString::number(m, 'f', 1) + "\n\n\n";
    if (end > first) {
        log+=quickSort(arr, first, end, size);
    }
    if (last > begin){
        log+=quickSort(arr, begin, last, size);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString log = "";
    log+=quickSort(arr, 0, size-1, size);


    ui->input_3->clear();
    ui->input_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_3->setColumnCount(size);
    ui->input_3->setRowCount(1);
    for(int i = 0; i<size; ++i)
    {
        ui->input_3->setItem(0, i,new QTableWidgetItem(QString::number(arr[i], 'f', 1)));
    }
    ui->textEdit->setText(log);
}
