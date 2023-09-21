#ifndef MANUAL_H
#define MANUAL_H

#include <QDialog>
#include <vector>
#include <QString>
using namespace std;

namespace Ui {
class Manual;
}

class Manual : public QDialog
{
    Q_OBJECT

public:
    explicit Manual(vector<pair<QString,QString>>* u=nullptr,vector<pair<QString,QString>>* e=nullptr,QWidget *parent = nullptr);
    ~Manual();

private:
    Ui::Manual *ui;
    vector<pair<QString,QString>>* unequal;//使用指针，由此每一处的修改可以直接修改mainwindow中的数据
    int unequalIndex;
    int equalIndex;
    vector<pair<QString,QString>>* equal;
    void showText();
    bool isSave; //是否保存
    string tmpDir;//当前遍历的是Equal/Unequal
    void save();
    void showTextDiff();
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_commandLinkButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // MANUAL_H
