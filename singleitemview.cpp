#include "singleitemview.h"
#include <QGridLayout>

#include <QLabel>

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

}

void SingleItemView::scrollTo(const QModelIndex &index, ScrollHint hint)
{

}

QRect SingleItemView::visualRect(const QModelIndex &index) const
{

}

int SingleItemView::horizontalOffset() const
{

}

bool SingleItemView::isIndexHidden(const QModelIndex &index) const
{

}

QModelIndex SingleItemView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{

}

void SingleItemView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags flags)
{

}

int SingleItemView::verticalOffset() const
{

}

QRegion SingleItemView::visualRegionForSelection(const QItemSelection &selection) const
{

}

void SingleItemView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{

}

void SingleItemView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{

}
