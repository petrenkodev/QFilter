#ifndef ABSTRACTREPOSITORY_H
#define ABSTRACTREPOSITORY_H

#include <QObject>

class Wagon;

class AbstractRepository : public QObject {

    Q_OBJECT

    public:
        explicit AbstractRepository(QObject *parent = nullptr);

        virtual void insert(Wagon wagon) = 0;
        virtual void update(Wagon wagon) = 0;
        virtual void remove(int number) = 0;
        virtual Wagon getByNumber(int number) = 0;
        virtual QList<Wagon> getAll() = 0;
        virtual QList<Wagon> getNeedChange() = 0;
        virtual QList<Wagon> getOnDate(QDate date) = 0;

    signals:
        void dataUpdated();
};

#endif // ABSTRACTREPOSITORY_H
