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
        QTableWidgetItem *item1(ui->input_1->item(i,0));
        if (!item1)
        {
            ui->statusbar->showMessage("Fill Grid");
            return;
        }
        ui->input_1->item(i,0)->text().toDouble(&ok);
        if(!ok)
        {
            ui->statusbar->showMessage(QString("Can not convert item at %1 row to double").arg(i+1));
            return;
        }
        arr[i] = ui->input_1->item(i, 0)->text().toDouble();
    }
    size = ui->spinBox->text().toInt();
    ui->statusbar->showMessage("Grid saved");
}


void MainWindow::on_pushButton_2_clicked()
{
    size = ui->spinBox->text().toInt();
    for(int i = 0; i<size; ++i)
    {
        if(i%2)
            arr[i] = std::sqrt(std::abs(arr[i] - 10));
    }

    ui->input_2->clear();
    ui->input_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->setColumnCount(size);
    ui->input_2->setRowCount(1);
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
        arr[i] = -100. + (rand() / ( RAND_MAX / (100.+100.) ) );
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

void swap(double *xp, double *yp)
{
    double temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void MainWindow::on_pushButton_3_clicked()
{
    int i, j, min_idx;
    QString log = "";

    for (i = 0; i < size-1; ++i)
    {
        log+=QString("==================\n"
                     "=%1 Big iteration=\n"
                     "==================\n").arg(i+1);

        min_idx = i;
        for (j = i+1; j < size; ++j)
        if (arr[j] < arr[min_idx])
            min_idx = j;

        swap(&arr[min_idx], &arr[i]);
        for (j = 0; j < size; ++j)
            log+=QString::number(arr[j], 'f', 1) + " | ";
        log+="\n";
    }
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
