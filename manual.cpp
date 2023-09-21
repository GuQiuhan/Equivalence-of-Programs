#include "manual.h"
#include "ui_manual.h"
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

Manual::Manual(vector<pair<QString,QString>>* u,vector<pair<QString,QString>>* e,QWidget *parent ) :
    QDialog(parent),
    unequal(u),
    equal(e),
    ui(new Ui::Manual)
{
    isSave=false;
    unequalIndex=0;
    equalIndex=0;

    tmpDir="Unequal";//默认先确认不等价的
    if(u->size()==0)
    {
        tmpDir="Equal";
    }

    ui->setupUi(this);
    showTextDiff();

    //设置文本编辑器偏好
    QPalette pt = palette();
    pt.setBrush(QPalette::Highlight, Qt::yellow);//设置黄色高亮
    pt.setBrush(QPalette::HighlightedText, Qt::NoBrush);
    ui->textBrowser->setPalette(pt);
    ui->textBrowser_2->setPalette(pt);
}

Manual::~Manual()
{
    delete ui;
}


void Manual::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/image/bkg.jpg"),QRect());

}

void Manual::showText()//显示文本
{
    //清空选中框
    ui->equal->setCheckState(Qt::Unchecked);
    ui->unequal->setCheckState(Qt::Unchecked);
    ui->notSure->setCheckState(Qt::Unchecked);

    if(tmpDir=="Unequal")
    {
        QString data;
        QFile file((*unequal)[unequalIndex].first); //path是文件的路径
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"文件未打开!";
        }
        while(!file.atEnd())
        {
            QByteArray array = file.readLine();
            QString str(array);
           // qDebug()<< str;
            data.append(str);
        }
        ui->textBrowser->setText(data);


        QString data2;
        QFile file2((*unequal)[unequalIndex].second); //path是文件的路径
        if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"文件未打开!";
        }
        while(!file2.atEnd())
        {
            QByteArray array = file2.readLine();
            QString str(array);
           // qDebug()<< str;
            data2.append(str);
        }
        ui->textBrowser_2->setText(data2);
    }

    else
    {
        QString data;
        QFile file((*equal)[equalIndex].first); //path是文件的路径
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"文件未打开!";
        }
        while(!file.atEnd())
        {
            QByteArray array = file.readLine();
            QString str(array);
           // qDebug()<< str;
            data.append(str);
        }
        ui->textBrowser->setText(data);


        QString data2;
        QFile file2((*equal)[equalIndex].second); //path是文件的路径
        if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"文件未打开!";
        }
        while(!file2.atEnd())
        {
            QByteArray array = file2.readLine();
            QString str(array);
           // qDebug()<< str;
            data2.append(str);
        }
        ui->textBrowser_2->setText(data2);
    }
}



void Manual::on_commandLinkButton_clicked()//返回按钮
{
    this->close();
}

void Manual::on_pushButton_clicked()//nextPair
{
    if(isSave==false)//未保存需要提示是否保存
    {
        QMessageBox::StandardButton result= QMessageBox::question(this,"question","Are you sure not to save?", QMessageBox::Yes | QMessageBox::Save , QMessageBox::Save);
        if (result == QMessageBox::Save)
        {
           save();
        }

    }
    if(tmpDir=="Unequal")
    {
        unequalIndex++;
        if(unequalIndex==(*unequal).size())//说明不等价集遍历结束，遍历等价集
        {
            tmpDir="Equal";
        }
    }
    else
    {
        equalIndex++;
        if(equalIndex==(*equal).size())//说明遍历结束
        {
            QMessageBox::information(this, "information","That's all!");
        }
    }
    isSave=false;
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
    showTextDiff();
}

void Manual::on_pushButton_2_clicked()//save
{
   save();

}

void Manual::save()
{
    if(isSave)//不要重复保存
    {
         QMessageBox::information(this, "information","Save Successfully!");
         return;
    }

    if(ui->equal->isChecked()==false&&ui->unequal->isChecked()==false&&ui->notSure->isChecked()==false)//未选
    {
        QMessageBox::warning(this, "warning","Check First!(You can choose 'not sure', which won't change anything.)");
        return;
    }

    isSave=true;


    if(tmpDir=="Unequal")
    {
        if(ui->equal->isChecked()==true)//说明人工判断是等价的
        {
            pair<QString,QString> tmp= (*unequal)[unequalIndex];
            (*equal).push_back(tmp);
            (*unequal).erase((*unequal).begin() + unequalIndex);//删除此对
            unequalIndex--;
        }

    }
    else if(tmpDir=="Equal")
    {
        if(ui->unequal->isChecked()==true)//说明人工判断是不等价的
        {
            pair<QString,QString> tmp= (*equal)[equalIndex];
            (*unequal).push_back(tmp);
            (*equal).erase((*equal).begin() + equalIndex);//删除此对
            equalIndex--;
        }

    }


    QMessageBox::information(this, "information","Save Successfully!");

}

void Manual::showTextDiff()//展示不同
{
    //清空选中框
    ui->equal->setCheckState(Qt::Unchecked);
    ui->unequal->setCheckState(Qt::Unchecked);
    ui->notSure->setCheckState(Qt::Unchecked);

    if(tmpDir=="Unequal")//确定打开哪个文件
    {

        QFile file1((*unequal)[unequalIndex].first); //path是文件的路径
        QFile file2((*unequal)[unequalIndex].second); //path是文件的路径
        if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"文件未打开!";
        }
        if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"文件未打开!";
        }

        //开始逐行读取文件并判断
        while(!file1.atEnd()&&!file2.atEnd())
        {
            QByteArray array1 = file1.readLine();
            QByteArray array2 = file2.readLine();
            QString str1(array1);
            QString str2(array2);

            //一行相同，直接输出
            if(str1==str2)
            {
                ui->textBrowser->append(str1);
                ui->textBrowser_2->append(str2);
            }

            //不同，以str1为主对file2逐行对比直至找到相同的，或者找不到
            else
            {
                bool flag=false;
//                QString data1;
//                QString data2;
                //制造空行高亮效果
                ui->textBrowser->append("<span style=\"background-color: rgba(255,193,37,0.3);\"><font color=\"#FFE4E1\">___________________________________________________________________</font></span>");
                str2= "<font color=\"#FF0000\">" + str2 + "</font>";
                ui->textBrowser_2->append(str2);
                while(!flag&&!file1.atEnd()&&!file2.atEnd())
                {
                    array2 = file2.readLine();
                    QString tmp(array2);
                    if(str1==tmp)
                    {
                        ui->textBrowser->append(str1);
                        ui->textBrowser_2->append(tmp);
                        flag=true;

                    }
                    else
                    {
                        ui->textBrowser->append("<span style=\"background-color: rgba(255,193,37,0.3);\"><font color=\"#FFE4E1\">___________________________________________________________________</font></span>");
                        tmp= "<font color=\"#FF0000\">" + tmp + "</font>";
                        ui->textBrowser_2->append(tmp);
                    }

                }
                if(!flag)//没有找到，将str1输出
                {
                    str1= "<font color=\"#FF0000\">" + str1 + "</font>";
                    ui->textBrowser->append(str1);
                }
            }

        }

        //将剩下的都写入textbrowser

        //QString data1,data2;
        while(!file1.atEnd())
        {
            QByteArray array = file1.readLine();
            QString str(array);
            str= "<font color=\"#FF0000\">" + str + "</font>";
            ui->textBrowser->append(str);

        }


        while(!file2.atEnd())
        {
            QByteArray array = file2.readLine();
            QString str(array);
            str= "<font color=\"#FF0000\">" + str + "</font>";
            ui->textBrowser_2->append(str);
        }
    }

    else
    {

        QFile file1((*equal)[equalIndex].first); //path是文件的路径
        QFile file2((*equal)[equalIndex].second); //path是文件的路径
        if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"文件未打开!";
        }
        if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"文件未打开!";
        }

        //开始逐行读取文件并判断
        while(!file1.atEnd()&&!file2.atEnd())
        {
            QByteArray array1 = file1.readLine();
            QByteArray array2 = file2.readLine();
            QString str1(array1);
            QString str2(array2);

            if(str1==str2)
            {
                ui->textBrowser->append(str1);
                ui->textBrowser_2->append(str2);
            }

            else
            {
                bool flag=false;

                ui->textBrowser->append("<span style=\"background-color: rgba(255,193,37,0.3);\"><font color=\"#FFE4E1\">___________________________________________________________________</font></span>");
                //data1.append("\n");
                str2= "<font color=\"#FF0000\">" + str2 + "</font>";
                ui->textBrowser_2->append(str2);
                while(!flag&&!file1.atEnd()&&!file2.atEnd())
                {
                    array2 = file2.readLine();
                    QString tmp(array2);
                    if(str1==tmp)
                    {

                        ui->textBrowser->append(str1);
                        ui->textBrowser_2->append(tmp);
                        flag=true;

                    }
                    else
                    {
                        ui->textBrowser->append("<span style=\"background-color: rgba(255,193,37,0.3);\"><font color=\"#FFE4E1\">___________________________________________________________________</font></span>");

                        tmp= "<font color=\"#FF0000\">" + tmp + "</font>";
                        ui->textBrowser_2->append(tmp);

                    }

                }
                if(!flag)
                {
                    str1= "<font color=\"#FF0000\">" + str1 + "</font>";
                    ui->textBrowser->append(str1);

                }
            }

        }

        //将剩下的都写入textbrowser

        //QString data1,data2;
        while(!file1.atEnd())
        {
            QByteArray array = file1.readLine();
            QString str(array);
           // qDebug()<< str;
            str= "<font color=\"#FF0000\">" + str + "</font>";
            ui->textBrowser->append(str);
            //data1.append(str);
        }
        //ui->textBrowser->append(data1);


        while(!file2.atEnd())
        {
            QByteArray array = file2.readLine();
            QString str(array);
           // qDebug()<< str;
            str= "<font color=\"#FF0000\">" + str + "</font>";
            ui->textBrowser_2->append(str);

            //data2.append(str);
        }
        //ui->textBrowser_2->append(data2);


    }
}


