#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    selectedRowIndex = -1;

    QRegExp int_exp("[1-9]\\d*");
    QRegExpValidator *validator = new QRegExpValidator(int_exp, this);

    ui->priceLineEdit->setValidator(validator);

    ui->hashTableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->hashTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->hashTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->statusLabel->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    QString item = ui->itemLineEdit->text();
    QString price = ui->priceLineEdit->text();

    if (item.isEmpty())
        return;
    if (price.isEmpty())
        price = "100";

    if (table.contains(item.toStdString()) == -1)
    {
        ui->hashTableWidget->insertRow(ui->hashTableWidget->rowCount());

        QTableWidgetItem *nameItem = new QTableWidgetItem();
        nameItem->setText(item);
        ui->hashTableWidget->setItem(ui->hashTableWidget->rowCount() - 1, 0, nameItem);

        QTableWidgetItem *priceItem = new QTableWidgetItem();
        priceItem->setText(price);
        ui->hashTableWidget->setItem(ui->hashTableWidget->rowCount() - 1, 1, priceItem);

        ui->delButton->setEnabled(false);
        ui->delAllButton->setEnabled(true);
    }
    else
    {
        QTableWidgetItem *priceItem = new QTableWidgetItem();
        priceItem->setText(price);
        ui->hashTableWidget->setItem(selectedRowIndex, 1, priceItem);
    }

    table.add(item.toStdString(), price.toUInt());

    ui->sumValueLineEdit->setText(QString::number(table.getSumValue()));

    ui->itemLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->statusLabel->setVisible(false);
    ui->writeToFileButton->setEnabled(true);
}

void MainWindow::on_hashTableWidget_cellClicked(int row, int column)
{
    ui->delButton->setEnabled(true);

    ui->itemLineEdit->setText(ui->hashTableWidget->item(row, 0)->text());
    ui->priceLineEdit->setText(ui->hashTableWidget->item(row, 1)->text());

    selectedRowIndex = row;

    ui->statusLabel->setVisible(false);
}

void MainWindow::on_delButton_clicked()
{
    if (ui->hashTableWidget->selectedItems().empty())
        return;

    table.remove(ui->hashTableWidget->item(selectedRowIndex, 0)->text().toStdString());

    ui->hashTableWidget->removeRow(selectedRowIndex);

    ui->itemLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->delButton->setEnabled(false);

    ui->sumValueLineEdit->setText(QString::number(table.getSumValue()));

    if (ui->hashTableWidget->rowCount() == 0)
    {
        ui->delAllButton->setEnabled(false);
        ui->writeToFileButton->setEnabled(false);
    }

    ui->statusLabel->setVisible(false);
}

void MainWindow::on_delAllButton_clicked()
{
    if (ui->hashTableWidget->rowCount() == 0)
        return;

    table.clear();

    ui->hashTableWidget->setRowCount(0);

    ui->delButton->setEnabled(false);
    ui->delAllButton->setEnabled(false);
    ui->sumValueLineEdit->clear();
    ui->statusLabel->setVisible(false);
    ui->writeToFileButton->setEnabled(false);
}

void MainWindow::on_writeToFileButton_clicked()
{
    if (ui->hashTableWidget->rowCount() != 0)
    {
        std::string fileName = ui->fileNameLineEdit->text().toStdString();
        std::ofstream ofs;
        ofs.open(fileName);
        ofs << table;
        ofs.close();
        ui->statusLabel->setText("Записано");
        ui->statusLabel->setVisible(true);
    }
}

void MainWindow::on_readFromFileButton_clicked()
{
    std::string fileName = ui->fileNameLineEdit->text().toStdString();
    std::ifstream ifs;
    ifs.open(fileName);
    if (ifs.is_open())
    {
        ui->hashTableWidget->setRowCount(0);

        ifs >> table;

        uint32_t size = table.getSize();
        for (Iterator<string, uint32_t> iter = table.begin(); size != 0; iter++, size--)
        {
            ui->hashTableWidget->insertRow(ui->hashTableWidget->rowCount());

            QTableWidgetItem *nameItem = new QTableWidgetItem();
            nameItem->setText(QString::fromStdString(iter.currentKey()));
            ui->hashTableWidget->setItem(ui->hashTableWidget->rowCount() - 1, 0, nameItem);

            QTableWidgetItem *priceItem = new QTableWidgetItem();
            priceItem->setText(QString::number(iter.currentValue()));
            ui->hashTableWidget->setItem(ui->hashTableWidget->rowCount() - 1, 1, priceItem);
        }

        ui->delButton->setEnabled(false);

        if (ui->hashTableWidget->rowCount() != 0)
        {
            ui->writeToFileButton->setEnabled(true);
            ui->delAllButton->setEnabled(true);
            ui->statusLabel->setText("Прочитано");
        }
        else
            ui->statusLabel->setText("Таблица пуста");

        ui->statusLabel->setVisible(true);
    }
}
