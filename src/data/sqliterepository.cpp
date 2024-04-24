#include "sqliterepository.h"
#include "settings.h"
#include "wagon.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDriver>

#include <QDebug>

SqliteRepository::SqliteRepository(QObject *parent) : AbstractRepository{parent}
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Settings::dataBasePath());
    if (!db.open())
        qFatal("%s", qUtf8Printable(db.lastError().text()));

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS 'Wagons' ("
               "'wagonNumber' INTEGER NOT NULL UNIQUE, "
               "'replacementDate' TEXT NOT NULL, "
               "'nextReplacementDate' TEXT NOT NULL, "
               "'surname' TEXT, "
               "'filterType' TEXT, "
               "'wagonType' TEXT, "
               "'comment' TEXT, "
               "PRIMARY KEY('wagonNumber') );");

    QSqlDriver *driver = db.driver();
    driver->subscribeToNotification("Wagons");
    connect(driver, SIGNAL(notification(QString)), this, SIGNAL(dataUpdated()));
}

void SqliteRepository::insert(Wagon wagon)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Wagons (wagonNumber, replacementDate, nextReplacementDate, surname, filterType, wagonType, comment) "
                  "VALUES (:wagonNumber, :replacementDate, :nextReplacementDate, :surname, :filterType, :wagonType, :comment)");
    query.bindValue(":wagonNumber", wagon.wagonNumber());
    query.bindValue(":replacementDate", wagon.replacementDate());
    query.bindValue(":nextReplacementDate", wagon.nextReplacementDate());
    query.bindValue(":surname", wagon.surname());
    query.bindValue(":filterType", wagon.filterType());
    query.bindValue(":wagonType", wagon.wagonType());
    query.bindValue(":comment", wagon.comment());
    query.exec();
}

void SqliteRepository::update(Wagon wagon)
{
    QSqlQuery query;
    query.prepare("UPDATE Wagons "
                  "SET replacementDate = :replacementDate, "
                      "nextReplacementDate = :nextReplacementDate, "
                      "surname = :surname, "
                      "filterType = :filterType, "
                      "wagonType = :wagonType, "
                      "comment = :comment "
                  "WHERE wagonNumber = :wagonNumber");

    query.bindValue(":wagonNumber", wagon.wagonNumber());
    query.bindValue(":replacementDate", wagon.replacementDate());
    query.bindValue(":nextReplacementDate", wagon.nextReplacementDate());
    query.bindValue(":surname", wagon.surname());
    query.bindValue(":filterType", wagon.filterType());
    query.bindValue(":wagonType", wagon.wagonType());
    query.bindValue(":comment", wagon.comment());
    query.exec();
}

void SqliteRepository::remove(int number)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Wagons WHERE wagonNumber = :wagonNumber;");
    query.bindValue(":wagonNumber", number);
    query.exec();
}

Wagon SqliteRepository::getByNumber(int number)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Wagons WHERE wagonNumber = :wagonNumber;");
    query.bindValue(":wagonNumber", number);
    query.exec();query.next();
    return createWagon(query);
}

QList<Wagon> SqliteRepository::getAll()
{
    QSqlQuery query("SELECT * FROM Wagons");
    return createList(query);
}

QList<Wagon> SqliteRepository::getNeedChange()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Wagons WHERE strftime('%J', 'now') - strftime('%J', nextReplacementDate) > 0;");
    query.exec();
    return createList(query);
}

QList<Wagon> SqliteRepository::getOnDate(QDate date)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Wagons WHERE (strftime('%J', :date) - strftime('%J', nextReplacementDate)) >= 0 AND "
                                             "(strftime('%J', :date) - strftime('%J', nextReplacementDate)) % :currentPeriod = 0 ;");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":currentPeriod", Settings::currentPeriod());
    query.exec();
    return createList(query);
}

Wagon SqliteRepository::createWagon(QSqlQuery query)
{
    int wagonNumberIndex = query.record().indexOf("wagonNumber");
    int replacementDateIndex = query.record().indexOf("replacementDate");
    int nextReplacementDateIndex = query.record().indexOf("nextReplacementDate");
    int surnameIndex = query.record().indexOf("surname");
    int filterTypeIndex = query.record().indexOf("filterType");
    int wagonTypeIndex = query.record().indexOf("wagonType");
    int commentIndex = query.record().indexOf("comment");

    int wagonNumber = query.value(wagonNumberIndex).toInt();
    QDate replacementDate = query.value(replacementDateIndex).toDate();
    QDate nextReplacementDate = query.value(nextReplacementDateIndex).toDate();
    QString surname = query.value(surnameIndex).toString();
    QString filterType = query.value(filterTypeIndex).toString();
    QString wagonType = query.value(wagonTypeIndex).toString();
    QString comment = query.value(commentIndex).toString();

    Wagon wagon(wagonNumber);
    wagon.setReplacementDate(replacementDate);
    wagon.setNextReplacementDate(nextReplacementDate);
    wagon.setSurname(surname);
    wagon.setFilterType(filterType);
    wagon.setWagonType(wagonType);
    wagon.setComment(comment);

    return wagon;
}

QList<Wagon> SqliteRepository::createList(QSqlQuery query)
{
    QList<Wagon> list;
    while (query.next()) {
        Wagon wagon = createWagon(query);
        list.append(wagon);
    }
    return list;
}
