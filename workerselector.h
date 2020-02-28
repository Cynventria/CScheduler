#ifndef WORKERSELECTOR_H
#define WORKERSELECTOR_H

#include <QWidget>
#include "people.h"
#include <vector>
using namespace std;

namespace Ui {
class WorkerSelector;
}

class WorkerSelector : public QWidget
{
    Q_OBJECT

public:
    explicit WorkerSelector(QWidget *parent = nullptr);
    ~WorkerSelector();

    vector<People> List;
    vector<People> *selectedList;
    void setList(vector<People> AList, vector<People>* SList){
        List = AList;
        selectedList = SList;
        loadList();
    }
    void loadList();
    void refreshList();
    void clear();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::WorkerSelector *ui;
};

#endif // WORKERSELECTOR_H
