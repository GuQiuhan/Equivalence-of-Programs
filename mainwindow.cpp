#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handle.h"
#include <iostream>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPainter>
#include <QDebug>
#include "manual.h"
#include <QMessageBox>
using namespace std;

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

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/image/bkg.jpg"),QRect());

}

void MainWindow::on_pushButton_clicked()//开始检测按钮
{
    dir=ui->lineEdit->text();
    if(dir==NULL)
    {
        QMessageBox::information(this, "warning","The directory path can not be NULL!");
        return;
    }

    //string path="/Users/pro/Desktop/QtProjects/SoftwareProj/input";
    //vector<vector<pair<QString,QString>>> ans=Handle().handle(QString::fromStdString(path));
    vector<vector<pair<QString,QString>>> ans=Handle().handle(dir);
    equal=ans[0];
    unequal=ans[1];

    showAns();

}

void MainWindow::showAns()
{
    QStandardItemModel* model = new QStandardItemModel();
    QStringList labels = QObject::trUtf8("File1,File2").simplified().split(",");
    model->setHorizontalHeaderLabels(labels);

    QStandardItem* item;
    int i=0;
    while(i!=equal.size())
    {
        item = new QStandardItem(equal[i].first);//括号里面是QString即可
        model->setItem(i,0,item);
        item = new QStandardItem(equal[i].second);
        model->setItem(i,1,item);
        i++;
    }

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 500);//设置列宽，注意要在setModel之后
    ui->tableView->setColumnWidth(1, 500);
    ui->tableView->show();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->label_2->setText("Equal Result: total "+QString::number(equal.size(), 10)+".");
    ui->label_2->adjustSize();
    ui->label_2->repaint();

    QStandardItemModel* model2 = new QStandardItemModel();
    QStringList labels2 = QObject::trUtf8("File1,File2").simplified().split(",");
    model2->setHorizontalHeaderLabels(labels2);

    //QStandardItem* item;
    i=0;
    while(i!=unequal.size())
    {
        item = new QStandardItem(unequal[i].first);//括号里面是QString即可
        model2->setItem(i,0,item);
        item = new QStandardItem(unequal[i].second);
        model2->setItem(i,1,item);
        i++;
    }

    ui->tableView_2->setModel(model2);
    ui->tableView_2->setColumnWidth(0, 500);//设置列宽，注意要在setModel之后
    ui->tableView_2->setColumnWidth(1, 500);
    ui->tableView_2->show();
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->label_3->setText("Unequal Result: total "+QString::number(unequal.size(), 10)+".");
    ui->label_3->adjustSize();
    ui->label_3->repaint();
}

void MainWindow::on_pushButton_2_clicked()//刷新，数据改变后重新展示
{
    showAns();
}

void MainWindow::on_commandLinkButton_clicked()//人工检测
{
    //if(unequal.size()==0&&equal.size()==0)
    if(unequal.empty()&&equal.empty())
    {
        QMessageBox::information(this, "warning","Please judge automatically first!");
        return;
    }
    Manual m(&unequal,&equal);
    m.exec();

    showAns();

}
