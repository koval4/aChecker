#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
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
    try {
        AutomatonsRegister::inst().get("begin")->run(ui->input_edit->toPlainText().toStdString());
        ui->output_tb->append(QString("All is ok."));
    } catch (ParseException& exc) {
        ui->output_tb->append(QString(exc.what()));
    } catch (std::exception& exc) {
        QMessageBox::critical(this, "Error occured!", exc.what());
    } catch (...) {
        QMessageBox::critical(this, "Error occured!", "Unhandled exception catched!");
    }
}

void MainWindow::on_actionOpen_Automaton_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, "Open file with finite-state automaton", ".", "Text files (*.txt *.fsa)");
    if (!filename.isNull())
        FileReader { filename.toStdString() }.read();
}
