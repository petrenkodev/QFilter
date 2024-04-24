#include "mainwindow.h"
#include "aboutdialog.h"
#include "src/data/abstractrepository.h"
#include "editdialog.h"
#include "manualdialog.h"
#include "settingdialog.h"
#include "src/data/settings.h"
#include "ui_mainwindow.h"
#include "src/models/wagonmodel.h"
#include <QMessageBox>
#include <QPushButton>

#include <QDebug>

MainWindow::MainWindow(AbstractRepository *repository, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), repository(repository) {
    ui->setupUi(this);

    // model
    model = new WagonModel(repository);

    // mainWindow
    setGeometry(Settings::windowX(), Settings::windowY(), Settings::windowWidth(), Settings::windowHeight());

    // menu
    connect(ui->actionExit, &QAction::triggered, qApp, &QApplication::closeAllWindows);       // Выход
    connect(ui->actionManual, &QAction::triggered, this, []() { ManualDialog().exec(); });    // Краткое руководство
    connect(ui->actionAbout, &QAction::triggered, this, []() { AboutDialog().exec(); });      // О программе
    connect(ui->actionSettings, &QAction::triggered, this, []() { SettingDialog().exec(); }); // Настройки
    connect(ui->actionAdd, &QAction::triggered, this, &MainWindow::addNew);                   // Добавить
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::editCurrent);             // Изменить
    connect(ui->actionMark, &QAction::triggered, this, &MainWindow::markCurrent);             // Отметить
    connect(ui->actionRemove, &QAction::triggered, this, &MainWindow::removeCurrent);         // Удалить

    int colCount = model->columnCount(QModelIndex());
    for (int i = 0; i < colCount; ++i) {
        QAction *action = ui->menuColumns->addAction(model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        action->setCheckable(true);
        action->setChecked(Settings::columnVisible(i));
        action->setData(i);
        connect(action, &QAction::triggered, this, [=](bool checed) { (checed) ? ui->tableView->showColumn(action->data().toInt()) : ui->tableView->hideColumn(action->data().toInt());});
    }

    // filterComboBox
    connect(ui->filterComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(displayModeChanged(int)));

    // dateEdit
    ui->dateEdit->setVisible(false);
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    ui->dateEdit->setDate(QDate::currentDate().addDays(1));
    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), model, SLOT(setDate(QDate)));

    // winterMode
    Settings::winterMode() ? ui->winterRadioButton->setChecked(true) : ui->summerRadioButton->setChecked(true);
    //connect(ui->winterRadioButton, SIGNAL(toggled(bool)), model, SLOT(setWinterMode(bool)));
    connect(ui->winterRadioButton, SIGNAL(toggled(bool)), this, SLOT(setMode(bool)));

    // tableView
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i = 0; i < model->columnCount(QModelIndex()); ++i) {
        (Settings::columnVisible(i)) ? ui->tableView->showColumn(i) : ui->tableView->hideColumn(i);
    }
    connect(ui->tableView, &QTableView::activated, ui->actionMark, &QAction::trigger);

    // search
    //connect(ui->searchEdit, &QLineEdit::textChanged, this, [=]() { model->setSearch(ui->searchEdit->text()); });

    // StatusBar
    connect(model, &WagonModel::layoutChanged, this, [=]() { ui->statusbar->showMessage("Всего: " + QString::number(model->rowCount(QModelIndex()))); });

    displayModeChanged(0);
}

MainWindow::~MainWindow() {
    Settings::setWindowX(geometry().x());
    Settings::setWindowY(geometry().y());
    Settings::setWindowWidth(geometry().width());
    Settings::setWindowHeight(geometry().height());

    for (int i = 0; i < model->columnCount(QModelIndex()); ++i) {
        Settings::setColumnVisible(i, !ui->tableView->isColumnHidden(i));
    }

    delete model;
    delete ui;
}

void MainWindow::addNew() {
    EditDialog dialog(repository);
    dialog.exec();
}

void MainWindow::editCurrent() {
    savePosition();
    int number = model->data(model->index(currentPosition(), 0)).toInt();
    Wagon wagon = repository->getByNumber(number);
    EditDialog dialog(repository, wagon);
    dialog.exec();
    recoverPosition();
}

void MainWindow::markCurrent() {
    savePosition();
    int number = model->data(model->index(currentPosition(), 0)).toInt();
    Wagon wagon = repository->getByNumber(number);
    EditDialog dialog(repository, wagon, EditDialog::Mark);
    dialog.exec();
    recoverPosition();
    connect(ui->winterRadioButton, SIGNAL(toggled(bool)), this, SLOT(setMode(bool)));
}

void MainWindow::removeCurrent() {
    int number = model->data(model->index(currentPosition(), 0)).toInt();
    if (QMessageBox::question(this, "Удалить", "Вы уверены, что хотите удалить вагон " + QString::number(number)) == QMessageBox::Yes) {
        savePosition();
        repository->remove(number);
        recoverPosition();
    }
}

void MainWindow::displayModeChanged(int index) {
    ui->dateEdit->setVisible(index == 1);
    switch (index) {
        case 0:
            model->setMode(WagonModel::NeedChange);
            break;
        case 1:
            model->setMode(WagonModel::OnDate);
            break;
        case 2:
            model->setMode(WagonModel::All);
            break;
    }
    ui->tableView->setFocus();
    setPosition(0);
}

int MainWindow::currentPosition() {
    return ui->tableView->currentIndex().row();
}

void MainWindow::setPosition(int position) {
    ui->tableView->selectRow(position);
}

void MainWindow::savePosition() {
    prevPosition = currentPosition();
}

void MainWindow::recoverPosition() {
    setPosition(std::min(prevPosition, model->rowCount(QModelIndex()) - 1));
}

void MainWindow::setMode(bool winterMode)
{
    qDebug() << winterMode;
    Settings::setWinterMode(winterMode);
}
