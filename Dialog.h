#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_2_pause_clicked();

private:
    struct Clock
    {
        size_t s;
        size_t m;
        size_t h;
    } __clock{0, 0, 0};

private:
    Ui::Dialog *ui;
    bool is_pause{false};
    bool is_over{false};
};
#endif // DIALOG_H
