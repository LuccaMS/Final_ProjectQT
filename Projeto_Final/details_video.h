#ifndef DETAILS_VIDEO_H
#define DETAILS_VIDEO_H

#include <QDialog>

namespace Ui {
class details_video;
}

class details_video : public QDialog
{
    Q_OBJECT

public:
    explicit details_video(QWidget *parent = nullptr, int video_id = 0);
    ~details_video();

private:
    Ui::details_video *ui;
};

#endif // DETAILS_VIDEO_H
