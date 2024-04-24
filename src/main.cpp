#include "src/dialogs/mainwindow.h"
#include "src/data/sqliterepository.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    SqliteRepository repository;
    MainWindow mainWindos(&repository);
    mainWindos.show();
    return application.exec();
}
