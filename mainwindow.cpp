#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWidget>
#include "funzionilimoncello.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    switch (ui->sceltaCalcolo->currentIndex()) {
        case 0:
            ui->tentativoObiettivo->hide();
            ui->tentativoDati->hide();
            break;
        case 1:
            ui->tentativoPrecedente->hide();
            ui->tentativoDati->hide();
            break;
        case 2:
            ui->tentativoObiettivo->hide();
            ui->tentativoPrecedente->hide();
            break;
        default:
            ui->tentativoObiettivo->hide();
            ui->tentativoPrecedente->hide();
            ui->tentativoDati->hide();
            break;
    }
    ui->risultati->hide();
    ui->risultati_2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sceltaCalcolo_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->tentativoPrecedente->show();
        ui->tentativoObiettivo->hide();
        ui->tentativoDati->hide();
        break;
    case 1:
        ui->tentativoObiettivo->show();
        ui->tentativoPrecedente->hide();
        ui->tentativoDati->hide();
        break;
    case 2:
        ui->tentativoDati->show();
        ui->tentativoObiettivo->hide();
        ui->tentativoPrecedente->hide();
        break;
    default:
        ui->tentativoObiettivo->hide();
        ui->tentativoPrecedente->hide();
        ui->tentativoDati->hide();
        break;
    }
    ui->risultati->hide();
    ui->risultati_2->hide();
    ui->labelGradazioneAlcolica->clear();
    ui->labelDolcezza_2->clear();
    ui->grammiacqua->clear();
    ui->grammialcol->clear();
    ui->grammizucchero->clear();
}

void MainWindow::on_calcolaDaDati_clicked()
{
    Tentativi tentativo(ui->massaAlcool->value(),ui->massaZucchero->value(),ui->massaAcqua->value()); //alcol,zucchero,acqua
    ui->risultati->show();
    ui->labelDolcezza_2->setNum(tentativo.dolcezza);
    ui->labelGradazioneAlcolica->setNum(tentativo.gradazione);
}


void MainWindow::on_calcolaDaObiettivo_clicked()
{
    Tentativi tentativo(ui->massaScorze->value(),ui->gradazione->value(),ui->dolcezza->value());
    ui->risultati->show();
    ui->risultati_2->show();
    ui->labelDolcezza_2->setNum(tentativo.dolcezza);
    ui->labelGradazioneAlcolica->setNum(tentativo.gradazione);
    ui->grammiacqua->setNum(tentativo.massaAcqua);
    ui->grammialcol->setNum(tentativo.massaAlcool);
    ui->grammizucchero->setNum(tentativo.massaZucchero);
}


void MainWindow::on_calcoloDaTentativo_clicked()
{
    Tentativi tentativo(0,0,0);
    double buccelimone = ui->massaScorze1->value();
    switch (ui->sceltaTentativo->currentIndex()) {
        default:
            Tentativi t(TentativiPassati::primotentativo,buccelimone);
            tentativo = t;
    }
    ui->risultati->show();
    ui->risultati_2->show();
    ui->labelDolcezza_2->setNum(tentativo.dolcezza);
    ui->labelGradazioneAlcolica->setNum(tentativo.gradazione);
    ui->grammiacqua->setNum(tentativo.massaAcqua);
    ui->grammialcol->setNum(tentativo.massaAlcool);
    ui->grammizucchero->setNum(tentativo.massaZucchero);
}

