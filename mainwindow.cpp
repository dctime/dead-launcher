#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QProcess>
#include <iostream>
#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *conn;
    sql::ConnectOptionsMap connectionProperties;

    std::string name;
    int timeInSeconds;

    try {

        driver = sql::mysql::get_mysql_driver_instance();
        conn = driver->connect("sql12.freemysqlhosting.net",
                               "sql12724310", "xffMZcQICr");
        conn->setSchema("sql12724310");
        std::unique_ptr<sql::Statement> statement(conn->createStatement());
        std::unique_ptr<sql::ResultSet> resultSet(
            statement->executeQuery("SELECT * FROM LongestSurvivalTime ORDER BY "
                                    "TimeInSeconds DESC LIMIT 100"));

        while (resultSet->next()) {
            name = resultSet->getString("Name");
            timeInSeconds = resultSet->getInt("TimeInSeconds");
            const QString nameQString = QString::fromStdString(name);
            std::string timeFormatted = std::to_string(timeInSeconds);
            const QString timeFormattedQString = QString::fromStdString(timeFormatted);
            ui->longestTableWidget->insertRow(ui->longestTableWidget->rowCount());
            ui->longestTableWidget->setItem(ui->longestTableWidget->rowCount()-1, 0, new QTableWidgetItem(nameQString));
            ui->longestTableWidget->setItem(ui->longestTableWidget->rowCount()-1, 1, new QTableWidgetItem(timeFormattedQString));
                    std::cout << "Name: " << name << ", TimeInSeconds: " << timeInSeconds
                << std::endl;
            std::cout << "added a row" << std::endl;
        }
    } catch (sql::SQLException &e) {
        std::cout << "# Err: " << e.what();
        std::cout << " (My SQL Error Code: " << e.getErrorCode();
        std::cout << ", SQL_STATE: " << e.getSQLState() << " )" << std::endl;
        if (e.getErrorCode() == 2005) {
            std::cout << "Offline" << std::endl;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{
    QString text = ui->nameEdit->text();

    for (char c : text.toStdString()) {
        if (c == ' ') {
            QString errorText = "It is not allowed to have spaces in it.";
            ui->errorMessageLabel->setText(errorText);
            ui->nameEdit->clear();
            ui->nameEdit->setFocus();
            QString style = "border-color: rgb(192, 28, 40); border-width : 1.2px; border-style:inset;";
            ui->nameEdit->setStyleSheet(style);
            return;
        }
    }

    QProcess OProcess;                  //Waits for execution to complete
    QString program = "dead/dead";
    QStringList arguments;
    arguments << text;
    OProcess.setProgram(program);
    OProcess.setArguments(arguments);
    ui->playButton->setEnabled(false);
    OProcess.startDetached(); //Starts execution of command
    OProcess.waitForStarted();
    std::cout << "Process Started" << std::endl;
}

