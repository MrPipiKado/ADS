#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <vector>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    output = "";
    D = nullptr;
    setTexts();
    getWordToFind();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTexts(){
    std::ifstream file1("/home/user/lab11.txt");
    std::string line;

    if (file1.is_open())
    {
    getline (file1,line);
    S=QString::fromStdString(line);
    getline (file1,line);
    P=QString::fromStdString(line);
          file1.close();
      }
    ui->first_text->setText(S);
    ui->word->setText(P);
}

void MainWindow::getWordToFind(){
            wordToFind = P;
}

void MainWindow::prefixFunction(){
    int wordSize = wordToFind.size();
    D = new int[wordSize];
    D[0] = 0;
    for(int i = 1; i < wordSize; i++ ){
        int j = D[i-1];
        while(j > 0 && wordToFind[j] != wordToFind[i]){
            j = D[j - 1];
        }
        if(wordToFind[j] == wordToFind[i]){
            j++;
        }
        D[i] = j;
    }
    for(int i = 0; i < wordSize; i++){
        output += wordToFind.left(i+1) + "\t\t" + wordToFind.left(i+1);
        output += "\t\t" + QString::number(D[i]);
        output += "\n";
    }
    ui->search_results->setText(output);
}

void MainWindow::on_find_clicked()
{
    std::vector<int> indexes;
    int n = 0;
    int index;
    prefixFunction();
    while(KMT_search(n)>0)
    {
        index = KMT_search(n);
        n = index+wordToFind.size();
        indexes.push_back(index);
    QTextCharFormat fmt;
    fmt.setBackground(Qt::yellow);
    QTextCursor cursor(ui->first_text->document());
    cursor.setPosition(index, QTextCursor::MoveAnchor);
    cursor.setPosition(index + wordToFind.size(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(fmt);
    output + "\nFound word at index: " + QString::number(index);
    }
    std::reverse(indexes.begin(), indexes.end());
    output+="\n";
    for (auto i : indexes)
    {
        output+= QString::number(i) + " ";
    }
    ui->search_results->setText(output);
}

int MainWindow::KMT_search(int start){
    int d;
    int i = start;
    int j = 0;
    while(i < S.size() && j < wordToFind.size()){
        d = 1;
        while(d != wordToFind.size()){
            if(S[i] == wordToFind[j]){
                d++;
                i++;
                j++;
            } else {
                i=i+d-D[d];
                j = 0;
                break;
            }
        }
        if (d == wordToFind.size()){
            return i - d + 1;
        }
    }
    return -1;
}


