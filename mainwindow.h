#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class QSplitter;
class QStandardItemModel;
class QTreeView;
class QListView;
class QTableView;
class BarDelegate;

class QTableView;
class MulModel;
class ObjectTreeModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupView();
    void setupTableView();
    void setupTreeView();

private:
    std::unique_ptr<QTreeView> tree_;
    std::unique_ptr<QListView> list_;
    std::unique_ptr<QTableView> table_;

    std::unique_ptr<QSplitter> splitter_;
    std::unique_ptr<QStandardItemModel> model_;

    BarDelegate *delegate_;


    QTableView *mulTable_;
    MulModel *mulModel_;
    ObjectTreeModel *treeModel_;

    QObject root_;


};
#endif // MAINWINDOW_H
