#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QStringList files_names = QFileDialog::getOpenFileNames(this, "Cambiar nombre", "E:/games/Invincible");
    QString file_name;
    foreach(file_name, files_names){
        QFile file(file_name);
        QStringList split = file_name.split("/");
        QString newName = split.last();

        split.removeLast();
        QString dir = split.join("/");

        if(newName.contains("The Boys") && newName.contains("#")){
            QString number = newName.split("#").last().replace(".mp4", "").trimmed();
            number = number.split(" ").first().trimmed();
            while(number.length() < 3){
                number.prepend("0");
            }

            newName = newName.split("#").first().trimmed();
            newName = newName.replace("The Boys", "").trimmed();
            newName = newName.replace("_", "").trimmed();

            newName = "The Boys #" + number + " - " + newName + ".mp4";
            newName.prepend(dir + "/");
            if(file.exists()){
                file.rename(newName);
            }
        }

    }
    QMessageBox::information(this, "Exito", "Convertido correctamente");
}
