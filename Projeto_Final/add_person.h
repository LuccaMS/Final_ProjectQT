#ifndef ADD_PERSON_H
#define ADD_PERSON_H

#include <QDialog>

namespace Ui {
class add_person;
}

class add_person : public QDialog
{
    Q_OBJECT

public:
    explicit add_person(QWidget *parent = nullptr);
    ~add_person();

private slots:
    void on_btn_addperson_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::add_person *ui;
};

#endif // ADD_PERSON_H
