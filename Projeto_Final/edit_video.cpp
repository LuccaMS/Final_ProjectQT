#include "edit_video.h"
#include "ui_edit_video.h"
#include <QtSql>
#include <QMessageBox>
#include <QVector>
#include <QPixmap>
#include <QFileDialog>

bool check;
static int id_person;
QByteArray imgAnterior;
int iddovideo;

edit_video::edit_video(QWidget *parent, int x) :
    QDialog(parent),
    ui(new Ui::edit_video)
{
    ui->setupUi(this);
    check = false;
    id_person = x;
    QSqlQuery query;
    query.prepare("select * from video where id="+QString::number(x));
    if(query.exec())
    {
        query.first();
        ui->txt_id->setText(query.value(0).toString());
        ui->txt_name->setText(query.value(1).toString());
        ui->txt_tipo->setText(query.value(2).toString());
        ui->video_price->setValue(query.value(3).toInt());
        ui->video_age->setValue(query.value(4).toInt());
        ui->video_id->setValue(query.value(5).toInt());
        ui->video_idp->setValue(query.value(6).toInt());
        iddovideo = query.value(5).toInt();

        QByteArray outByteArray = query.value(7).toByteArray();
        QPixmap outPixmap = QPixmap();
        outPixmap.loadFromData(outByteArray);
        ui->label_image->setPixmap(outPixmap);
        ui->label_image->setScaledContents(true);
        imgAnterior = query.value(7).toByteArray();
    }
}

edit_video::~edit_video()
{
    delete ui;
}

void edit_video::on_btn_image_clicked()
{
    QString filtro = "Arquivos PNG (*.png*) ;; Arquivos JPEG (*.jpeg*) ;; Arquivos JPG (*.jpg*)";
    QString abrirArquivo=QFileDialog::getOpenFileName(this,"Abrir Imagem",QDir::homePath(),filtro);
    arquivo = new QFile(abrirArquivo);
    if(arquivo->isOpen())
    {
        QMessageBox::information(this, "","Arquivo aberto com sucesso !");
    }
    check=true;
}

void edit_video::on_btn_save_clicked()
{

    int c = 0;
    int z = 0;

    QString nome = ui->txt_name->text();
    QString tipo = ui->txt_tipo->text();
    QString preco = ui->video_price->text();
    QString idade = ui->video_age->text();
    QString idv = ui->video_id->text();
    QString idp = ui->video_idp->text();

    QVector <QString> t;
    QSqlQuery q;
    q.prepare("select id_person from person");

    if(q.exec())
    {
        while(q.next())
        {
            t.push_back(q.value(0).toString()); //Rodando todas as pessoas do banco de dados e botando seus ids em um vector
        }
    }
    for(int i = 0; i < t.size(); i++)
    {
        if(idp.toInt() == t.at(i).toInt())
        {
            c++; //Se existir uma pessoa com esse id no banco de dados, irá somar a essa variável
        }
    }

    QVector <QString> videoidcheck;
    QSqlQuery v;
    v.prepare("select id_video from video");
    if(v.exec())
    {
        while(v.next())
        {
            videoidcheck.push_back(v.value(0).toString()); //Rodando todos os vídeos do banco de dados e botando seus ids em um vector
        }
    }

    for(int i = 0; i < videoidcheck.size(); i++)
    {
        if(idv.toInt() == videoidcheck.at(i).toInt())
        {
            z++; //Se existir um vídeo com o mesmo id no banco de dados, irá somar a esssa variável
        }
    }

    //Verifica se o ID_person digitado existe no banco de dados ou se o ID_Peson digitado foi zero,
    //em ambos casos executa o código
    if(c != 0 || idp.toInt() == 0)
    {
        QSqlQuery query;
        int x;
        query.prepare("select age_person from person where id_person=:idp");
        query.bindValue(":idp",idp);
        if(query.exec())
        {
            while(query.next())
            {
                x = query.value(0).toInt();  //Irá pegar a idade da pessoa
            }
            if(x == ui->video_age->value() || x > ui->video_age->value() || ui->video_idp->value() == 0) //Verifica a idade da pessoa
            {
                if(z == 0 || iddovideo == ui->video_id->value()) //Verifica se o ID do vídeo já existe no bank, ou se ele não foi alterado na execução.
                {
                    if(!check)
                    {
                        QSqlQuery query;
                        QSqlQuery b;

                        query.prepare("delete from video where id="+QString::number(id_person));
                        query.exec();

                        //O ideal aqui seria usar update, mas como enfrentei problemas com isso, estou deletando o dado do bank e botando ele de novo totalmente igual

                        b.prepare("insert into video (id,name_video,type_video,price_video,age_video,id_video,idperson_video,imagem_video) values('"+QString::number(id_person)+"','"+nome+"','"+tipo+"','"+preco+"','"+idade+"','"+idv+"','"+idp+"',:imageData) ");
                        b.bindValue(":imageData", imgAnterior);

                        if(b.exec())
                        {
                            QMessageBox::information(this, "Êxito","Vídeo editado com sucesso !");
                            this->close();
                        }
                        else
                            QMessageBox::warning(this, "ERRO","Erro ao editar o vídeo!");
                    }
                    if(check)
                    {
                        if(!arquivo->open(QIODevice::ReadOnly))
                        {
                            QMessageBox::information(this, "","Erro ao abrir a imagem !");
                            this->close();
                        }
                        QByteArray inByteArray = arquivo->readAll();

                        QSqlQuery query;
                        QSqlQuery b;

                        query.prepare("delete from video where id="+QString::number(id_person));
                        query.exec();

                        b.prepare("insert into video (id,name_video,type_video,price_video,age_video,id_video,idperson_video,imagem_video) values('"+QString::number(id_person)+"','"+nome+"','"+tipo+"','"+preco+"','"+idade+"','"+idv+"','"+idp+"',:imageData) ");
                        b.bindValue(":imageData", inByteArray);

                        if(b.exec())
                        {
                            QMessageBox::information(this, "Êxito","Vídeo editado com sucesso !");
                            this->close();
                        }
                        else
                            QMessageBox::warning(this, "ERRO","Erro ao editar o vídeo!");
                    }
                }
                else
                {
                    QMessageBox::warning(this, "ERRO","Já existe um vídeo com esse ID !");
                }
            }
            else
            {
                QMessageBox::warning(this, "ERRO","Idade da pessoa é inferiror a faixa etária !");
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO","Erro ao abrir o banco de dados para analisar a idade da pessoa !");
            this->close();
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO","Não existe uma pessoa com esse ID no banco de dados !");
    }
}
