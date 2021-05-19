#ifndef EDIT_VIDEO_H
#define EDIT_VIDEO_H

#include <QDialog>
#include <QFile>

namespace Ui {
class edit_video;
}

class edit_video : public QDialog
{
    Q_OBJECT

public:
    explicit edit_video(QWidget *parent = nullptr, int video_id = 0);
    ~edit_video();

private slots:
    void on_btn_image_clicked();

    void on_btn_save_clicked();

private:
    Ui::edit_video *ui;
    QFile *arquivo;
};

#endif // EDIT_VIDEO_H
