#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->clear();
    this->showMaximized();
    this->setWindowTitle("Student Information Management System");
    this->setCentralWidget(ui->tabWidget);

    initializeFileMenu(ui->menuBar);
    initializeEditMenu(ui->menuBar);
    initializeToolbar(ui->mainToolBar);

    if (!dbModel.connect(DEFAULT_DB))
    {
        QMessageBox::warning(this, "Warning!", "Cannot connect to default database!");
    }

    viewList.resize(dbModel.readStuInfo());

    for (int i = 0; i < viewList.size(); ++i)
    {
        viewList[i] = new QTableView(ui->tabWidget);
        viewList[i]->setModel(dbModel.getModel(i));
        ui->tabWidget->addTab(viewList[i], dbModel.getTable(i));
    }
}

void MainWindow::initializeFileMenu(QMenuBar *menuBar)
{//initialize the menu bar
    QMenu *fileMenu = menuBar->addMenu(tr("File"));

    QMenu *DBMenu = new QMenu(tr("Database Management"), fileMenu);
    fileMenu->addMenu(DBMenu);

    fileMenu->addSeparator();

    QAction *createAction = new QAction(tr("New"), fileMenu);
    fileMenu->addAction(createAction);
    QAction *openAction = new QAction(tr("Open"), fileMenu);
    fileMenu->addAction(openAction);
    QAction *closeAction = new QAction(tr("Close"), fileMenu);
    fileMenu->addAction(closeAction);
    QAction *saveAction = new QAction(tr("Save"), fileMenu);
    fileMenu->addAction(saveAction);

    fileMenu->addSeparator();

    QAction *exitAction = new QAction(tr("Exit"), fileMenu);
    fileMenu->addAction(exitAction);
}

void MainWindow::initializeEditMenu(QMenuBar *menuBar)
{
    QMenu *editMenu = menuBar->addMenu(tr("Edit"));

    QAction *withdrawAction = new QAction(tr("Revoke"), editMenu);
    editMenu->addAction(withdrawAction);

    editMenu->addSeparator();

    QAction *addinfoAction = new QAction(tr("Add"), editMenu);
    editMenu->addAction(addinfoAction);
    QAction *alterinfoAction = new QAction(tr("Alter"), editMenu);
    editMenu->addAction(alterinfoAction);
    QAction *removeinfoAction = new QAction(tr("Remove"), editMenu);
    editMenu->addAction(removeinfoAction);

    editMenu->addSeparator();

    QAction *sortAction = new QAction(tr("Sort"), editMenu);
    editMenu->addAction(sortAction);
}

void MainWindow::initializeToolbar(QToolBar *toolBar)
{
    QAction *createAction = new QAction(QIcon(tr(":/icon/create")), tr("New"), toolBar);
    toolBar->addAction(createAction);
    QAction *openAction = new QAction(QIcon(tr(":/icon/open")), tr("Open"), toolBar);
    toolBar->addAction(openAction);
    QAction *saveAction = new QAction(QIcon(tr(":/icon/save")), tr("Save"), toolBar);
    toolBar->addAction(saveAction);

    toolBar->addSeparator();

    QAction *addinfoAction = new QAction(QIcon(tr(":/icon/add")), tr("Add"), toolBar);
    toolBar->addAction(addinfoAction);
    QAction *alterinfoAction = new QAction(QIcon(tr(":/icon/alter")), tr("Alter"), toolBar);
    toolBar->addAction(alterinfoAction);
    QAction *removeinfoAction = new QAction(QIcon(tr(":/icon/remove")), tr("Remove"), toolBar);
    toolBar->addAction(removeinfoAction);
    QAction *sortAction = new QAction(QIcon(tr(":/icon/sort")), tr("Sort"), toolBar);
    toolBar->addAction(sortAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}
