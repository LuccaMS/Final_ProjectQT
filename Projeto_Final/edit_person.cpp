#include "edit_person.h"
#include "ui_edit_person.h"
#include <QtSql>
#include <QMessageBox>
#include <QVector>

static int ida;
static int idnh;

edit_person::edit_person(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::edit_person)
{
    ui->setupUi(this);
    ida =id;
    QSqlQuery query;
    query.prepare("select * from person where id="+QString::number(id));
    if(query.exec())
    {
        query.first();
        ui->txt_id->setText(query.value(0).toString());
        ui->person_id->setValue(query.value(1).toInt());
        ui->txt_name->setText(query.value(2).toString());
        ui->person_age->setValue(query.value(3).toInt());
        ui->person_age->setMinimum(query.value(3).toInt());
        idnh = query.value(1).toInt();
    }
}

edit_person::~edit_person()
{
    delete ui;
}

void edit_person::on_btn_save_clicked()
{
    QString id,name,age;

    id = ui->person_id->text();
    name = ui->txt_name->text();
    age = ui->person_age->text();

    QVector <QString> t;
    QSqlQuery q;
    q.prepare("select id_person from person");
    if(q.exec()) // Isso é para checar se já existe uma outra person com o mesmo ID
    {
        while(q.next())
        {
            t.push_back(q.value(0).toString());
        }

        int c = 0;
        for(int i = 0; i < t.size();i++)
        {
            if(id == t.at(i))
            {
                c++;
            }
        }
        if(c == 0 || idnh == ui->person_id->value())
        {
            QSqlQuery query;

            query.prepare("update person set id_person = '"+id+"', name_person = '"+name+"', age_person = '"+age+"' where id = "+QString::number(ida));
            if(query.exec())
            {
                 QMessageBox::information(this, "Sucesso","Dados atualizados com sucesso!");
                this->close();
            }
        }
        else
            QMessageBox::warning(this, "ERRO","ID já está sendo utilizado!");
     }
    else
        QMessageBox::warning(this, "ERRO", "Erro ao verificar se o ID já existe");
}
