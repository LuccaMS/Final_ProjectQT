#ifndef LIVRES_H
#define LIVRES_H

#include <QDialog>

namespace Ui {
class livres;
}

class livres : public QDialog
{
    Q_OBJECT

public:
    explicit livres(QWidget *parent = nullptr);
    ~livres();

    static bool aux;

private slots:
    void on_btn_alug_clicked();

private:
    Ui::livres *ui;

};

#endif // LIVRES_H
