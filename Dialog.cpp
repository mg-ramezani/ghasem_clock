#include "Dialog.h"
#include "./ui_Dialog.h"

#include <thread>
#include <chrono>

#include <QMessageBox>

#include <iostream>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , setting("ghasem")
{
    ui->setupUi(this);
    setWindowTitle("ghasem-clock");

    if (!setting.value("s").isNull())
    {
        const auto r{QMessageBox::question(this, "Reload ?", "Reload last time ?")};
        if (r == QMessageBox::Yes)
        {
            __clock.s = setting.value("s").toUInt();
            __clock.m = setting.value("m").toUInt();
            __clock.h = setting.value("h").toUInt();

            const QString t{QString("%1:%2:%3").arg(__clock.h).arg(__clock.m).arg(__clock.s)};
            ui->label_time->setText(t);
        }
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_start_clicked()
{
    using namespace std::chrono_literals;

    if (ui->pushButton_start->text() == "X")
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
        ui->pushButton_start->setText("X");

        while (!is_over)
        {
            while (is_pause)
            {
                std::this_thread::sleep_for(500ms);
            }

            if (__clock.s != 59)
            {
                __clock.s++;
            }
            else
            {
                __clock.s = 0;
                if (__clock.m != 59)
                {
                    __clock.m++;
                }
                else
                {
                    __clock.m = 0;
                    __clock.h++;
                }
            }

            const QString t{QString("%1:%2:%3").arg(__clock.h).arg(__clock.m).arg(__clock.s)};
            ui->label_time->setText(t);

            std::thread([&]() {
                setting.setValue("s", QVariant::fromValue(__clock.s));
                setting.setValue("m", QVariant::fromValue(__clock.m));
                setting.setValue("h", QVariant::fromValue(__clock.h));

                std::this_thread::sleep_for(1min);
            }).detach();

            std::this_thread::sleep_for(1s);
        }

        ui->pushButton_start->setText("S");
    }).detach();
}

void Dialog::on_pushButton_2_pause_clicked()
{
    is_pause = !is_pause;
}
