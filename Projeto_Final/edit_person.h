#ifndef EDIT_PERSON_H
#define EDIT_PERSON_H

#include <QDialog>

namespace Ui {
class edit_person;
}

class edit_person : public QDialog
{
    Q_OBJECT

public:
    explicit edit_person(QWidget *parent = nullptr, int person_id = 0);
    ~edit_person();

private slots:
    void on_btn_save_clicked();

private:
    Ui::edit_person *ui;

};

#endif // EDIT_PERSON_H
