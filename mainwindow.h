#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebEngineWidgets>
#include "favorite.h"
#include "browserdatamanager.h"
#include "favoriteedit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    BrowserDataManager *data;
    FavoriteEdit editWindow;

private slots:
    void on_addTab_clicked();
    void on_removeTab_clicked(int);
    void tab_finished_loading();
    void on_lineEdit_returnPressed();
    void on_favoriteButton_clicked();
    void on_homePageEdit_returnPressed();
    void loadUrl_on_currentTab(QUrl);
    void on_historyListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_favoritesListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_clearHistoryButton_clicked();
    void on_backButton_clicked();
    void on_forwardButton_clicked();
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
