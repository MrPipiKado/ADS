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

QString merge(double arr[], int l, int m, int r)
{
    QString log = "";
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    double L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    // Initial index of first subarray
    int i = 0;

    // Initial index of second subarray
    int j = 0;

    // Initial index of merged subarray
    int k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    return log;
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
QString mergeSort(double arr[], int l, int r)
{
    QString log = "";
    if (l < r)
    {
        for(int i=l; i<=r; ++i)
            log+=QString::number(arr[i], 'f', 1) + " ";
        log+="\n";
        // Same as (l+r)/2, but avoids
        // overflow for large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        log+=mergeSort(arr, l, m);
        log+=mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
        for(int i=l; i<=r; ++i)
            log+=QString::number(arr[i], 'f', 1) + " ";
        log+="\n";
    }

    return log;
}

void MainWindow::on_pushButton_3_clicked()
{
    QString log = "";
    log = mergeSort(arr, 0, size-1);


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
