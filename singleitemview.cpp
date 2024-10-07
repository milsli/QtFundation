#include "singleitemview.h"
#include <QGridLayout>

#include <QLabel>
#include <QScrollBar>

SingleItemView::SingleItemView(QWidget *parent) : QAbstractItemView(parent)
{
    QGridLayout *layout = new QGridLayout( this->viewport() );
    label = new QLabel();
    layout->addWidget( label, 0, 0 );
    label->setAlignment( Qt::AlignCenter );
    label->setSizePolicy(
        QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding ) );
    label->setText( tr("<i>No data.</i>") );
}

QModelIndex SingleItemView::indexAt(const QPoint &point) const
{
    if(this->viewport()->pos() != point)
        return QModelIndex();

    return currentIndex();
}

void SingleItemView::scrollTo(const QModelIndex &index, ScrollHint hint)
{
// cannot scroll
}

QRect SingleItemView::visualRect(const QModelIndex &index) const
{
    if( selectionModel()->selection().indexes().count() != 1 )
        return QRect();
    if( currentIndex() != index )
        return QRect();
    return rect();
}

int SingleItemView::horizontalOffset() const
{
    return horizontalScrollBar()->value();
}

bool SingleItemView::isIndexHidden(const QModelIndex &index) const
{

    // NA RAZIE TAK JAK TUTAJ ALE TO TRZEBA ZAIMPLEMENTOWAĆ PORZĄDNIE



    return false;
}

QModelIndex SingleItemView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    return currentIndex();
}

void SingleItemView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags flags)
{
    // do nothing
}

int SingleItemView::verticalOffset() const
{
    return verticalScrollBar()->value();
}

QRegion SingleItemView::visualRegionForSelection(const QItemSelection &selection) const
{
    if( selectionModel()->selection() != selection )
        return QRegion();
    return visibleRegion();}

void SingleItemView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    updateText();
}

void SingleItemView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    updateText();
}

void SingleItemView::updateText()
{
    switch( selectionModel()->selection().indexes().count() )
    {
    case 0:
        label->setText( tr("<i>No data.</i>") );
        break;
    case 1:
        label->setText( model()->data( currentIndex() ).toString() );
        break;
    default:
        label->setText( tr("<i>Too many items selected.<br>"
                          "Can only show one item at a time.</i>") );
        break;
    }
}
