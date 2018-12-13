#include "stuinfomanagesystem.h"

StuInfoManageSystem::StuInfoManageSystem()
{
    username = "root";
    password = "123456";

    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setPort(3306);
    database.setUserName(username);
    database.setPassword(password);
}

bool StuInfoManageSystem::connect(const QString &dbName)
{
    if (database.isOpen())
    {
        qDebug() << "Data Base has been open: " << database.databaseName() << endl;
        return false;
    }

    database.setDatabaseName(dbName);
    if (!database.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error: ") + dbName, database.lastError().text());
        return false;
    }
    return true;
}
int StuInfoManageSystem::readStuInfo()
{
    QStringList tempTableList = database.tables();
    QStringList::iterator it = tempTableList.begin();
    while (it != tempTableList.end())
    {
        if (it->size() > 8 && it->startsWith("student_"))
        {//Filter invalid tables
            QSqlTableModel* ptr = new QSqlTableModel;
            ptr->setTable(*it);
            ptr->select();
            if (ptr->rowCount() == 0)
            {//Filter empty tables
                delete ptr;
            }
            else
            {
                modelList.push_back(ptr);
                initializeModel(ptr);
            }
        }

        ++it;
    }

    return modelList.size();
}

void StuInfoManageSystem::clearModels()
{
    for (int i = 0; i < modelList.size(); ++i)
    {
        delete modelList[i];
    }
    modelList.clear();
}
void StuInfoManageSystem::initializeModel(QSqlTableModel *ptr)
{
    ptr->setHeaderData(StuInfoManageSystem::Sno, Qt::Horizontal, "学号");
    ptr->setHeaderData(StuInfoManageSystem::Sname, Qt::Horizontal, "名字");
    ptr->setHeaderData(StuInfoManageSystem::Sex, Qt::Horizontal, "性别");
    ptr->setHeaderData(StuInfoManageSystem::Birthday, Qt::Horizontal, "生日");
    ptr->setHeaderData(StuInfoManageSystem::Nativeplace, Qt::Horizontal, "籍贯");
    ptr->setHeaderData(StuInfoManageSystem::Address, Qt::Horizontal, "住址");
    ptr->setEditStrategy(QSqlTableModel::OnManualSubmit);
}
QSqlTableModel* StuInfoManageSystem::createModel(const QString &tableName)
{
    QSqlTableModel* ptr = new QSqlTableModel;
    modelList.push_back(ptr);
    ptr->setTable(tableName);
    if (database.tables().contains(tableName) && ptr->rowCount() != 0)
    {
        QMessageBox::warning(0, QObject::tr("Database Error"), QObject::tr("The table has existed!"));
        delete ptr;
        modelList.pop_back();
        return NULL;
    }
    else if (!database.tables().contains(tableName))
    {
        createTable(tableName);
    }

    initializeModel(ptr);
    ptr->select();
    return ptr;
}
QSqlTableModel* StuInfoManageSystem::getModel(int tableIndex)
{
    if (tableIndex >= modelList.size())
        return NULL;

    return modelList[tableIndex];
}
QSqlTableModel* StuInfoManageSystem::getModel(const QString &tableName)
{
    if (!database.tables().contains(tableName))
        return NULL;

    QSqlTableModel* ptr = new QSqlTableModel;
    ptr->setTable(tableName);
    modelList.push_back(ptr);
    initializeModel(ptr);
    ptr->select();
    return ptr;
}
void StuInfoManageSystem::removeModel(int tableIndex)
{
    delete modelList[tableIndex];
    modelList.remove(tableIndex);
}

bool StuInfoManageSystem::createTable(const QString &tableName)
{
    QSqlQuery query;
    if (!query.exec("create table " + tableName + " (sno int primary key, sname varchar(20) not null, sex char(4) not null, birthday date not null, nativeplace varchar(80), address varchar(80))"))
    {
        QMessageBox::critical(0, QObject::tr("Database Error"), query.lastError().text());
        return false;
    }
    return true;
}
QString StuInfoManageSystem::getTableName(int tableIndex)
{
    if (tableIndex >= modelList.size())
        return NULL_TABLE;

    return modelList[tableIndex]->tableName();
}

bool StuInfoManageSystem::getInfo(QSqlRecord& res, int tableIndex, int row)
{
    QSqlTableModel* curTable = modelList[tableIndex];
    if (row >= curTable->rowCount())
        return false;

    res = curTable->record(row);
    return true;
}
bool StuInfoManageSystem::setInfo(QSqlRecord& arg, int tableIndex, int row)
{
    QSqlTableModel* curTable = modelList[tableIndex];
    if (row >= curTable->rowCount())
        return false;

    curTable->setRecord(row, arg);
    return true;
}
bool StuInfoManageSystem::addInfo(QSqlRecord &arg, int tableIndex)
{
    QSqlTableModel* curTable = modelList[tableIndex];
    if (curTable->insertRecord(curTable->rowCount(), arg))
    {
        return true;
    }
    else
        return false;
}
bool StuInfoManageSystem::removeInfo(int tableIndex, int row)
{
    QSqlTableModel* curTable = modelList[tableIndex];
    if (row >= curTable->rowCount())
        return false;

    return curTable->removeRow(row);
}

bool StuInfoManageSystem::submitChange(int tableIndex)
{
    return modelList[tableIndex]->submitAll();
}

bool StuInfoManageSystem::submitAllChange()
{
    for (int i = 0; i < modelList.size(); ++i)
    {
        if (!modelList[i]->submitAll())
            return false;
    }
    return true;
}
