#include "search_person.h"
#include "ui_search_person.h"
#include "edit_person.h"
#include <QtSql>
#include <QMessageBox>

search_person::search_person(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search_person)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.prepare("select * from person");
    if(query.exec())
    {
        int cont = 0;
        ui->person_search->setColumnCount(4);
        while(query.next())
        {
            ui->person_search->insertRow(cont);
            ui->person_search->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->person_search->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->person_search->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->person_search->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->person_search->item(cont,0)->setTextAlignment(Qt::AlignCenter);
            ui->person_search->item(cont,1)->setTextAlignment(Qt::AlignCenter);
            ui->person_search->item(cont,2)->setTextAlignment(Qt::AlignCenter);
            ui->person_search->item(cont,3)->setTextAlignment(Qt::AlignCenter);

            ui->person_search->setRowHeight(cont, 20);
            cont++;
        }
        ui->person_search->setColumnWidth(0, 4);
        ui->person_search->setColumnWidth(2,200);

        QStringList cabecalhos={"ID", "ID_PERSON", "NAME_PERSON", "AGE_PERSON"};
        ui->person_search->setHorizontalHeaderLabels(cabecalhos);
        ui->person_search->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->person_search->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->person_search->verticalHeader()->setVisible(false);
        ui->person_search->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->person_search->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    else
        QMessageBox::warning(this, "ERRO", "Erro ao pesquisar na tabela de PERSON");
}

search_person::~search_person()
{
    delete ui;
}

void search_person::on_btn_edit_clicked()
{
    int linha = ui->person_search->currentRow();
    int id=ui->person_search->item(linha,0)->text().toInt();

    edit_person a_edit(this,id);
    a_edit.exec();
    QSqlQuery query;
    query.prepare("select * from person where id="+QString::number(id));
    if(query.exec())
    {
        query.first();
        ui->person_search->setItem(linha, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->person_search->setItem(linha, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->person_search->setItem(linha, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->person_search->item(linha,0)->setTextAlignment(Qt::AlignCenter);
        ui->person_search->item(linha,1)->setTextAlignment(Qt::AlignCenter);
        ui->person_search->item(linha,2)->setTextAlignment(Qt::AlignCenter);
        ui->person_search->item(linha,3)->setTextAlignment(Qt::AlignCenter);
    }
}

void search_person::on_btn_delete_clicked()
{
    int linha=ui->person_search->currentRow();
    int id=ui->person_search->item(linha, 0)->text().toInt();
    QSqlQuery query;
    query.prepare("delete from person where id="+QString::number(id));
    if(query.exec())
    {
        ui->person_search->removeRow(linha);
        QMessageBox::information(this, "Êxito", "Pessoa excluida do banco de dados com sucesso !");
    }
    else
        QMessageBox::warning(this, "ERRO", "Erro ao excluir a pessoa do banco de dados !");
}
