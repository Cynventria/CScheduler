#ifndef WORKERSUI_H
#define WORKERSUI_H

#include <QWidget>
#include "peoplelist.h"

namespace Ui {
class WorkersUI;
}

class WorkersUI : public QWidget
{
    Q_OBJECT

public:
    explicit WorkersUI(QWidget *parent = nullptr);
    ~WorkersUI();

    PeopleList *Workers;
    void setList(PeopleList* PList){Workers = PList;}

private slots:
    void on_Button_Import_clicked();

private:
    Ui::WorkersUI *ui;
};

#endif // WORKERSUI_H
