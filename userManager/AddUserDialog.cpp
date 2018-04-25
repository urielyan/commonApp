#include "AddUserDialog.h"
#include "ui_AddUserDialog.h"

#include <QMessageBox>

AddUserDialog::AddUserDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddUser)
    , m_data(new UserData)
{
    ui->setupUi(this);
    UserData useData;
    ui->access->addItems(useData.getAccessList());
    ui->manradioButton->setChecked(true);

    ui->stature->setPlaceholderText(tr("单位为cm，范围为0-300。"));
    ui->stature->setValidator(new QIntValidator(0, 300, ui->stature));

    ui->weight->setPlaceholderText(tr("单位为kg，范围为0-150"));
    ui->weight->setValidator(new QIntValidator(0, 150, ui->weight));

    ui->age->setPlaceholderText(tr("范围为0-150"));
    ui->age->setValidator(new QIntValidator(0, 150, ui->age));
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::on_add_clicked()
{
    if (
            ui->usserName->text().size() == 0
            || ui->passwd->text().size() == 0
            )
    {
        QMessageBox::warning(this, tr("输入错误"), tr("您输入的数据有误，请重新输入"));
        return;
    }

    m_data->setUserName(ui->usserName->text());
    m_data->setPasswd(ui->passwd->text());
    m_data->setAccess(ui->access->currentIndex());
    m_data->setGender(ui->manradioButton->isChecked() ?
                          UserData::Male : UserData::Female);
    m_data->setAge(ui->age->text().toInt());
    m_data->setWeight(ui->weight->text().toDouble());
    m_data->setStature(ui->stature->text().toDouble());
    this->accept();
}

void AddUserDialog::on_cancel_clicked()
{
    this->reject();
}

UserData *AddUserDialog::data() const
{
    return m_data;
}

void AddUserDialog::setData(UserData *data)
{
    m_data = data;
}
