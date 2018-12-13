#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recorddialog.h"

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
    initializeHelpMenu(ui->menuBar);
    initializeToolbar(ui->mainToolBar);

    if (!dbModel.connect(DEFAULT_DB))
    {
        QMessageBox::warning(this, "Warning!", "Cannot connect to default database!");
    }

    int viewNum = dbModel.readStuInfo();

    for (int i = 0; i < viewNum; ++i)
    {
        addView(dbModel.getModel(i));
    }
}

void MainWindow::initializeFileMenu(QMenuBar *menuBar)
{//initialize the menu bar
    QMenu *fileMenu = menuBar->addMenu(tr("File"));

    QAction *createAction = new QAction(tr("New"), fileMenu);
    connect(createAction, &QAction::triggered, this, &MainWindow::createTable);
    fileMenu->addAction(createAction);
    QAction *openAction = new QAction(tr("Open"), fileMenu);
    connect(openAction, &QAction::triggered, this, &MainWindow::openTable);
    fileMenu->addAction(openAction);
    QAction *closeAction = new QAction(tr("Close"), fileMenu);
    connect(closeAction, &QAction::triggered, this, &MainWindow::closeTable);
    fileMenu->addAction(closeAction);

    fileMenu->addSeparator();

    QAction *saveAction = new QAction(tr("Save"), fileMenu);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveTable);
    fileMenu->addAction(saveAction);
    QAction *saveAllAction = new QAction(tr("Save All"), fileMenu);
    connect(saveAllAction, &QAction::triggered, this, &MainWindow::saveAllTable);
    fileMenu->addAction(saveAllAction);

    fileMenu->addSeparator();

    QAction *exitAction = new QAction(tr("Exit"), fileMenu);
    fileMenu->addAction(exitAction);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
}
void MainWindow::initializeEditMenu(QMenuBar *menuBar)
{
    QMenu *editMenu = menuBar->addMenu(tr("Edit"));

    QAction *addinfoAction = new QAction(tr("Add"), editMenu);
    editMenu->addAction(addinfoAction);
    connect(addinfoAction, &QAction::triggered, this, &MainWindow::addRow);
    QAction *alterinfoAction = new QAction(tr("Alter"), editMenu);
    editMenu->addAction(alterinfoAction);
    connect(alterinfoAction, &QAction::triggered, this, &MainWindow::alterRow);
    QAction *removeinfoAction = new QAction(tr("Remove"), editMenu);
    editMenu->addAction(removeinfoAction);
    connect(removeinfoAction, &QAction::triggered, this, &MainWindow::removeRow);

    editMenu->addSeparator();

    QMenu *sortMenu = new QMenu(tr("Sort"), editMenu);
    editMenu->addMenu(sortMenu);
    QAction *sortById = new QAction(tr("Sort by Student Id"), sortMenu);
    connect(sortById, &QAction::triggered, this, &MainWindow::sortRowsById);
    QAction *sortByName = new QAction(tr("Sort By Name"), sortMenu);
    connect(sortByName, &QAction::triggered, this, &MainWindow::sortRowsByName);
    sortMenu->addAction(sortById);
    sortMenu->addAction(sortByName);
}
void MainWindow::initializeHelpMenu(QMenuBar *menuBar)
{
    QMenu* helpMenu = new QMenu(tr("Help"), menuBar);
    QAction* aboutAction = new QAction(tr("About"), menuBar);
    helpMenu->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::openAboutDialog);
    QAction* codeAction = new QAction(tr("Source Code URL"), menuBar);
    helpMenu->addAction(codeAction);
    connect(codeAction, &QAction::triggered, this, &MainWindow::openURLDialog);

    menuBar->addMenu(helpMenu);
}
void MainWindow::initializeToolbar(QToolBar *toolBar)
{
    QAction *createAction = new QAction(QIcon(tr(":/icon/create")), tr("New"), toolBar);
    toolBar->addAction(createAction);
    connect(createAction, &QAction::triggered, this, &MainWindow::createTable);
    QAction *openAction = new QAction(QIcon(tr(":/icon/open")), tr("Open"), toolBar);
    toolBar->addAction(openAction);
    connect(openAction, &QAction::triggered, this, &MainWindow::openTable);
    QAction *closeAction = new QAction(QIcon(tr(":/icon/close")), tr("Close"), toolBar);
    toolBar->addAction(closeAction);
    connect(closeAction, &QAction::triggered, this, &MainWindow::closeTable);
    QAction *saveAction = new QAction(QIcon(tr(":/icon/save")), tr("Save"), toolBar);
    toolBar->addAction(saveAction);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveTable);

    toolBar->addSeparator();

    QAction *addinfoAction = new QAction(QIcon(tr(":/icon/add")), tr("Add"), toolBar);
    toolBar->addAction(addinfoAction);
    connect(addinfoAction, &QAction::triggered, this, &MainWindow::addRow);
    QAction *alterinfoAction = new QAction(QIcon(tr(":/icon/alter")), tr("Alter"), toolBar);
    toolBar->addAction(alterinfoAction);
    connect(alterinfoAction, &QAction::triggered, this, &MainWindow::alterRow);
    QAction *removeinfoAction = new QAction(QIcon(tr(":/icon/remove")), tr("Remove"), toolBar);
    toolBar->addAction(removeinfoAction);
    connect(removeinfoAction, &QAction::triggered, this, &MainWindow::removeRow);
}

void MainWindow::createTable()
{
    bool ok;
    QString tableName = QInputDialog::getText(this, tr("New Table"), tr("Input the name of new table"), QLineEdit::Normal, "", &ok);

    if (ok && tableName.size() != 0)
    {
        QSqlTableModel* newModel = dbModel.createModel("student_" + tableName);
        if (newModel != NULL)
                addView(newModel);
        else
        {
            QMessageBox::warning(this, "Warning!", "Cannot create table:" + tableName);
        }
    }
}
void MainWindow::openTable()
{
    bool ok;
    QString tableName = QInputDialog::getText(this, tr("Open a Table"), tr("Input the name of the table"), QLineEdit::Normal, "", &ok);

    if (ok && tableName.size() != 0)
    {
        tableName = "student_" + tableName;
        for (int i = 0; i < ui->tabWidget->count(); ++i)
        {
            if (ui->tabWidget->tabText(i) == tableName) // The table has been open
            {
                ui->tabWidget->setCurrentIndex(i);
                return;
            }
        }

        QSqlTableModel* newModel = dbModel.getModel(tableName);
        if (newModel != NULL)
        {
            addView(newModel);
            ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
        }
        else
        {
            QMessageBox::warning(this, tr("Database Error!"), tr("Table do not exist: ") + tableName);
        }
    }
}
void MainWindow::closeTable()
{
    int index = ui->tabWidget->currentIndex();
    if (ui->tabWidget->tabText(index).endsWith(CHANGE_TAG))
    {//indicate that the table has been altered
        if (QMessageBox::question(this, "Notification", "表格已被修改，是否保存？", QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Save) == QMessageBox::Save)
        {
            saveViewChange(index);
        }
    }

    ui->tabWidget->removeTab(index);
    dbModel.removeModel(index);
}
void MainWindow::saveTable()
{
    int index = ui->tabWidget->currentIndex();
    saveViewChange(index);
}
void MainWindow::saveAllTable()
{
    if (!dbModel.submitAllChange())
    {
        QMessageBox::critical(this, "Database Error!", "Cannot submit all changes!");
    }

    for (int i = 0; i < ui->tabWidget->count(); ++i)
    {
        if (ui->tabWidget->tabText(i).endsWith(CHANGE_TAG))
        {
            //eliminate the '*'
            QString tableName = ui->tabWidget->tabText(i);
            tableName.remove(tableName.size() - tr(CHANGE_TAG).size(), 1);
            ui->tabWidget->setTabText(i, tableName);
        }
    }
}

void MainWindow::addRow()
{
    int tableIndex = ui->tabWidget->currentIndex();

    QTableView* curTable = dynamic_cast<QTableView*>(ui->tabWidget->currentWidget());
    if (curTable == NULL)
    {
        qDebug() << "Unknown Error occured when add a row into table #" << tableIndex;
        return;
    }

    RecordDialog dialog(this);
    connect(&dialog, &RecordDialog::returnRecord, this, &MainWindow::recvRecord);
    if (dialog.exec() == QDialog::Accepted)
    {
        if (!dbModel.addInfo(recordCache, tableIndex))
        {
            QMessageBox::critical(this, tr("Database Error!"), "Can not insert the record into table " + ui->tabWidget->tabText(tableIndex));
            return;
        }
        addChangeTag(tableIndex);
        curTable->setModel(dbModel.getModel(tableIndex));
    }
}
void MainWindow::removeRow()
{
    int tableIndex = ui->tabWidget->currentIndex();

    QTableView* curTable = dynamic_cast<QTableView*>(ui->tabWidget->currentWidget());
    if (curTable == NULL)
    {
        qDebug() << "Unknown Error occured when add a row into table #" << tableIndex;
        return;
    }

    if (dbModel.removeInfo(tableIndex, curTable->currentIndex().row()))
    {
        addChangeTag(tableIndex);
        curTable->setModel(dbModel.getModel(tableIndex));
    }
}
void MainWindow::alterRow()
{
    int tableIndex = ui->tabWidget->currentIndex();

    QTableView* curTable = dynamic_cast<QTableView*>(ui->tabWidget->currentWidget());
    if (curTable == NULL)
    {
        qDebug() << "Unknown Error occured when add a row into table #" << tableIndex;
        return;
    }

    RecordDialog dialog(this, dbModel.getModel(tableIndex)->record(curTable->currentIndex().row()));
    connect(&dialog, &RecordDialog::returnRecord, this, &MainWindow::recvRecord);
    if (dialog.exec() == QDialog::Accepted)
    {
        if (!dbModel.setInfo(recordCache, tableIndex, curTable->currentIndex().row()))
        {
            QMessageBox::critical(this, tr("Database Error!"), "Can not alter the record in table " + ui->tabWidget->tabText(tableIndex));
            return;
        }
        addChangeTag(tableIndex);
        curTable->setModel(dbModel.getModel(tableIndex));
    }
}
void MainWindow::sortRowsById()
{
    for (int i = 0; i < ui->tabWidget->count(); ++i)
    {
        dbModel.getModel(i)->sort(StuInfoManageSystem::Sno, Qt::AscendingOrder);
    }
}
void MainWindow::sortRowsByName()
{
    for (int i = 0; i < ui->tabWidget->count(); ++i)
    {
        dbModel.getModel(i)->sort(StuInfoManageSystem::Sname, Qt::AscendingOrder);
    }
}

void MainWindow::saveViewChange(int index)
{
    if (!dbModel.submitChange(index))
    {
        QMessageBox::critical(this, tr("Database Error!"), "Can not submit change on table " + ui->tabWidget->tabText(index));
        return;
    }

    //eliminate the '*'
    QString tableName = ui->tabWidget->tabText(index);
    tableName.remove(tableName.size() - tr(CHANGE_TAG).size(), 1);
    ui->tabWidget->setTabText(index, tableName);
}
void MainWindow::addChangeTag(int index)
{
    if (!ui->tabWidget->tabText(index).endsWith(CHANGE_TAG))
        ui->tabWidget->setTabText(index, ui->tabWidget->tabText(index) + CHANGE_TAG);
}
void MainWindow::addView(QSqlTableModel *newModel)
{
    QTableView* ptr = new QTableView(ui->tabWidget);
    ptr->setModel(newModel);
    ptr->setSelectionMode(QAbstractItemView::SingleSelection);
    ptr->setSelectionBehavior(QAbstractItemView::SelectRows);
    ptr->resizeColumnsToContents();
    ptr->setColumnWidth(StuInfoManageSystem::Birthday, 200);
    ptr->setColumnWidth(StuInfoManageSystem::Nativeplace, 200);
    int blank = this->width() - ptr->width();
    ptr->setColumnWidth(StuInfoManageSystem::Address, blank + ptr->columnWidth(StuInfoManageSystem::Address));
    ptr->setEditTriggers(QTableView::NoEditTriggers);

    ui->tabWidget->addTab(ptr, newModel->tableName());
}

void MainWindow::recvRecord(QSqlRecord arg)
{
    recordCache = arg;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    bool dirty = false;
    for (int i = 0; i < ui->tabWidget->count(); ++i)
    {
        if (ui->tabWidget->tabText(i).endsWith(CHANGE_TAG))
        {//indicate that a table has been altered
            dirty = true;
        }
    }

    if (dirty)
    {
        QMessageBox::StandardButton res = QMessageBox::question(this, "Notification", "表格已被修改，是否保存？", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);
        if (res == QMessageBox::Save)
        {
            dbModel.submitAllChange();
        }
        else if (res == QMessageBox::Cancel)
        {
            event->ignore();
            return;
        }
    }

    QMainWindow::closeEvent(event);
}
void MainWindow::openAboutDialog()
{
    QMessageBox::about(this, "About", tr("2018年秋季学期高级程序设计大作业 by 吴昌容"));
}
void MainWindow::openURLDialog()
{
    QMessageBox::about(this, "Code URL", tr("Github代码链接：https://github.com/BYGX-wcr/Final-Project-of-Senior-PD.git"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
