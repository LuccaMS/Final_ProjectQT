#include "edit_livres.h"
#include "ui_edit_livres.h"
#include <QtSql>
#include <QMessageBox>
#include <QVector>
#include "livres.h"

int t;
bool livres::aux = false;

edit_livres::edit_livres(QWidget *parent, int x) :
    QDialog(parent),
    ui(new Ui::edit_livres)
{
    ui->setupUi(this);
    t = x;
    livres::aux = false;
    QSqlQuery query;

    query.prepare("select * from video where id="+QString::number(x));
    if(query.exec())
    {
        query.first();
        ui->text_id->setText(query.value(0).toString());
        ui->text_name->setText(query.value(1).toString());
        ui->text_tipo->setText(query.value(2).toString());
        ui->text_preco->setText(query.value(3).toString());
        ui->text_idade->setText(query.value(4).toString());
        ui->text_idv->setText(query.value(5).toString());
        ui->spinBox_idp->setValue(query.value(6).toInt());

        QByteArray outByteArray = query.value(7).toByteArray();
        QPixmap outPixmap = QPixmap();
        outPixmap.loadFromData(outByteArray);
        ui->label_igm->setPixmap(outPixmap);
        ui->label_igm->setScaledContents(true);
    }
}

edit_livres::~edit_livres()
{
    delete ui;
}

void edit_livres::on_btn_save_clicked()
{

    QString a;
    a = ui->spinBox_idp->text();
    QVector<QString> x ;
    QSqlQuery q;
    q.prepare("select id_person from person");
    if(q.exec())
    {
        while(q.next())
        {
            x.push_back(q.value(0).toString());
        }
    }
    else
        QMessageBox::warning(this,"","Erro ao verificar a existência do ID_Pessoa digitado !");

    int c = 0;
    for(int i = 0; i <x.size();i++)
    {
        if(a == x.at(i))
        {
            c++;
        }
    }

    QSqlQuery query;
    int z;
    query.prepare("select age_person from person where id_person=:idp");
    query.bindValue(":idp",a);
    if(query.exec())
    {
        while(query.next())
        {
            z = query.value(0).toInt();  //Irá pegar a idade da pessoa em questão
        }

        if(z == ui->text_idade->text().toInt() || z > ui->text_idade->text().toInt() || ui->spinBox_idp->value() == 0)
        {
            if(c != 0)
            {
                QSqlQuery query;
                query.prepare("update video set idperson_video = '"+a+"' where id="+QString::number(t));
                if(query.exec())
                {
                    livres::aux = true;
                    QMessageBox::information(this,"","Vídeo alugado com sucesso !");
                    this->close();
                }
                else
                    QMessageBox::warning(this,"ERRO","Erro ao alugar o vídeo!");
            }

            else if(ui->spinBox_idp->value() == 0)
            {
                QMessageBox::information(this,"","ID person continua como zero !");
            }

            else
            {
                QMessageBox::warning(this,"ERRO","Não existe alguém com tal ID no banco de dados!");
                this->close();
            }

        }
        else
        {
            QMessageBox::warning(this,"ERRO","Idade da pessoa em questão menor que a faixa etária !");
        }
    }
    else
    {
        QMessageBox::warning(this,"ERRO","Erro ao verificar a faixa etária !");
    }

}
