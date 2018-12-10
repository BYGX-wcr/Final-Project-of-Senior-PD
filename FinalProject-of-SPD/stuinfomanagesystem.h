#ifndef STUINFOMANAGESYSTEM_H
#define STUINFOMANAGESYSTEM_H

#include <QDebug>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>

#define NULL_TABLE "null"

class StuInfoManageSystem
{
public:
    StuInfoManageSystem();

    bool connect(const QString& dbName);
    int readStuInfo();
    void clearModels();

    QSqlTableModel* getModel(int tableIndex);
    QString getTable(int tableIndex);
    bool getInfo(QSqlRecord& res, int tableIndex, int row);
    bool setInfo(QSqlRecord& arg, int tableIndex, int row);

private:
    QString username;
    QString password;
    QSqlDatabase database;

    QStringList tableList;
    QVector<QSqlTableModel*> modelList;
};

#endif // STUINFOMANAGESYSTEM_H
