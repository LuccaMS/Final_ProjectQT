#include "search_video.h"
#include "ui_search_video.h"
#include "edit_video.h"
#include "details_video.h"
#include <QtSql>
#include <QMessageBox>
#include <QVector>

search_video::search_video(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search_video)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.prepare("select * from video");
    if(query.exec())
    {
        int cont = 0;
        ui->video_search->setColumnCount(7);
        while(query.next())
        {
            ui->video_search->insertRow(cont);
            ui->video_search->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->video_search->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->video_search->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->video_search->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->video_search->setItem(cont,4,new QTableWidgetItem(query.value(4).toString()));
            ui->video_search->setItem(cont,5,new QTableWidgetItem(query.value(5).toString()));
            ui->video_search->setItem(cont,6,new QTableWidgetItem(query.value(6).toString()));
            ui->video_search->item(cont,0)->setTextAlignment(Qt::AlignCenter);
            ui->video_search->item(cont,1)->setTextAlignment(Qt::AlignCenter);
            ui->video_search->item(cont,2)->setTextAlignment(Qt::AlignCenter);
            ui->video_search->item(cont,3)->setTextAlignment(Qt::AlignCenter);
            ui->video_search->item(cont,4)->setTextAlignment(Qt::AlignCenter);
            ui->video_search->item(cont,5)->setTextAlignment(Qt::AlignCenter);
            ui->video_search->item(cont,6)->setTextAlignment(Qt::AlignCenter);
            ui->video_search->setRowHeight(cont, 20);
            cont++;
        }
        ui->video_search->setColumnWidth(0, 7);
        ui->video_search->setColumnWidth(1,150);

        QStringList cabecalhos={"ID", "NOME DO VIDEO", "TIPO", "PREÇO", "FAIXA ETÁRIA", "ID DO VIDEO", "ID PERSON"};
        ui->video_search->setHorizontalHeaderLabels(cabecalhos);
        ui->video_search->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->video_search->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->video_search->verticalHeader()->setVisible(false);
        ui->video_search->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->video_search->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    else
        QMessageBox::warning(this, "ERRO", "Erro ao pesquisar na tabela de PERSON");

}

search_video::~search_video()
{
    delete ui;
}

void search_video::on_btn_edit_clicked()
{
    int linha = ui->video_search->currentRow();
    int id=ui->video_search->item(linha,0)->text().toInt();

    edit_video e_edit(this,id);
    e_edit.exec();
    QSqlQuery query;
    query.prepare("select * from video where id="+QString::number(id));
    if(query.exec())
    {
        query.first();
        ui->video_search->setItem(linha,0,new QTableWidgetItem(query.value(0).toString()));
        ui->video_search->setItem(linha,1,new QTableWidgetItem(query.value(1).toString()));
        ui->video_search->setItem(linha,2,new QTableWidgetItem(query.value(2).toString()));
        ui->video_search->setItem(linha,3,new QTableWidgetItem(query.value(3).toString()));
        ui->video_search->setItem(linha,4,new QTableWidgetItem(query.value(4).toString()));
        ui->video_search->setItem(linha,5,new QTableWidgetItem(query.value(5).toString()));
        ui->video_search->setItem(linha,6,new QTableWidgetItem(query.value(6).toString()));
        ui->video_search->item(linha,0)->setTextAlignment(Qt::AlignCenter);
        ui->video_search->item(linha,1)->setTextAlignment(Qt::AlignCenter);
        ui->video_search->item(linha,2)->setTextAlignment(Qt::AlignCenter);
        ui->video_search->item(linha,3)->setTextAlignment(Qt::AlignCenter);
        ui->video_search->item(linha,4)->setTextAlignment(Qt::AlignCenter);
        ui->video_search->item(linha,5)->setTextAlignment(Qt::AlignCenter);
        ui->video_search->item(linha,6)->setTextAlignment(Qt::AlignCenter);
        ui->video_search->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->video_search->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    }

}

void search_video::on_btn_delet_clicked()
{
    int linha=ui->video_search->currentRow();
    int id=ui->video_search->item(linha, 0)->text().toInt();
    QSqlQuery query;
    query.prepare("delete from video where id="+QString::number(id));
    if(query.exec())
    {
        ui->video_search->removeRow(linha);
        QMessageBox::information(this, "Êxito", "Vídeo excluido com sucesso");
    }
    else
        QMessageBox::warning(this, "ERRO", "Erro ao excluir o vídeo");

}

void search_video::on_btn_detail_clicked()
{
    int linha=ui->video_search->currentRow();
    int id=ui->video_search->item(linha, 0)->text().toInt();
    details_video detail(this,id);
    detail.exec();
}

void search_video::on_btn_desalug_clicked()
{
    QString x = "0";

    int linha = ui->video_search->currentRow();
    int id = ui->video_search->item(linha,0)->text().toInt();
    QSqlQuery query;
    query.prepare("update video set idperson_video = '"+x+"' where id="+QString::number(id));
    if(ui->video_search->item(linha,6)->text().toInt() == 0)
    {
        QMessageBox::warning(this, "ERRO", "Vídeo já se encontra desalugado");
    }
    else
    {
        if(query.exec())
        {
            QSqlQuery uptable;
            uptable.prepare("select idperson_video from video where id="+QString::number(id));
            if(uptable.exec())
            {
                while(uptable.next())
                {
                    ui->video_search->setItem(linha,6,new QTableWidgetItem(uptable.value(0).toString()));
                    ui->video_search->item(linha,6)->setTextAlignment(Qt::AlignCenter);
                }
            }
            else
            {
                QMessageBox::warning(this, "ERRO", "Erro ao atualizar a tabela");
            }

            QMessageBox::information(this, "Êxito", "Vídeo desalugado com sucesso");
        }
        else
            QMessageBox::warning(this, "ERRO", "Erro ao desalugar o vídeo (query não executado)");
    }

}
