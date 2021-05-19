#ifndef SEARCH_PERSON_H
#define SEARCH_PERSON_H

#include <QDialog>

namespace Ui {
class search_person;
}

class search_person : public QDialog
{
    Q_OBJECT

public:
    explicit search_person(QWidget *parent = nullptr);
    ~search_person();

private slots:
    void on_btn_edit_clicked();

    void on_btn_delete_clicked();

private:
    Ui::search_person *ui;
};

#endif // SEARCH_PERSON_H
