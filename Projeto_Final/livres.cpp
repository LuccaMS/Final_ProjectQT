#include "livres.h"
#include "ui_livres.h"
#include "edit_livres.h"
#include <QtSql>
#include <QMessageBox>

livres::livres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::livres)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.prepare("select * from video where idperson_video=:idp");
    query.bindValue(":idp",0);
    if(query.exec())
    {
        int cont = 0;
        ui->livres_search->setColumnCount(7);
        while(query.next())
        {
            ui->livres_search->insertRow(cont);
            ui->livres_search->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->livres_search->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->livres_search->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->livres_search->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->livres_search->setItem(cont,4,new QTableWidgetItem(query.value(4).toString()));
            ui->livres_search->setItem(cont,5,new QTableWidgetItem(query.value(5).toString()));
            ui->livres_search->setItem(cont,6,new QTableWidgetItem(query.value(6).toString()));
            ui->livres_search->item(cont,0)->setTextAlignment(Qt::AlignCenter);
            ui->livres_search->item(cont,1)->setTextAlignment(Qt::AlignCenter);
            ui->livres_search->item(cont,2)->setTextAlignment(Qt::AlignCenter);
            ui->livres_search->item(cont,3)->setTextAlignment(Qt::AlignCenter);
            ui->livres_search->item(cont,4)->setTextAlignment(Qt::AlignCenter);
            ui->livres_search->item(cont,5)->setTextAlignment(Qt::AlignCenter);
            ui->livres_search->item(cont,6)->setTextAlignment(Qt::AlignCenter);
            ui->livres_search->setRowHeight(cont, 20);
            cont++;
        }
        ui->livres_search->setColumnWidth(0, 7);
        ui->livres_search->setColumnWidth(1,150);

        QStringList cabecalhos={"ID", "NOME DO VIDEO", "TIPO", "PREÇO", "FAIXA ETÁRIA", "ID DO VIDEO", "ID PERSON"};
        ui->livres_search->setHorizontalHeaderLabels(cabecalhos);
        ui->livres_search->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->livres_search->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->livres_search->verticalHeader()->setVisible(false);
        ui->livres_search->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->livres_search->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

livres::~livres()
{
    delete ui;
}

void livres::on_btn_alug_clicked()
{

    int linha = ui->livres_search->currentRow();
    int id=ui->livres_search->item(linha,0)->text().toInt();

    edit_livres e(this,id);
    e.exec();

    if(aux)
    {
        ui->livres_search->removeRow(linha);
    }
}
