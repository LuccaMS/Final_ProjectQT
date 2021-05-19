#include "details_video.h"
#include "ui_details_video.h"
#include <QtSql>

details_video::details_video(QWidget *parent, int x) :
    QDialog(parent),
    ui(new Ui::details_video)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.prepare("select * from video where id="+QString::number(x));
    if(query.exec())
    {
        query.first();
        ui->txt_id->setText(query.value(0).toString());
        ui->txt_nome->setText(query.value(1).toString());
        ui->txt_tipo->setText(query.value(2).toString());
        ui->txt_price->setText(query.value(3).toString());
        ui->txt_age->setText(query.value(4).toString());
        ui->txt_idv->setText(query.value(5).toString());
        ui->txt_idp->setText(query.value(6).toString());

        QByteArray outByteArray = query.value(7).toByteArray();
        QPixmap outPixmap = QPixmap();
        outPixmap.loadFromData(outByteArray);
        ui->txt_imagem->setPixmap(outPixmap);
        ui->txt_imagem->setScaledContents(true);
    }
}

details_video::~details_video()
{
    delete ui;
}
