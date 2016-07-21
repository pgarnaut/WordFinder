#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WordFinder.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSet_Dictionary_triggered();

    void on_solveButton_clicked();

private:
    void showError(const std::string &msg);
    Ui::MainWindow *ui;
    WordFinder finder;
};

#endif // MAINWINDOW_H
