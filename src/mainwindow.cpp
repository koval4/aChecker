#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include "filereader.h"
#include "automatonsregister.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_parse_btn_clicked() {
    QString line;
    ui->input_edit->setPlainText(line);
    AutomatonsRegister::inst().get("begin").run(line.toStdString());
}

void MainWindow::on_actionOpen_Automaton_triggered() {
    FileReader {
        QFileDialog::getOpenFileName(this, "Open file with finite-state automaton").toStdString()
    }.read();
}
