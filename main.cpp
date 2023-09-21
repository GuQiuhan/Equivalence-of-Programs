#include "mainwindow.h"


#include <QApplication>
#include <vector>

#include "handle.h"
#include <iostream>
#include <QProcess>
#include "start.h"
using namespace std;

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>


QString users_path="/Users/pro/Desktop/QtProjects/SoftwareProj/users.txt";//可改变路径

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv); //googleTest框架
    GTEST_FLAG_SET(death_test_style, "fast");
    RUN_ALL_TESTS();//googleTest框架




    QApplication a(argc, argv);
    Start s;
    MainWindow wm;
    if(s.exec()==QDialog::Accepted)
    {

        wm.show();
    }

    return a.QApplication::exec();
}
