#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <chrono>
#include <QtCharts>

using namespace std::chrono;
void callSort(int *array, int size, int i);

QString MainWindow::methods[METHODS_COUNT] = {"Bubble sort", "Selection sort",
                                              "Shell sort", "Merge sort", "Quick sort", "Count sort"};
int MainWindow::sizes[SIZES_COUNT] = {0};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table = ui->table;
    initializeCounts();
    initializeTable();
    arrays = new int*[METHODS_COUNT];
}

MainWindow::~MainWindow()
{
    delete ui;
    delete [] arrays;
}

void MainWindow::initializeTable(){
    table->setRowCount(METHODS_COUNT);
    table->setColumnCount(SIZES_COUNT);

    for(int i = 0; i < SIZES_COUNT; i++){
        table->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::number(sizes[i])));
    }

    for(int i = 0; i < METHODS_COUNT; i++){
        table->setVerticalHeaderItem(i, new QTableWidgetItem(methods[i]));
    }
}

void MainWindow::initializeCounts(){
    int n = 1024;
    for(int i = 0; i < SIZES_COUNT; i++){
        sizes[i] = n;
        n *= 4;
    }
}

void swap(int &a, int &b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int *array, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(array[i] > array[i+1]){
                swap(array[i], array[i+1]);
            }
        }
    }
}

void selectionSort(int *array, int size){
    int *min;
    QString str = "";
    for(int i = 0; i < size; i++){
        min = &array[i];
        for(int j = i; j < size; j++){
            if(array[j] < *min){
                min = &array[j];
            }
        }
        swap(array[i], *min);
    }
}

void shellSort(int *array, int size) {
    for (int gap = size/2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i += 1) {
            int temp = array[i];
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

void merge(int *array, int left, int middle, int right){
    int size_1 = middle - left + 1;
    int size_2 = right - middle;
    double *tempArray_1 = new double[size_1];
    double *tempArray_2 = new double[size_2];

    for(int i = 0; i < size_1; i++){
        tempArray_1[i] = array[left+i];
    }
    for(int j = 0; j < size_2; j++){
        tempArray_2[j] = array[middle + 1 + j];
    }
    int i, j;
    i = j = 0;
    int k = left;

    while (i < size_1 && j < size_2) {
        if(tempArray_1[i] <= tempArray_2[j]){
            array[k] = tempArray_1[i];
            i++;
        } else {
            array[k] = tempArray_2[j];
            j++;
        }
        k++;
    }

    while(i < size_1){
        array[k] = tempArray_1[i];
        i++;
        k++;
    }

    while(j < size_2){
        array[k] = tempArray_2[j];
        j++;
        k++;
    }

    delete [] tempArray_1;
    delete [] tempArray_2;
}

void mergeSort(int *array, int left, int right){
    if (left < right){
        int middle = (left + right) / 2;
        mergeSort(array, left, middle);
        mergeSort(array, middle+1, right);
        merge(array, left, middle, right);
    }
}

void quickSort(int *array, int first, int last){
    if (first == last) {
        return;
    }
    int m = array[(first + last) / 2];
    int i = first, j = last;
    while (i <= j) {
        while (array[i] < m) {
            i++;
        }
        while (array[j] > m){
            j--;
        }
        if (i <= j) {
            swap(array[i], array[j]);
            i++;
            j--;
        }
    }
    if (j > first) {
        quickSort(array, first, j);

    }
    if (last > i){
        quickSort(array, i, last);

    }
}

void countSort(int *array, int size) {
    int min  = array[0], max = array[0];

    for(int i = 1; i < size; i++){
        if(array[i]<min){
            min = array[i];
        }
        else if(array[i]>max){
            max = array[i];
        }
    }

    int tempSize = max - min +1;
    int *temp = new int[tempSize];

    for(int i = 0; i < tempSize;i++){
        temp[i] = 0;
    }
    for(int i = 0; i < size; i++){
        temp[array[i] - min]++;
    }

    for(int i = min, j = 0; i<=max;i++){
        while(temp[i - min]-- > 0){
            array[j++] = i;
        }
    }
    delete [] temp;
}

void callSort(int *array, int size, int i){
    switch (i) {
    case 0:
        bubbleSort(array, size);
        break;
    case 1:
        selectionSort(array, size);
        break;
    case 2:
        shellSort(array, size);
        break;
    case 3:
        mergeSort(array, 0, size-1);
        break;
    case 4:
        quickSort(array, 0, size-1);
        break;
    case 5:
        countSort(array, size);
        break;
    }
}

void MainWindow::on_sort_clicked()
{
    for(int k = 0; k < SIZES_COUNT; k++){
        randData = new int[sizes[k]];

        for(int i = 0; i < sizes[k]; i++){
            randData[i] = rand() % 1000;
        }
        times = new double*[METHODS_COUNT];

        for(int i = 0; i < METHODS_COUNT; i++){
            arrays[i] = new int[sizes[k]];
            times[i] = new double[SIZES_COUNT];
            for(int j = 0; j < sizes[k]; j++){
                arrays[i][j] = randData[j];
            }
        }
        int i = k < 4 ? 0 : 2;
        while(i < METHODS_COUNT){
                const auto begin = high_resolution_clock::now();
                callSort(arrays[i], sizes[k], i);
                auto end = high_resolution_clock::now() - begin;
                table->setItem(i, k, new QTableWidgetItem(QString::number(duration<double, std::milli>(end).count())));
                i++;
        }
        delete [] randData;
        for(int i = 0; i < METHODS_COUNT; i++){
            delete [] arrays[i];
        }
    }

    for(int i = 0; i < METHODS_COUNT; i++){
        for(int j = 0; j < SIZES_COUNT; j++){
            if (table->item(i, j) != nullptr){
                times[i][j] = table->item(i, j)->text().toDouble();
            } else {
                times[i][j] = 10000;
            }
        }
    }
    buildChart();
    buildDiagram();
}

void MainWindow::buildChart(){
    QChart *chart = new QChart();
    chart->legend()->setVisible(true);

    QLineSeries **series = new QLineSeries* [METHODS_COUNT];

    for(int i = 0; i < METHODS_COUNT; i++){
        series[i] = new QLineSeries;
        series[i]->setName(methods[i]);
        for(int j = 0; j < SIZES_COUNT; j++){
            series[i]->append(j, times[i][j]);
        }
        chart->addSeries(series[i]);
    }

    chart->createDefaultAxes();
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    for(int i = 0; i < SIZES_COUNT; i++){
        axis->append(QString::number(sizes[i]));
    }

    chart->setAxisX(axis, series[0]);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->graph->addWidget(chartView);
}

void MainWindow::buildDiagram() {
    QBarSet *set1 = new QBarSet("1024");
    *set1<<times[0][2]<<times[1][2]<<times[2][2]<<times[3][2]<<times[4][2]<<times[5][2];
    QBarSeries *series = new QBarSeries();
    series->append(set1);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->setAnimationOptions(QChart::AllAnimations);

    QStringList categories;
    categories << "Bubble Sort" << "Selection Sort" << "Shell Sort" << "Merge Sort" << "Quick Sort" << "Count Sort";
    QBarCategoryAxis*axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    chart->legend()->setVisible(false);
    QChartView*chartView = new QChartView(chart);
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window,QRgb(0xffffff));
    pal.setColor(QPalette::WindowText,QRgb(0x404040));
    qApp->setPalette(pal);
    diagramLayout = new QGridLayout(ui->diagramWidget);
    diagramLayout->addWidget(chartView,0,0);
}
