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


void MainWindow::on_pushButton_clicked()
{
    std::ifstream file1("/home/user/lab12_1.txt");
    std::string line;

    if (file1.is_open()) {
        while (getline (file1,line)){
          text1 += QString::fromStdString(line);
        }
        file1.close();
    }
    ui->first_text->setText(text1);
    std::ifstream file2("/home/user/lab12_2.txt");

    if (file2.is_open()) {
        while (getline (file2,line)) {
          text2 += QString::fromStdString(line);
        }
        file2.close();
    }
    ui->second_text->setText(text2);
}

int BoyerMooreSearch(QString text, QString word, QString & log){
    int i = 0;
    int j, stop;

    while(i < text.size() - word.size()){
        j = word.size() - 1;
        stop = word.size();
        while(j >= 0 && text[i+j] == word[j]){
            log += "Comparing " + word[j] + " to " + text[i+j] + ", match " + QString::number(i+j) + "\n";
            j--;
        }
        if(j == -1){
            return i;
        }
        stop = j;
        if(stop == word.size()){
            i = i + word.size();
        } else if (j > stop) {
            i = i + j - stop;
        } else {
            i++;
        }
    }
    return -1;
}

void MainWindow::on_pushButton_2_clicked()
{
    QStringList words = text1.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QString log = " ";
    word = words[words.size()/2];
    ui->label->setText(word);
    for(int i = 0; i<word.size(); ++i)
    {
        if(word[i]=='a') word[i] = 'o';
        if(word[i]=='i') word[i] = 'e';
    }
    ui->label_2->setText(word);

    int index = BoyerMooreSearch(text2, word, log);
    ui->label_3->setText(QString::number(index));

    QTextCharFormat fmt;
    fmt.setBackground(Qt::yellow);
    QTextCursor cursor(ui->second_text->document());
    cursor.setPosition(index, QTextCursor::MoveAnchor);
    cursor.setPosition(index + word.size(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(fmt);
    log += "\nFound word at index: " + QString::number(index);

    ui->textEdit_3->setText(log);
}
