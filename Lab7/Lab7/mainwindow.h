#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QMainWindow>
#include <QTableWidget>

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
    void on_sort_clicked();

private:
    Ui::MainWindow *ui;
    QTableWidget *table;
    QGridLayout *diagramLayout;
    enum {SIZES_COUNT = 7, METHODS_COUNT = 6};
    static int sizes[SIZES_COUNT];
    static QString methods[METHODS_COUNT];
    int **arrays;
    double **times;
    int *randData;
    void initializeTable();
    static void initializeCounts();
    void buildChart();
    void buildDiagram();
};
#endif // MAINWINDOW_H
