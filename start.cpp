#include "start.h"
#include "ui_start.h"
#include <QPainter>

Start::Start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);

}

Start::~Start()
{
    delete ui;
}

void Start::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/image/bkg.jpg"),QRect());

}


void Start::on_pushButton_clicked()
{
    this->accept();
}
