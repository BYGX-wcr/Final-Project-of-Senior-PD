#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QDialog>
#include <QVector>
#include <QSqlRecord>
#include <QSqlField>
#include <QPushButton>

namespace Ui {
class RecordDialog;
}

class RecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordDialog(QWidget *parent = 0);
    explicit RecordDialog(QWidget *parent, const QSqlRecord& init);
    ~RecordDialog();
    
    void setId(const QString& id);
    void setName(const QString& name);
    void setGender(int val);
    void setDate(const QDate& date);
    void setNP(const QString& nativePlace);
    void setAddr(const QString& addr);

    void validateInput();
    void accept();

signals:
    void returnRecord(QSqlRecord);
    
private:
    enum Gender {Male, Female};
    QVector<bool> flags;
    Ui::RecordDialog *ui;
    
    QSqlRecord curRecord;
};

#endif // RECORDDIALOG_H
