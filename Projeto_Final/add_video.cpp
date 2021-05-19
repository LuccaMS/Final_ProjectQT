#include "add_video.h"
#include "ui_add_video.h"
#include <QDialog>
#include <QtSql>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QVector>

bool g;

add_video::add_video(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_video)
{
    ui->setupUi(this);
    g = false;
}

add_video::~add_video()
{
    delete ui;
}

void add_video::on_btn_salvar_clicked()
{
    QString nome, tipo, preco, age, idv, idp;
    nome = ui->txt_titulo->text();
    tipo = ui->txt_tipo->text();
    preco = ui->video_valor->text();
    age = ui->video_age->text();
    idv = ui->video_id->text();
    idp = ui->video_idalug->text();
    QVector <QString> t;
    QSqlQuery q;
    q.prepare("select id_person from person");

    QVector <QString> videoidcheck;
    QSqlQuery video;
    video.prepare("select id_video from video");

    if(q.exec() && video.exec()) //Verificando se abriu person e vídeo
    {
        while(q.next())
        {
            t.push_back(q.value(0).toString()); //Rodando todas as pessoas do banco de dados e botando seus ids em um vector
        }
        while(video.next())
        {
            videoidcheck.push_back(video.value(0).toString());  //Rodando todos os vídeos do banco de dados e botando seus ids em um vector
        }

        int v = 0;
        int c = 0;

        for(int i = 0; i < t.size();i++)
        {
            if(idp == t.at(i))
            {
                c++; //Se existir uma pessoa com esse id no banco de dados, irá somar a essa variável
            }
        }

        for(int i = 0; i < videoidcheck.size(); i++)
        {
            if(idv == videoidcheck.at(i))
            {
                v++; //Se existir um vídeo com o mesmo id no banco de dados, irá somar a esssa variável
            }
        }

        if(c != 0 || ui->video_idalug->value() == 0) //Olha se C é dif de zero, caso seja, existe alguem no banco de dados com o mesmo id digitado, ou se é zero
        {
            QSqlQuery query;
            int x;
            query.prepare("select age_person from person where id_person=:idp");
            query.bindValue(":idp",idp);
            if(query.exec())
            {
                while(query.next())
                {
                    x = query.value(0).toInt(); //Vai pegar a idade da pessoa com o idp
                }
                //Verifica se a idade é maior ou igual a da pessoa, ou se é zero, caso seja 0 é livre pq ninguém está alugando
                if(x == ui->video_age->value() || x > ui->video_age->value() || ui->video_idalug->value() == 0)
                {
                    if(v == 0) //Verifica se o id do vídeo inserido já existe no banco de dados
                    {
                        if(!g) //Verifica se o botão de inserir imagem foi clicado, se não, vai botar uma imagem padrão
                        {
                            arquivo = new QFile("../Projeto_Final/default-image.png"); //Imagem padrão na pasta do programa
                            if(!arquivo->open(QIODevice::ReadOnly))
                            {
                                QMessageBox::warning(this, "","Erro ao abrir a imagem padrão !");
                            }
                            QByteArray inByteArray = arquivo->readAll();

                            QSqlQuery query;
                            query.prepare("insert into video (name_video,type_video,price_video,age_video,id_video,idperson_video,imagem_video) values('"+nome+"','"+tipo+"','"+preco+"','"+age+"','"+idv+"','"+idp+"',:imageData) ");
                            query.bindValue(":imageData", inByteArray);

                            if(query.exec())
                            {
                                QMessageBox::information(this, "Êxito","Vídeo salvo com sucesso (Imagem Padrão) !");
                                this->close();
                            }
                            else
                            {
                                QMessageBox::warning(this, "ERRO","Erro ao salvar o vídeo (ERRO IMAGEM) !");
                                this->close();
                            }
                        }
                        if(g) //Caso tenha sido apertado, vai ser true e vai botar a imagem escolhida
                        {
                            if(!arquivo->open(QIODevice::ReadOnly))
                            {
                                QMessageBox::warning(this, "","Erro ao abrir a imagem !");
                            }
                            QByteArray inByteArray = arquivo->readAll();

                            QSqlQuery query;
                            query.prepare("insert into video (name_video,type_video,price_video,age_video,id_video,idperson_video,imagem_video) values('"+nome+"','"+tipo+"','"+preco+"','"+age+"','"+idv+"','"+idp+"',:imageData) ");
                            query.bindValue(":imageData", inByteArray);

                            if(query.exec())
                            {
                                QMessageBox::information(this, "Êxito","Vídeo salvo com sucesso (Imagem Escolhida) !");
                                this->close();
                            }
                            else
                            {
                                QMessageBox::warning(this, "ERRO","Erro ao salvar o vídeo (ERRO IMAGEM) !");
                                this->close();
                            }

                        }
                    }
                    else
                    {
                        QMessageBox::warning(this, "ERRO","Já existe um vídeo com esse ID , Digite outro !");
                    }
                }
                else
                {
                    QMessageBox::warning(this, "ERRO","Idade da pessoa é inferiror a faixa etária !");
                }
            }
            else
            {
                QMessageBox::warning(this, "ERRO","Erro ao analisar a idade da pessoa !");
                this->close();
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO","Não existe uma pessoa com esse ID no banco de dados!");
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO","Erro ao abrir o banco de dados !");
        this->close();
    }

}

void add_video::on_btn_imagem_clicked()
{
    QString filtro = "Arquivos PNG (*.png*) ;; Arquivos JPEG (*.jpeg*) ;; Arquivos JPG (*.jpg*)";
    QString abrirArquivo=QFileDialog::getOpenFileName(this,"Abrir Imagem",QDir::homePath(),filtro);
    arquivo = new QFile(abrirArquivo);
    if(arquivo->isOpen())
    {
        QMessageBox::information(this, "","Arquivo aberto com sucesso !");
    }
    g=true;
}
