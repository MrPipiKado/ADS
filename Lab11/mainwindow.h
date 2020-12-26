#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_find_clicked();

private:
    Ui::MainWindow *ui;
    int *D;
    QString output;
    QString S;
    QString P;
    QString wordToFind;
    void setTexts();
    void getWordToFind();
    void prefixFunction();
    int KMT_search(int start);
};
#endif // MAINWINDOW_H
