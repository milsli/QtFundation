#include "bardelegate.h"
#include <QPainter>

BarDelegate::BarDelegate(QObject *parent)
    : QAbstractItemDelegate{parent}
{}

void BarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if( option.state & QStyle::State_Selected )
        painter->fillRect( option.rect, option.palette.highlight() );
    int value = index.model()->data( index, Qt::DisplayRole ).toInt();
    double factor = (double)value/100.0;
    painter->save();
    if( factor > 1 )
    {
        painter->setBrush( Qt::red );
        factor = 1;
    }
    else
        painter->setBrush( QColor( 0, (int)(factor*255), 255-(int)(factor*255) ) );
    painter->setPen( Qt::black );
    painter->drawRect( option.rect.x()+2, option.rect.y()+2,
                      (int)(factor*(option.rect.width()-5)), option.rect.height()-5 );
    painter->restore();}

QSize BarDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize( 45, 15 );
}
