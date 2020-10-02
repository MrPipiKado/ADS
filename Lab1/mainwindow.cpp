#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->input_1->clear();
    ui->input_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->setHorizontalHeaderItem(0, new QTableWidgetItem("Title"));
    ui->input_1->setHorizontalHeaderItem(1, new QTableWidgetItem("Price"));
    ui->input_1->setColumnCount(2);

    ui->input_2->clear();
    ui->input_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->setHorizontalHeaderItem(0, new QTableWidgetItem("Title"));
    ui->input_2->setHorizontalHeaderItem(1, new QTableWidgetItem("Price"));
    ui->input_2->setColumnCount(2);

    ui->output_1->clear();
    ui->output_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->output_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->output_1->setHorizontalHeaderItem(0, new QTableWidgetItem("Title"));
    ui->output_1->setHorizontalHeaderItem(1, new QTableWidgetItem("Price"));
    ui->output_1->setColumnCount(2);

    arr = nullptr;
    filtred_arr_1 = nullptr;
    filtred_arr_2 = nullptr;
    size = 0;
    filtred_size = 0;
    avg = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_count_valueChanged(int arg1)
{
    ui->input_1->setRowCount(arg1);
    delete [] arr;
    arr = new Product[arg1];
}

void MainWindow::on_pushButton_2_clicked()
{// click on enter
    bool ok = true;
    avg = 0;
    if(!arr)
    {
        ui->statusbar->showMessage("Fill Grid");
        return;
    }

    for(int i = 0; i<ui->count->text().toInt(); ++i)
    {
        QTableWidgetItem *item1(ui->input_1->item(i,0));
        QTableWidgetItem *item2(ui->input_1->item(i,1));
        if (!item1 || !item2)
        {
            ui->statusbar->showMessage("Fill Grid");
            return;
        }
        ui->input_1->item(i,1)->text().toDouble(&ok);
        if(!ok)
        {
            ui->statusbar->showMessage(QString("Can not convert item at %1 row to double").arg(i+1));
            return;
        }
        arr[i].setTitle(ui->input_1->item(i, 0)->text().toStdString());
        arr[i].setPrice(ui->input_1->item(i, 1)->text().toDouble());
        avg += arr[i].getPrice();
    }
    size = ui->count->text().toInt();
    avg /= size;
    ui->statusbar->showMessage("Grid saved");
    ui->avg_lable->setText(QString("%1").arg(avg));
}

void MainWindow::on_pushButton_3_clicked()
{//click on filter
    filtred_size = 0;
    delete [] filtred_arr_1;
    delete [] filtred_arr_2;
    filtred_arr_1 = new Product[size];
    filtred_arr_2 = new Product[size];
    for(int i = 0; i < size; ++i)
    {
        if(arr[i].getPrice()<avg)
        {
            filtred_arr_1[filtred_size].setPrice(arr[i].getPrice());
            filtred_arr_2[filtred_size].setPrice(arr[i].getPrice());

            filtred_arr_1[filtred_size].setTitle(arr[i].getTitle());
            filtred_arr_2[filtred_size++].setTitle(arr[i].getTitle());
        }
    }
    ui->input_2->clear();
    ui->input_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->setHorizontalHeaderItem(0, new QTableWidgetItem("Title"));
    ui->input_2->setHorizontalHeaderItem(1, new QTableWidgetItem("Price"));
    ui->input_2->setColumnCount(2);
    ui->input_2->setRowCount(filtred_size);
    for(int i = 0; i < filtred_size; ++i)
    {
        ui->input_2->setItem(i, 0,new QTableWidgetItem(QString::fromStdString(filtred_arr_1[i].getTitle())));
        ui->input_2->setItem(i, 1,new QTableWidgetItem(QString::number(filtred_arr_1[i].getPrice())));
    }
}

void MainWindow::on_pushButton_clicked()
{//read from file
    QString file = QFileDialog::getOpenFileName(this,
            tr("Open File"),"/home/user/ADS/Lab1", "Text file(*.txt)");
    if (!file.isEmpty())
    {
        QFile FILE(file);
        if(FILE.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream input(&FILE);
            QString tmp_str;
            double tmp_db;
                input>>size;
                ui->count->setValue(size);
                delete [] arr;
                arr = new Product[size];
                avg = 0;
                ui->input_1->clear();
                ui->input_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                ui->input_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                ui->input_1->setHorizontalHeaderItem(0, new QTableWidgetItem("Title"));
                ui->input_1->setHorizontalHeaderItem(1, new QTableWidgetItem("Price"));
                ui->input_1->setColumnCount(2);
                ui->input_1->setRowCount(size);
                for(int i = 0; i<size; ++i)
                {
                    input>>tmp_str>>tmp_db;
                    arr[i].setTitle(tmp_str.toStdString());
                    arr[i].setPrice(tmp_db);
                    avg += arr[i].getPrice();
                    ui->input_1->setItem(i, 0,new QTableWidgetItem(QString::fromStdString(arr[i].getTitle())));
                    ui->input_1->setItem(i, 1,new QTableWidgetItem(QString::number(arr[i].getPrice())));
                }
                avg/=size;
            }
        ui->statusbar->showMessage(QString("Grid loaded from %1").arg(file));
        ui->avg_lable->setText(QString("%1").arg(avg));
        FILE.close();
    }
}

QString Bubble(Product *arr, int size, double & time)
{
    const auto begin = std::chrono::high_resolution_clock::now();
    Product tmp;
    QString log = "";
    for(int i = 0; i < size; ++i)
    {
        log+=QString("==================\n"
                     "=%1 Big iteration=\n"
                     "==================\n").arg(i+1);
        for(int j = 0; j < size-1; ++j)
        {
            if(arr[j].getTitle() > arr[j+1].getTitle())
            {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
            log+=QString::fromStdString(arr[j].getTitle()) +
                    " " + QString::number(arr[j].getPrice()) + "\n";
        }
        log+=QString::fromStdString(arr[size-1].getTitle()) +
                " " + QString::number(arr[size-1].getPrice()) + "\n";
    }
    auto end = std::chrono::high_resolution_clock::now() - begin;
    time = std::chrono::duration<double, std::milli>(end).count();
    return log;
}

QString BubbleFlag(Product *arr, int size, double & time)
{
    const auto begin = std::chrono::high_resolution_clock::now();
    bool flag = false;
    Product tmp;
    QString log = "";
    for(int i = 0; i < size; ++i)
    {
        flag = false;
        log+=QString("==================\n"
                     "=%1 Big iteration=\n"
                     "==================\n").arg(i+1);
        for(int j = 0; j < size-1; ++j)
        {
            if(arr[j].getTitle() > arr[j+1].getTitle())
            {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                flag = true;
            }
            log+=QString::fromStdString(arr[j].getTitle()) +
                    " " + QString::number(arr[j].getPrice()) + "\n";
        }
        log+=QString::fromStdString(arr[size-1].getTitle()) +
                " " + QString::number(arr[size-1].getPrice()) + "\n";
        if(!flag)
            break;
    }
    auto end = std::chrono::high_resolution_clock::now() - begin;
    time = std::chrono::duration<double, std::milli>(end).count();
    return log;
}

void MainWindow::on_pushButton_4_clicked()
{
    double BS_time, BSF_time;
    ui->BS->setText(Bubble(filtred_arr_1, filtred_size, BS_time));
    ui->BSF->setText(BubbleFlag(filtred_arr_2, filtred_size, BSF_time));

    ui->output_1->setColumnCount(2);
    ui->output_1->setRowCount(filtred_size);
    for (int i = 0; i < filtred_size; ++i)
    {
        ui->output_1->setItem(i, 0,new QTableWidgetItem(QString::fromStdString(filtred_arr_1[i].getTitle())));
        ui->output_1->setItem(i, 1,new QTableWidgetItem(QString::number(filtred_arr_1[i].getPrice())));
    }

    ui->time_1->setText(QString::number(BS_time));
    ui->time_2->setText(QString::number(BSF_time));
}
