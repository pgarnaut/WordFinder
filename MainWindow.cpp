#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QString>

#include <stdio.h>

#include <WordFinder.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->ui->mainStatusBar->showMessage("using dictionary: ... who knows?", 9999999);
    this->ui->mainStatusBar->setFocus();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionSet_Dictionary_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Dictionary"), "", tr(""));

    printf("Path: %s\n", (const char *)(fileName.data()));
    this->ui->mainStatusBar->showMessage(fileName, 9999999);
    this->finder.setDictionary("using dictionary: " + fileName.toStdString());
}

void MainWindow::on_solveButton_clicked() {
    printf("kowabunga\n");
    printf("%s\n", this->ui->possibleLetters->text().toStdString().c_str());
    printf("%s\n", this->ui->requiredLetters->text().toStdString().c_str());
    for (auto word : this->finder.solve(this->ui->possibleLetters->text().toStdString(),
                       this->ui->requiredLetters->text().toStdString())) {

        new QListWidgetItem(tr(word.c_str()), this->ui->resultList);
    }
}
