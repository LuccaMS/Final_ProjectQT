#ifndef EDIT_LIVRES_H
#define EDIT_LIVRES_H

#include <QDialog>

namespace Ui {
class edit_livres;
}

class edit_livres : public QDialog
{
    Q_OBJECT

public:
    explicit edit_livres(QWidget *parent = nullptr, int x = 0);
    ~edit_livres();

private slots:
    void on_btn_save_clicked();

private:
    Ui::edit_livres *ui;
};

#endif // EDIT_LIVRES_H
