#include "dsdatamodel.h"

DSDataModel::DSDataModel(QObject *parent) :
    QAbstractTableModel(parent)
{


    for (quint8 i = 0; i < 16; i++)
        header_data << QString::number(i, 16);

    for (int i = 0; i < 256; i++)
        BDData[i] = 0;
}


QVariant DSDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {

        return QString::number(BDData[index.row()*16 + index.column()], 16);

    }

    return QVariant();
}

int DSDataModel::rowCount(const QModelIndex &parent) const
{
    return data_size/16;
}

int DSDataModel::columnCount(const QModelIndex &parent) const
{
    return 16;
}

QVariant DSDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return header_data.at(section);
    } else {
        return QString::number(section*16, 16);
    }


}
