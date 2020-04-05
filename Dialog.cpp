#include "Dialog.h"
#include "./ui_Dialog.h"

#include <thread>
#include <chrono>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("ghasem-clock");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_start_clicked()
{
    using namespace std::chrono_literals;

    if (ui->pushButton_start->text() == "Stop")
    {
        is_over = true;
        is_pause = false;
        __clock = {};
    }
    else
    {
        is_over = is_pause = false;
    }

    std::thread([&]() {
        ui->pushButton_start->setText("Stop");

        while (!is_over)
        {
            while (is_pause)
            {
                std::this_thread::yield();
            }

            if (__clock.s != 59)
            {
                __clock.s++;
            }
            else if (__clock.s == 59)
            {
                __clock.s = 0;
                if (__clock.m != 59)
                {
                    __clock.m++;
                }
                else if (__clock.m == 59)
                {
                    __clock.m = 0;
                    __clock.h++;
                }
            }

            const QString t{QString("%1:%2:%3").arg(__clock.h).arg(__clock.m).arg(__clock.s)};
            ui->label_time->setText(t);

            std::this_thread::sleep_for(1s);
        }

        ui->pushButton_start->setText("Start");
    }).detach();
}

void Dialog::on_pushButton_2_pause_clicked()
{
    is_pause = !is_pause;
}
