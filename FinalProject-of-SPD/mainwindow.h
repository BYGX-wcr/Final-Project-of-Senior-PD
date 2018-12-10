#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QVector>
#include "stuinfomanagesystem.h"

#define DEFAULT_DB "student_db"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVector<QTableView*> viewList;

    StuInfoManageSystem dbModel;

    void initializeFileMenu(QMenuBar *menuBar);
    void initializeEditMenu(QMenuBar *menuBar);
    void initializeToolbar(QToolBar *toolBar);
};

#endif // MAINWINDOW_H
