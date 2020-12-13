#include "mainwindow.h"
#include <QApplication>

#include "hashtable.h"
#include <iostream>
#include <cassert>
#include <fstream>

int main(int argc, char *argv[])
{
    // Part I
    HashTable<int, uint32_t> table;

    assert(table.getSize() == 0);

    table.add(10, 25);
    assert(table.contains(10) > -1);
    assert(table.getSize() == 1);
    assert(table.getSumValue() == 25);
    assert(table[10] == 25);

    table.add(26, 242);
    assert(table.contains(26) > -1);
    assert(table.getSize() == 2);
    assert(table[26] == 242);
    assert(table.getSumValue() == 267);
    assert(table[10] == 25);

    std::ofstream ofs;
    ofs.open("file.txt");
    ofs << table;
    ofs.close();

    HashTable<int, uint32_t> fileTable;

    std::ifstream ifs;
    ifs.open("file.txt");
    ifs >> fileTable;
    ifs.close();
    assert(table == fileTable);

    fileTable.add(11, 24);
    assert(table != fileTable);

    HashTable<int, uint32_t> copyTable(table);
    assert(table == copyTable);

    Iterator<int, uint32_t> iter = table.begin();
    assert(iter.currentKey() == 10);
    int first = iter.currentKey();
    iter++;
    int second = iter.currentKey();
    assert(first == 10);
    assert(second == 26);

    table.remove(10);
    assert(table.getSumValue() == 242);
    assert(table.contains(10) == -1);

    table.remove(7);
    assert(table.getSize() == 1);

    table.remove(26);
    assert(table.getSize() == 0);
    assert(table.getSumValue() == 0);
    assert(table.contains(26) == -1);

    copyTable.add(25, 36);
    assert(table != copyTable);

    copyTable.clear();
    assert(copyTable.contains(25) == -1);
    assert(copyTable.isEmpty());

    for (int i = 0; i < 32; i++)
        table.add(i, 250);

    table.add(70, 40);
    assert(table[70] == 40);


    // Part II
    HashTable<string, uint32_t> newTable;
    assert(newTable.getSize() == 0);

    newTable.add("Item", 25);
    assert(newTable.contains("Item") > -1);
    assert(newTable.getSize() == 1);
    assert(newTable.getSumValue() == 25);
    assert(newTable["Item"] == 25);

    newTable.add("Pen", 242);
    assert(newTable.contains("Pen") > -1);
    assert(newTable.getSize() == 2);
    assert(newTable["Pen"] == 242);
    assert(newTable.getSumValue() == 267);
    assert(newTable["Item"] == 25);

    std::ofstream ofs2;
    ofs2.open("file2.txt");
    ofs2 << newTable;
    ofs2.close();

    HashTable<string, uint32_t> newFileTable;

    std::ifstream ifs2;
    ifs2.open("file2.txt");
    ifs2 >> newFileTable;
    ifs2.close();
    assert(newTable == newFileTable);

    newFileTable.add("Pencil", 24);
    assert(newTable != newFileTable);

    HashTable<string, uint32_t> newCopyTable(newTable);
    assert(newTable == newCopyTable);

    Iterator<string, uint32_t> iter2 = newTable.begin();
    assert(iter2.currentKey() == "Pen");
    string first2 = iter2.currentKey();
    iter2++;
    string second2 = iter2.currentKey();
    assert(first2 == "Pen");
    assert(second2 == "Item");

    newTable.remove("Item");
    assert(newTable.getSumValue() == 242);
    assert(newTable.contains("Item") == -1);

    newTable.remove("Pencil");
    assert(newTable.getSize() == 1);

    newTable.remove("Pen");
    assert(newTable.getSize() == 0);
    assert(newTable.getSumValue() == 0);
    assert(newTable.contains("Pen") == -1);

    newCopyTable.add("MacBook", 160000);
    assert(newTable != newCopyTable);

    newCopyTable.clear();
    assert(newCopyTable.contains("Item") == -1);
    assert(newCopyTable.isEmpty());


    QApplication a(argc, argv);


    MainWindow w;
    w.show();

    return a.exec();
}
