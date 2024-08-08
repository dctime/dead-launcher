#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QProcess>
#include <iostream>

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

void MainWindow::on_playButton_clicked()
{
    QString text = ui->nameEdit->text();
    std::cout<<"\n * Program to demonstrate the usage of linux commands in qt * \n";

    QProcess OProcess;                  //Waits for execution to complete
    QString program = "dead/dead";
    QStringList arguments;
    arguments << text;
    OProcess.setProgram(program);
    OProcess.setArguments(arguments);
    OProcess.startDetached(); //Starts execution of command
    OProcess.waitForStarted();
    std::cout << "Process Started" << std::endl;

    exit(EXIT_SUCCESS);

    // QString StdOut      =   OProcess.readAllStandardOutput();  //Reads standard output
    // QString StdError    =   OProcess.readAllStandardError();   //Reads standard error

    // std::cout<<"\n Printing the standard output..........\n";
    // std::cout<<std::endl<<StdOut.toStdString();
    // std::cout<<"\n Printing the standard error..........\n";
    // std::cout<<std::endl<<StdError.toStdString();

    // std::cout<<"\n\n";
}

