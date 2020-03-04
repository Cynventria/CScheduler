#include "scheduler.h"
#include "ui_scheduler.h"
#include <QDebug>
#include <QMessageBox>
#include "workerselector.h"

Scheduler::Scheduler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Scheduler)
{
    ui->setupUi(this);
    selectedEvent = 0;
    teamCount = 0;
    peopleUpdated = 0;
    nameMode = 0;

}

Scheduler::~Scheduler()
{
    delete ui;
}

void Scheduler::on_pushButton_clicked()
{
    if(ALLworkers->List.size() > 0){
        events.push_back(Events());
        updateScheduler();
    }
    else{
        QMessageBox msg(this);
        msg.setWindowTitle("Message");
        msg.setText("尚未匯入工人!");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
    }

}

void Scheduler::on_tableWidget_itemSelectionChanged()
{
    if(ui->tableWidget->currentRow() != -1){
        for(int i = 0; i < 3; i++){
            ui->tableWidget->item(selectedEvent, i)->setBackground(QColor("#ffffff"));
            ui->tableWidget->item(selectedEvent, i)->setForeground(QColor("Black"));
        }
    }

    if(ui->tableWidget->currentRow() != -1)selectedEvent = ui->tableWidget->currentRow();

    ui->tableWidget->clearSelection();

    /*for(int i = 0; i < 3; i++){
        ui->tableWidget->item(selectedEvent, i)->setBackground(QColor("#3a7fc2"));
        ui->tableWidget->item(selectedEvent, i)->setForeground(QColor("White"));
    }
    ui->timeEdit->setTime(events[selectedEvent].startTime);
    ui->timeEdit_2->setTime(events[selectedEvent].endTime);
    ui->lineEdit->setText((events[selectedEvent].title));*/
    updateScheduler();


}

void Scheduler::on_lineEdit_textChanged(const QString &arg1)
{
    if(selectedEvent>=0){
        events[selectedEvent].title = ui->lineEdit->text();
        updateScheduler();
    }
}

void Scheduler::on_textEdit_textChanged()
{
    if(selectedEvent>=0){
        events[selectedEvent].note = ui->lineEdit->text();
        updateScheduler();
    }
}

void Scheduler::on_pushButton_5_clicked() //ADD WORKER
{
    if(selectedEvent>=0){

        vector<People> AList(ALLworkers->List.begin(), ALLworkers->List.end());

        wSelector.setList(&AList, &events[selectedEvent].away);
        wSelector.show();
    }
}

void Scheduler::updateScheduler(){

    ui->tableWidget->setRowCount(0);
    for(int i = 0; i < events.size(); i++){
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(events[i].startTime.toString() + "~" + events[i].endTime.toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(events[i].title));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(events[i].note));
    }

    for(int i = 0; i < 3; i++){
        ui->tableWidget->item(selectedEvent, i)->setBackground(QColor("#3a7fc2"));
        ui->tableWidget->item(selectedEvent, i)->setForeground(QColor("White"));
    }


    ui->listWidget->clear();
    for(int i = ALLworkers->teamCount; i > 0; i--){
        if(selectedEvent >= 0) ui->listWidget->insertItem(0, new QListWidgetItem("第" +  QString::number(i) + "小隊 - " + QString::number(ALLworkers->eachTeam[i])));
    }

}
void Scheduler::on_timeEdit_userTimeChanged(const QTime &time)
{
    if(selectedEvent>=0){
        events[selectedEvent].startTime = ui->timeEdit->time();
        updateScheduler();
    }
}

void Scheduler::on_timeEdit_2_userTimeChanged(const QTime &time)
{
    if(selectedEvent>=0){
        events[selectedEvent].endTime = ui->timeEdit_2->time();
        updateScheduler();
    }
}

void Scheduler::on_pushButton_7_clicked()
{
    workersUI.show();
}
