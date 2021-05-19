#ifndef ADD_VIDEO_H
#define ADD_VIDEO_H

#include <QDialog>
#include <QFile>

namespace Ui {
class add_video;
}

class add_video : public QDialog
{
    Q_OBJECT

public:
    explicit add_video(QWidget *parent = nullptr);
    ~add_video();


private slots:
    void on_btn_salvar_clicked();

    void on_btn_imagem_clicked();

private:
    Ui::add_video *ui;
    QFile *arquivo;
};

#endif // ADD_VIDEO_H
