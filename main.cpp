/* Obsidian Browser
 * By: Adrian Siwy 
 * Product Type: Web Browser
 * Date Completed: 12/12/2016
 *
 *
*/


#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName(QString("adrian.siwy"));
    a.setApplicationName(QString("Obsidian"));
    MainWindow w;

    w.setStyleSheet("background-color: rgb(30, 0, 80)");
    w.adjustSize();
    w.show();

    return a.exec();
}
