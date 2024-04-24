#include "settingdialog.h"
#include "src/data/settings.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingDialog) {
    ui->setupUi(this);
    ui->winterPeriodEdit->setValue(Settings::winterPeriod());
    ui->summerPeriodEdit->setValue(Settings::summerPeriod());
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingDialog::saveSettings);
}

SettingDialog::~SettingDialog() {
    delete ui;
}

void SettingDialog::saveSettings() {
    Settings::setWinterPeriod(ui->winterPeriodEdit->value());
    Settings::setSummerPeriod(ui->summerPeriodEdit->value());
}
