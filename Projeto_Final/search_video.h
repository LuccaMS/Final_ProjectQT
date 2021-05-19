#ifndef SEARCH_VIDEO_H
#define SEARCH_VIDEO_H

#include <QDialog>
#include <QFile>
namespace Ui {
class search_video;
}

class search_video : public QDialog
{
    Q_OBJECT

public:
    explicit search_video(QWidget *parent = nullptr);
    ~search_video();

private slots:
    void on_btn_delet_clicked();

    void on_btn_edit_clicked();

    void on_btn_detail_clicked();

    void on_btn_desalug_clicked();

private:
    Ui::search_video *ui;
    QFile *arquivo;
};

#endif // SEARCH_VIDEO_H
