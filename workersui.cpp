#include "workersui.h"
#include "ui_workersui.h"
#include <QFileDialog>
#include <QDebug>

WorkersUI::WorkersUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkersUI)
{
    ui->setupUi(this);

}

WorkersUI::~WorkersUI()
{
    delete ui;
}

void WorkersUI::on_Button_Import_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "SelectCSV", ".", "*.csv");

    Workers->setCSV(path.toLocal8Bit().toStdString());
    Workers->import();
    /*for(int i = 0; i < Workers->List.size(); i++){
        qDebug() << Workers->List[i].name.c_str() << endl;
    }*/



    for(int i = 0; i < Workers->List.size(); i++){


        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(Workers->List[i].team)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(Workers->List[i].name));
        //ui->tableWidget->setItem(i, 2, new QTableWidgetItem(Workers->List[i].nickname));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(Workers->List[i].workGroup));

    }

}
