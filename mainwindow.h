#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showAns();


private:
    Ui::MainWindow *ui;
    QString dir;
    vector<pair<QString,QString>> equal;
    vector<pair<QString,QString>> unequal;



protected:
    void paintEvent(QPaintEvent *event);

    
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_commandLinkButton_clicked();
};
#endif // MAINWINDOW_H
