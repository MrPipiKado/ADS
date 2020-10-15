#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(0));
    ui->input->clear();
        ui->input->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->input->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        matrix_1 = nullptr;
        matrix_2 = nullptr;
        rows = 1;
        columns = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_row_valueChanged(int arg1)
{
    ui->input->setRowCount(arg1);

    rows = arg1;
}

void MainWindow::on_column_valueChanged(int arg1)
{
    ui->input->setColumnCount(arg1);
    columns = arg1;
}

void MainWindow::on_enter_clicked()
{
    columns = ui->column->text().toInt();
    rows = ui->row->text().toInt();
    matrix_1 = new double*[columns];
    for(int i = 0; i<columns; ++i)
    {
        matrix_1[i] = new double[rows];
    }
    for (int i=0; i< rows; ++i)
        for(int j=0; j<columns;++j)
        {
            matrix_1[j][i]=ui->input->item(i, j)->text().toDouble();
        }
    matrix_2 = new double*[columns];
    for(int i = 0; i<columns; ++i)
    {
        matrix_2[i] = new double[rows];
    }
    for (int i=0; i< rows; ++i)
        for(int j=0; j<columns;++j)
        {
            matrix_2[j][i]=ui->input->item(i, j)->text().toDouble();
        }
}
QString print_matrix(double ** matrix, int rows, int columns, int iteration, double tmp)
{
    QString printing = "Itaration "+ QString::number(iteration+1)+ " tmp was: "+ QString::number(tmp) + "\n";
    for(int j=0; j<rows;++j)
    {
    for (int i=0; i< columns; ++i)

        {
           printing +=QString::number(matrix[i][j], 'f', 2)+" ";
        }
      printing +=  "\n";
    }
    return printing;


}

QString Shell(double** matrix, int column,int rows,  double & time)
{
    QString log = "";
    int count = 0;
    const auto begin = std::chrono::high_resolution_clock::now();
    for (int gap = column/2; gap > 0; gap /= 2)
        {
            // Do a gapped insertion sort for this gap size.
            // The first gap elements a[0..gap-1] are already in gapped order
            // keep adding one more element until the entire array is
            // gap sorted
            for (int i = gap; i < column; i += 1)
            {
                // add a[i] to the elements that have been gap sorted
                // save a[i] in temp and make a hole at position i
                double temp = matrix[i][0];
                double *tmp_ptr = matrix[i];

                // shift earlier gap-sorted elements up until the correct
                // location for a[i] is found
                int j;
                for (j = i; j >= gap && matrix[j - gap][0] > temp; j -= gap)
                    matrix[j] = matrix[j - gap];

                //  put temp (the original a[i]) in its correct location
                matrix[j] = tmp_ptr;

                log+=print_matrix(matrix, rows, column, count, temp) + "\n";
                count++;
            }
        }

    auto end = std::chrono::high_resolution_clock::now() - begin;
    time = std::chrono::duration<double, std::milli>(end).count();
    return log;
}

void MainWindow::on_sort_clicked()
{
    double time_1, time_2;
    ui->output->clear();
        ui->output->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->output->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->output->setColumnCount(columns);
        ui->output->setRowCount(rows);
        ui->textEdit->setText(Shell(matrix_1, columns, rows,time_1)+"Time " + QString::number(time_1)+"mls");

        for(int j=0; j<rows;++j)
    for (int i=0; i< columns; ++i)

        {
             ui->output->setItem(j, i,new QTableWidgetItem(QString::number(matrix_1[i][j], 'f', 2)));
        }
}
double randoming()
{
   return -100. + (rand() / ( RAND_MAX / (200.) ) );
}

void MainWindow::on_ramdom_clicked()
{
    srand(static_cast<unsigned int>(clock()));
    ui->input->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input->setColumnCount(columns);
    ui->input->setRowCount(rows);

    for(int j=0; j<rows;++j)
for (int i=0; i< columns; ++i)

   {
        ui->input->setItem(j, i,new QTableWidgetItem(QString::number(randoming(), 'f', 2)));
   }
}
