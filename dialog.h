#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "people.h"
#include <vector>
using namespace std;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    vector<People> *list;

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
