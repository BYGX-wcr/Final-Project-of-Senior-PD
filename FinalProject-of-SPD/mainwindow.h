#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QInputDialog>
#include <QVector>
#include <QCloseEvent>
#include "stuinfomanagesystem.h"

#define DEFAULT_DB "student_db"
#define CHANGE_TAG "*"

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

    StuInfoManageSystem dbModel;
    QSqlRecord recordCache;

    //initial the window
    void initializeFileMenu(QMenuBar *menuBar);
    void initializeEditMenu(QMenuBar *menuBar);
    void initializeHelpMenu(QMenuBar *menuBar);
    void initializeToolbar(QToolBar *toolBar);

    //regulate tables
    void createTable();
    void openTable();
    void closeTable();
    void saveTable();
    void saveAllTable();

    //regulate row data
    void addRow();
    void alterRow();
    void removeRow();
    void sortRowsById();
    void sortRowsByName();

    //regulate views
    void saveViewChange(int index);
    void addChangeTag(int index);
    void addView(QSqlTableModel* newModel);
    
    //Special slots
    void recvRecord(QSqlRecord arg);
    void closeEvent(QCloseEvent* event);
    void openAboutDialog();
    void openURLDialog();
};

#endif // MAINWINDOW_H
