#include "objecttreemodel.h"

ObjectTreeModel::ObjectTreeModel(QObject *root, QObject *parent) : QAbstractItemModel{parent}
{}

Qt::ItemFlags ObjectTreeModel::flags(const QModelIndex &index) const
{

}

QVariant ObjectTreeModel::data(const QModelIndex &index, int role) const
{

}

QVariant ObjectTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole || orientation != Qt::Horizontal )
        return QVariant();
    switch( section )
    {
    case 0:
        return QString( "Object" );
    case 1:
        return QString( "Class" );
    default:
        return QVariant();
    }}

int ObjectTreeModel::rowCount(const QModelIndex &parent) const
{

}

int ObjectTreeModel::columnCount(const QModelIndex &parent) const
{

}

QModelIndex ObjectTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    QObject *parentObject;
    if( !parent.isValid() )
        parentObject = m_root;
    else
        parentObject = static_cast<QObject*>( parent.internalPointer() );
    if( row >= 0 && row < parentObject->children().count() )
        return createIndex( row, column, parentObject->children().at( row ) );
    else
        return QModelIndex();}

QModelIndex ObjectTreeModel::parent(const QModelIndex &index) const
{

}
