#ifndef START_H
#define START_H

#include <QDialog>

namespace Ui {
class Start;
}

class Start : public QDialog
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();

private:
    Ui::Start *ui;

protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_pushButton_clicked();
};

#endif // START_H
