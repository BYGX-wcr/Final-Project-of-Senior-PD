#include "recorddialog.h"
#include "ui_recorddialog.h"
#include "stuinfomanagesystem.h"

RecordDialog::RecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordDialog), flags(2, false)
{
    ui->setupUi(this);

    this->setWindowTitle("Record Dialog");
    ui->comboBox->addItem("男", RecordDialog::Male);
    ui->comboBox->addItem("女", RecordDialog::Female);
    QIntValidator* intValidator = new QIntValidator(100000000, 200000000, this);
    ui->lineEdit->setValidator(intValidator);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &RecordDialog::setId);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &RecordDialog::setName);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RecordDialog::setGender);
    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &RecordDialog::setDate);
    connect(ui->lineEdit_4, &QLineEdit::textChanged, this, &RecordDialog::setNP);
    connect(ui->lineEdit_5, &QLineEdit::textChanged, this, &RecordDialog::setAddr);

    //initialize the record
    curRecord.append(QSqlField("sno", QVariant::Int));
    curRecord.append(QSqlField("sname", QVariant::String));
    curRecord.append(QSqlField("sex", QVariant::String));
    curRecord.append(QSqlField("birthday", QVariant::Date));
    curRecord.append(QSqlField("nativeplace", QVariant::String));
    curRecord.append(QSqlField("address", QVariant::String));

    setGender(ui->comboBox->currentIndex());
    setDate(ui->dateEdit->date());
}

RecordDialog::RecordDialog(QWidget *parent, const QSqlRecord& init) :
    QDialog(parent),
    ui(new Ui::RecordDialog), flags(2, false), curRecord(init)
{
    ui->setupUi(this);

    this->setWindowTitle("Record Dialog");
    ui->comboBox->addItem("男", RecordDialog::Male);
    ui->comboBox->addItem("女", RecordDialog::Female);
    QIntValidator* intValidator = new QIntValidator(100000000, 200000000, this);
    ui->lineEdit->setValidator(intValidator);

    ui->lineEdit->setText(init.value("sno").toString());
    ui->lineEdit_2->setText(init.value("sname").toString());
    ui->comboBox->setCurrentText(init.value("sex").toString());
    ui->dateEdit->setDate(init.value("birthday").toDate());
    ui->lineEdit_4->setText(init.value("nativeplace").toString());
    ui->lineEdit_5->setText(init.value("address").toString());

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &RecordDialog::setId);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &RecordDialog::setName);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RecordDialog::setGender);
    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &RecordDialog::setDate);
    connect(ui->lineEdit_4, &QLineEdit::textChanged, this, &RecordDialog::setNP);
    connect(ui->lineEdit_5, &QLineEdit::textChanged, this, &RecordDialog::setAddr);
}

void RecordDialog::setId(const QString &id)
{
    if (id.size() <= 8)
        flags[StuInfoManageSystem::Sno] = false;
    else
        flags[StuInfoManageSystem::Sno] = true;
    curRecord.setValue("sno", id.toInt());

    validateInput();
}

void RecordDialog::setName(const QString &name)
{
    if (name.size() <= 0)
        flags[StuInfoManageSystem::Sname] = false;
    else
        flags[StuInfoManageSystem::Sname] = true;
    curRecord.setValue("sname", name);

    validateInput();
}

void RecordDialog::setGender(int val)
{
    if (val == Male)
        curRecord.setValue("sex", "男");
    else
        curRecord.setValue("sex", "女");
}

void RecordDialog::setDate(const QDate &date)
{
    curRecord.setValue("birthday", date);
}

void RecordDialog::setNP(const QString& nativePlace)
{
    curRecord.setValue("nativeplace", nativePlace);
}

void RecordDialog::setAddr(const QString &addr)
{
    curRecord.setValue("address", addr);
}

void RecordDialog::validateInput()
{
    bool flag = true;
    for (int i = 0; i < flags.size(); ++i)
    {
        flag = flag && flags[i];
    }

    if (flag)
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    else
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

void RecordDialog::accept()
{
    emit returnRecord(curRecord);
    QDialog::accept();
}

RecordDialog::~RecordDialog()
{
    delete ui;
}
