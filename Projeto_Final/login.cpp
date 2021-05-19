#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

static QSqlDatabase bancoDeDados=QSqlDatabase::addDatabase("QSQLITE");

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    bancoDeDados.setDatabaseName("../Projeto_Final/database/database.db");
    if(!bancoDeDados.open())
    {
        QMessageBox::warning(this, "ERRO", "Banco de dados não foi aberto com sucesso");
    }
}

Login::~Login()
{
    delete ui;
}


void Login::on_btn_login_clicked()
{
    QString username=ui->txt_username->text();
    QString password=ui->txt_password->text();
    if(!bancoDeDados.isOpen())
    {
       QMessageBox::warning(this, "ERRO", "Banco de dados não está aberto");
        return;
    }

    QSqlQuery query;
    if(query.exec("select * from users where username='"+username+"' and password='"+password+"'"))
    {
     int cont=0;
     while(query.next())
     {
         cont++;
     }
     if(cont>0)
     {
         this->close();
         central acentral;
         acentral.setModal(true);
         acentral.exec();
     }
     else
     {
         ui->txt_username->clear();
         ui->txt_password->clear();
         QMessageBox::warning(this, "ERRO", "username e senha incorretas");
     }
    }
}
