#include "mainwindow.h"
#include "bardelegate.h"
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QSplitter>
#include <QStandardItemModel>
#include "singleitemview.h"
#include "mulmodel.h"
#include "objecttreemodel.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // setupView();

    // setupTableView();
    setupTreeView();

}

MainWindow::~MainWindow() {}

void MainWindow::setupView()
{
    tree_ = unique_ptr<QTreeView>(new QTreeView);
    list_ = make_unique<QListView>();
    table_ =make_unique<QTableView>();

    splitter_ = make_unique<QSplitter>();

/*    jako pozycję widoku stosujemy QStandardItemModel
 *
 *
    splitter_->addWidget( tree_.get() );
    splitter_->addWidget( list_.get() );
    splitter_->addWidget( table_.get() );

    model_ = make_unique<QStandardItemModel>( 5, 2 );
    for( int r=0; r<5; r++ )
        for( int c=0; c<2; c++)
        {
            QStandardItem *item =
                new QStandardItem( QString("Row:%1, Column:%2").arg(r).arg(c) );
            if( c == 0 )
                for( int i=0; i<3; i++ )
                    item->appendRow( new QStandardItem( QString("Item %1").arg(i) ) );
            model_->setItem(r, c, item);
        }

    model_->setHorizontalHeaderItem( 0, new QStandardItem( "Name" ) );
    model_->setHorizontalHeaderItem( 1, new QStandardItem( "Phone number" ) );

    tree_->setModel( model_.get() );
    list_->setModel( model_.get() );
    table_->setModel( model_.get() );

    delegate_ = new BarDelegate;
    table_->setItemDelegateForColumn( 1, delegate_ );

*/

    // jako pozycję widoku stosujemy własną SingleItemView

    SingleItemView *selView = new SingleItemView;
    splitter_->addWidget( table_.get() );
    splitter_->addWidget(selView);

    model_ = make_unique<QStandardItemModel>( 5, 2 );
    for( int r=0; r<5; r++ )
        for( int c=0; c<2; c++)
        {
            QStandardItem *item =
                new QStandardItem( QString("Row:%1, Column:%2").arg(r).arg(c) );
            if( c == 0 )
                for( int i=0; i<3; i++ )
                    item->appendRow( new QStandardItem( QString("Item %1").arg(i) ) );
            model_->setItem(r, c, item);
        }

    model_->setHorizontalHeaderItem( 0, new QStandardItem( "Name" ) );
    model_->setHorizontalHeaderItem( 1, new QStandardItem( "Phone number" ) );



    table_->setModel( model_.get() );
    selView->setModel(model_.get());

    selView->setSelectionModel( table_->selectionModel() );



    setCentralWidget(splitter_.get());
}

void MainWindow::setupTableView()
{
    mulModel_ = new MulModel(14, 14);
    mulTable_ = new QTableView();
    mulTable_->setModel(mulModel_);

    setCentralWidget(mulTable_);
}

void MainWindow::setupTreeView()
{
    root_.setObjectName("root");
    QObject *mama = new QObject(&root_);
    mama->setObjectName("Kądziel");
    QObject *tata = new QObject(&root_);
    tata->setObjectName("Miecz");




    treeModel_ = new ObjectTreeModel(&root_);
    tree_ = make_unique<QTreeView>();

    tree_->setModel(treeModel_);

    setCentralWidget(tree_.get());
}
