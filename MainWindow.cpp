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
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionSet_Dictionary_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Dictionary"), "", tr(""));

    printf("Path: %s\n", (const char *)(fileName.data()));
    this->ui->textBrowser1->setText(fileName);
    this->finder.setDictionary(fileName.toStdString());
}
