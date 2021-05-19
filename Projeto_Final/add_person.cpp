#include "add_person.h"
#include "ui_add_person.h"
#include <QtSql>
#include <QMessageBox>
#include <QVector>

add_person::add_person(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_person)
{
    ui->setupUi(this);
}

add_person::~add_person()
{
    delete ui;
}

void add_person::on_btn_addperson_clicked()
{
    QString name,id,age;
    id = ui->person_id->text();
    age = ui->person_age->text();
    name = ui->person_name->text();
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
        if(c == 0 )
        {
            QSqlQuery query;
            query.prepare("insert into person (id_person,name_person,age_person) values('"+id+"','"+name+"','"+age+"')");
            if(query.exec())
            {
                QMessageBox::information(this, "Êxito","Pessoa salva no banco de dados com sucesso !");
                ui->person_id->setValue(0);
                ui->person_age->setValue(0);
                ui->person_name->clear();
            }
        }
        else
            QMessageBox::warning(this, "ERRO","ID já está sendo utilizado, digite outro!");
    }

    else
    {
        QMessageBox::warning(this, "ERRO","Erro ao salvar a pessoa no banco de dados !");
    }

}

void add_person::on_btn_cancel_clicked()
{
    ui->person_id->setValue(0);
    ui->person_name->clear();
    ui->person_age->setValue(0);
}
