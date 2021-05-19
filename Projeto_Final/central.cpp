#include "central.h"
#include "ui_central.h"
#include "add_person.h"
#include "search_person.h"
#include "add_video.h"
#include "search_video.h"
#include "livres.h"

central::central(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::central)
{
    ui->setupUi(this);
}

central::~central()
{
    delete ui;
}

void central::on_add_video_clicked()
{
    add_video avideo;
    avideo.exec();

}

void central::on_edit_video_clicked()
{
    search_video v;
    v.exec();
}

void central::on_add_person_clicked()
{
   add_person nperson;
   nperson.exec();
}

void central::on_edit_person_clicked()
{
  search_person p;
  p.exec();
}

void central::on_btn_livres_clicked()
{
  livres v;
  v.exec();
}
