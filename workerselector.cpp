#include "workerselector.h"
#include "ui_workerselector.h"
#include <QDebug>

WorkerSelector::WorkerSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkerSelector)
{
    ui->setupUi(this);
}

WorkerSelector::~WorkerSelector()
{
    delete ui;
}

void WorkerSelector::refreshList(){

    ui->tableWidget->setRowCount(0);
    ui->tableWidget_2->setRowCount(0);
    for(int i = 0; i < List.size(); i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(List[i].team)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(List[i].name));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(List[i].nickname));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(List[i].workGroup));
    }
    for(int i = 0; i < selectedList->size(); i++){
        ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
        ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(QString::number((*selectedList)[i].team)));
        ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem((*selectedList)[i].name));
        ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem((*selectedList)[i].nickname));
        ui->tableWidget_2->setItem(i, 3, new QTableWidgetItem((*selectedList)[i].workGroup));
    }

}
void WorkerSelector::loadList(){
    for(int i = 0; i < selectedList->size(); i++){
        for(int j = 0; j < List.size(); j++){
            if((*selectedList)[i].name == List[j].name){
                List.erase(List.begin()+j);
            }
        }
    }
    refreshList();
}
void WorkerSelector::clear(){
    List.clear();
    selectedList = NULL;
    ui->tableWidget->setRowCount(0);
    ui->tableWidget_2->setRowCount(0);
}

void WorkerSelector::on_pushButton_3_clicked()
{
    for(int i = 0; i < ui->tableWidget->selectedItems().size(); i+=4){
        for(int j = 0; j < List.size(); j++){
            if(ui->tableWidget->selectedItems()[i+1]->text() == List[j].name){
                selectedList->push_back(List[j]);
                List.erase(List.begin()+j);
                j--;
            }
        }
    }
    refreshList();
}

void WorkerSelector::on_pushButton_4_clicked()
{
    for(int i = 0; i < ui->tableWidget_2->selectedItems().size(); i+=4){
        for(int j = 0; j < selectedList->size(); j++){
            if(ui->tableWidget_2->selectedItems()[i+1]->text() == (*selectedList)[j].name){
                List.push_back((*selectedList)[j]);
                selectedList->erase(selectedList->begin()+j);
                j--;
            }
        }
    }
    refreshList();
}
