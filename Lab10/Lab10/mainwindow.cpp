#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
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


void MainWindow::on_pushButton_2_clicked()
{
    std::ifstream file1("/home/user/text1.txt");
        std::string line;

        if (file1.is_open()) {
            while (getline (file1,line)){
              text1 += QString::fromStdString(line);
            }
            file1.close();
        }
        ui->textEdit->setText(text1);
        std::ifstream file2("/home/user/text2.txt");

        if (file2.is_open()) {
            while (getline (file2,line)) {
              text2 += QString::fromStdString(line);
            }
            file2.close();
        }
        ui->textEdit_2->setText(text2);
}

int straightFind(QString S, int n, QString P, int m){
    int i, j;
    i = -1;
    do {
        j = 0;
        i++;
        while((j < m) && (S[i+j] == P[j])){
            j++;
        }
    } while (j < m && i < n-m);

    if(j == m){
        return i;
    } else {
        return -1;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QStringList words = text1.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        int min = 999999;
        for(int i = 0; i < words.size(); i++){
            if(words[i].size() < min){
                min = words[i].size();
                wordToFind = words[i];
            }
        }
        ui->label->setText(wordToFind);
        int index = straightFind(text2, text2.size(), wordToFind, wordToFind.size());
            QTextCharFormat fmt;
            fmt.setBackground(Qt::yellow);

            QTextCursor cursor(ui->textEdit_2->document());
            cursor.setPosition(index, QTextCursor::MoveAnchor);
            cursor.setPosition(index + wordToFind.size(), QTextCursor::KeepAnchor);
            cursor.setCharFormat(fmt);
            ui->label_2->setText(QString::number(index));
}
