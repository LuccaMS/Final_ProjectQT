#ifndef CENTRAL_H
#define CENTRAL_H

#include <QDialog>

namespace Ui {
class central;
}

class central : public QDialog
{
    Q_OBJECT

public:
    explicit central(QWidget *parent = nullptr);
    ~central();

private slots:
    void on_add_video_clicked();

    void on_edit_video_clicked();

    void on_add_person_clicked();

    void on_edit_person_clicked();

    void on_btn_livres_clicked();

private:
    Ui::central *ui;
};

#endif // CENTRAL_H
