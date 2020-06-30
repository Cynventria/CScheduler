#include "scheduler.h"
#include "ui_scheduler.h"
#include <QDebug>
#include <QMessageBox>
#include "workerselector.h"
#include <algorithm>

Scheduler::Scheduler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Scheduler)
{
    ui->setupUi(this);
    selectedEvent = 0;
    teamCount = 0;
    peopleUpdated = 0;
    nameMode = 0;
    QObject::connect(&wSelector, SIGNAL(workerChanged()), this, SLOT(EXTupdateScheduler()));

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
    if(selectedEvent>=0 && events.size() != 0){



        vector<People> AList(ALLworkers->List.begin(), ALLworkers->List.end());

        wSelector.setList(&AList, &events[selectedEvent].away);
        wSelector.show();
    }
}

void Scheduler::updateScheduler(){

    for(int i = 0; i < events.size(); i++){
        for(int j = i+1; j < events.size(); j++){
            if(events[i].startTime > events[j].startTime){
                swap(events[i], events[j]);
                if(i == selectedEvent) selectedEvent = j;
            }
        }
    }

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

    ui->timeEdit->setTime(events[selectedEvent].startTime);
    ui->timeEdit_2->setTime(events[selectedEvent].endTime);
    ui->lineEdit->setText(events[selectedEvent].title);


    ui->tableWidget_2->setRowCount(0);

    for(int i = 0; i < events[selectedEvent].away.size(); i++){
        ui->tableWidget_2->insertRow(i);
        ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(QString::number(events[selectedEvent].away[i].team)));
        ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(events[selectedEvent].away[i].name));
        ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(events[selectedEvent].away[i].workGroup));
    }

    bool overlaped = 0, peopleoverlapped = 0;
    //vector<int>
    for(int i = 0; i < events.size(); i++){
        if(i == selectedEvent) continue;
        if(events[i].startTime < events[selectedEvent].endTime && events[i].endTime > events[selectedEvent].startTime){
            //
            overlaped = 1;
            qDebug() << "overlapped　with"  << events[i].startTime << endl;
            for(int j = 0; j < events[selectedEvent].away.size() ; j++){
                for(int k = 0; k < events[i].away.size(); k++){
                    if( events[selectedEvent].away[j].name == events[i].away[k].name){
                        qDebug() << events[selectedEvent].away[j].name << "overlapped" << endl;

                        ui->tableWidget_2->item(j,0)->setBackground(QColor("#ffc0c0"));
                        ui->tableWidget_2->item(j,1)->setBackground(QColor("#ffc0c0"));
                        ui->tableWidget_2->item(j,2)->setBackground(QColor("#ffc0c0"));

                        peopleoverlapped = 1;

                    }
                }
            }

        }
    }
    //overlapped events detection

    ui->listWidget->clear();
    for(int i = ALLworkers->teamCount; i > 0; i--){
        int inTeam = ALLworkers->eachTeam[i];

        for(int j = 0; j < events[selectedEvent].away.size(); j++)
            if(events[selectedEvent].away[j].team == i)  inTeam--;

        if(selectedEvent >= 0) ui->listWidget->insertItem(0, new QListWidgetItem("第" +  QString::number(i) + "小隊 - " + QString::number(inTeam)));
        if(inTeam == 2) ui->listWidget->item(0)->setBackground(QColor("#ffc0c0"));
        else if(inTeam < 2) ui->listWidget->item(0)->setBackground(QColor("#ff5a5a"));
    }
    if(peopleoverlapped)
        ui->listWidget->insertItem(0, new QListWidgetItem("!!重複調離同一個人!!"));


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
void Scheduler::EXTupdateScheduler(){
    qDebug() << "UPDATED FROM SLOT" << endl;
    updateScheduler();
}

void Scheduler::on_pushButton_2_clicked()
{
    events.erase(events.begin()+selectedEvent);
    selectedEvent = 0;
    updateScheduler();
}
