#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>

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
    QString replacement = ui->le_replacement_text->text().trimmed();
    QString splitter = ui->le_splitter->text().trimmed();
    QString format = ui->le_format->text().trimmed();

    QStringList files_names = QFileDialog::getOpenFileNames(this, "Seleccione los archivos a modificar", "E:/games/Invincible");
    QString file_name;
    foreach(file_name, files_names){
        QFile file(file_name);
        QStringList split = file_name.split("/");
        QString newName = split.last();

        split.removeLast();
        QString dir = split.join("/");

        if(newName.contains(replacement) && newName.contains(splitter)){
            QString number = newName.split(splitter).last().replace(format, "").trimmed();
            number = number.split(" ").first().trimmed();
            while(number.length() < 3){
                number.prepend("0");
            }

            newName = newName.split(splitter).first().trimmed();
            newName = newName.replace(replacement, "").trimmed();
            newName = newName.replace("_", "").trimmed();

            newName = replacement + " " + splitter + number + " - " + newName + format;
            newName.prepend(dir + "/");
            if(file.exists()){
                file.rename(newName);
            }
        }

    }
}
