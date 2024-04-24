#ifndef SQLITEREPOSITORY_H
#define SQLITEREPOSITORY_H

#include "abstractrepository.h"

class QSqlQuery;

class SqliteRepository : public AbstractRepository {

    Q_OBJECT

    public:
        explicit SqliteRepository(QObject *parent = nullptr);

        virtual void insert(Wagon wagon) override;
        virtual void update(Wagon wagon) override;
        virtual void remove(int number) override;
        virtual Wagon getByNumber(int number) override;
        virtual QList<Wagon> getAll() override;
        virtual QList<Wagon> getNeedChange() override;
        virtual QList<Wagon> getOnDate(QDate date) override;

    private:
        Wagon createWagon(QSqlQuery query);
        QList<Wagon> createList(QSqlQuery query);
};

#endif // SQLITEREPOSITORY_H
