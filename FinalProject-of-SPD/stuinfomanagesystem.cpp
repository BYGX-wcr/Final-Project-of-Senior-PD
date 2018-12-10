#include "stuinfomanagesystem.h"

StuInfoManageSystem::StuInfoManageSystem()
{
    username = "root";
    password = "123456";

    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("host");
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
    tableList.clear();
    QStringList tempTableList = database.tables();
    QStringList::iterator it = tempTableList.begin();
    while (it != tempTableList.end())
    {
        if (it->contains("student"))
        {
            tableList.push_back(*it);
        }

        ++it;
    }

    for (int i = 0; i < tableList.size(); ++i)
    {
        QSqlTableModel* ptr = new QSqlTableModel;
        modelList[i] = ptr;
        ptr->setTable(tableList[i]);
    }
    return tableList.size();
}

void StuInfoManageSystem::clearModels()
{
    for (int i = 0; i < modelList.size(); ++i)
    {
        delete modelList[i];
    }
    modelList.clear();
    tableList.clear();
}

QSqlTableModel* StuInfoManageSystem::getModel(int tableIndex)
{
    if (tableIndex >= modelList.size())
        return NULL;

    return modelList[tableIndex];
}

QString StuInfoManageSystem::getTable(int tableIndex)
{
    if (tableIndex >= tableList.size())
        return NULL_TABLE;

    return tableList.at(tableIndex);
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
