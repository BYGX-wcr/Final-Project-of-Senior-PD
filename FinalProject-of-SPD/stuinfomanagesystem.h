#ifndef STUINFOMANAGESYSTEM_H
#define STUINFOMANAGESYSTEM_H

#include <QDebug>
#include <QObject>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QMessageBox>

#define NULL_TABLE "null"

class StuInfoManageSystem
{
public:
    enum TableHeader { Sno, Sname, Sex, Birthday, Nativeplace, Address};

    StuInfoManageSystem();

    bool connect(const QString& dbName);
    int readStuInfo();

    void initializeModel(QSqlTableModel* ptr);
    QSqlTableModel* createModel(const QString& tableName);
    QSqlTableModel* getModel(int tableIndex);
    QSqlTableModel* getModel(const QString& tableName);
    void removeModel(int tableIndex);
    void clearModels();

    QString getTableName(int tableIndex);
    bool createTable(const QString &tableName);

    bool getInfo(QSqlRecord& res, int tableIndex, int row);
    bool setInfo(QSqlRecord& arg, int tableIndex, int row);
    bool addInfo(QSqlRecord& arg, int tableIndex);
    bool removeInfo(int tableIndex, int row);

    bool submitChange(int tableIndex);
    bool submitAllChange();

private:
    QString username;
    QString password;
    QSqlDatabase database;

    QVector<QSqlTableModel*> modelList;
};

#endif // STUINFOMANAGESYSTEM_H
