#ifndef DSDATAMODEL_H
#define DSDATAMODEL_H

#include <QAbstractTableModel>

#include <QStringList>

class DSDataModel : public QAbstractTableModel
{
    Q_OBJECT

private:

    quint16 data_size;

public:
    explicit DSDataModel(QObject *parent = 0);

    quint8 BDData[256];

    QStringList header_data;


    void setDataSize(quint16 size) {data_size = size;}

    QVariant data(const QModelIndex &index, int role) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;



signals:

public slots:

};

#endif // DSDATAMODEL_H
