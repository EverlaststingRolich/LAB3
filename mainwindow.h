#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hashtable.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();

    void on_hashTableWidget_cellClicked(int row, int column);

    void on_delButton_clicked();

    void on_delAllButton_clicked();

    void on_writeToFileButton_clicked();

    void on_readFromFileButton_clicked();

private:
    Ui::MainWindow *ui;

    HashTable<string, uint32_t> table;
    int selectedRowIndex;
};

#endif // MAINWINDOW_H
