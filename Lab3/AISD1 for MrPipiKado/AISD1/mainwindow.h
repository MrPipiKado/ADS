#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <QString>
#include <QTableWidgetItem>
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
    void on_row_valueChanged(int arg1);

    void on_column_valueChanged(int arg1);

    void on_enter_clicked();

    void on_sort_clicked();

    void on_ramdom_clicked();

private:
    Ui::MainWindow *ui;

    double **matrix_1;
    double **matrix_2;
    int rows;
    int columns;
};
#endif // MAINWINDOW_H
