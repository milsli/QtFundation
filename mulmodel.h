#ifndef MULMODEL_H
#define MULMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class MulModel : public QAbstractTableModel
{
public:
    MulModel(int rows, int columns, QObject *parent = nullptr);

    Qt::ItemFlags flags( const QModelIndex &index ) const;
    QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const;

    QVariant headerData( int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole ) const;
    int rowCount( const QModelIndex &parent = QModelIndex() ) const;
    int columnCount( const QModelIndex &parent = QModelIndex() ) const;
private:
    int m_rows, m_columns;
};

#endif // MULMODEL_H
