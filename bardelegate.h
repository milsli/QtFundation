#ifndef BARDELEGATE_H
#define BARDELEGATE_H

#include <QAbstractItemDelegate>

class BarDelegate : public QAbstractItemDelegate
{
public:
    explicit BarDelegate(QObject *parent = nullptr);

    void paint( QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index ) const;
    QSize sizeHint( const QStyleOptionViewItem &option,
                   const QModelIndex &index ) const;

    QWidget *createEditor( QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index ) const;
    void setEditorData( QWidget *editor,
                       const QModelIndex &index ) const;
    void setModelData( QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index ) const;
    void updateEditorGeometry( QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index ) const;
};

#endif // BARDELEGATE_H
