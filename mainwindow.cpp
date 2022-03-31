#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebEngineWidgets>
#include <QSettings>
#include "browserdatamanager.h"
#include "favoriteedit.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //colors changed
    ui->tabWidget->setStyleSheet("background-color: rgb(240, 242, 255)");
    ui->browserTabs->setStyleSheet("background-color: rgb(220, 200, 255)");
    ui->favoriteButton->setStyleSheet("background-color: rgb(220, 200, 255)");
    ui->addButton->setStyleSheet("background-color: rgb(220, 200, 255)");
    ui->editButton->setStyleSheet("background-color: rgb(220, 200, 255)");
    ui->deleteButton->setStyleSheet("background-color: rgb(220, 200, 255)");
    ui->backButton->setStyleSheet("background-color: rgb(220, 200, 255)");
    ui->forwardButton->setStyleSheet("background-color: rgb(220, 200, 255)");
    ui->clearHistoryButton->setStyleSheet("background-color: rgb(220, 200, 255)");

    // load in the history and favorites from file
    data = new BrowserDataManager();

    // load in the saved history
    foreach (QUrl url, data->historyList) {
       ui->historyListWidget->addItem(url.toString());
    }

    // load the favorites data
    for( int i=0; i<data->favoritesList.count(); ++i )
    {
        ui->favoritesListWidget->addItem(data->favoritesList[i].name);
        data->favoritesList[i].listItem = ui->favoritesListWidget->item(ui->favoritesListWidget->count() - 1);
    }

    //allow the tabs to be closeable
    ui->browserTabs->setTabsClosable(true);
    connect(ui->browserTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(on_removeTab_clicked(int)));

    //make an addtab button
    QPushButton *newTab = new QPushButton();
    newTab->setFlat(true);
    newTab->setText(" + ");
    newTab->setFixedWidth(40);
    connect(newTab, &QPushButton::clicked, this, &MainWindow::on_addTab_clicked);
    ui->browserTabs->setCornerWidget(newTab, Qt::TopRightCorner);

    //add the default tab
    QWebEngineView *webPage = new QWebEngineView();
    ui->browserTabs->addTab(webPage, "");
    connect(webPage, SIGNAL(titleChanged(QString)), this, SLOT(tab_finished_loading()));
    loadUrl_on_currentTab(data->homePage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// When a tab finishes loading, update the title of the tab
void MainWindow::tab_finished_loading()
{
    QWebEngineView *webPage = (QWebEngineView*)sender();
    ui->browserTabs->setTabText(ui->browserTabs->indexOf(webPage), webPage->title());
}

// Load a url on the current tab webPage
void MainWindow::loadUrl_on_currentTab(QUrl url)
{
    //get access to the current webView
    QWebEngineView* pWebView = NULL;
    QWidget* pWidget = ui->browserTabs->widget(ui->browserTabs->currentIndex());
    // You can use metaobject to get widget type or qobject_cast
    pWebView = (QWebEngineView*)pWidget;

    pWebView->load(url);

    //Add the web url to the history
    data->historyList << url;
    ui->historyListWidget->addItem(url.toString());
    data->save_historyData();
}

// Add a tab and set it to the homePage
void MainWindow::on_addTab_clicked()
{
    //create a new tab with the loaded webpage and set it as the open tab
    QWebEngineView *webPage = new QWebEngineView();

    ui->browserTabs->addTab(webPage, "");
    ui->browserTabs->setCurrentIndex(ui->browserTabs->count() - 1);
    connect(webPage, SIGNAL(titleChanged(QString)), this, SLOT(tab_finished_loading()));

    loadUrl_on_currentTab(data->homePage);
}

// Remove the tab selected
void MainWindow::on_removeTab_clicked(int index)
{
    // If there is only one tab, set the current tab to homePage
    if (ui->browserTabs->count() == 1) {
        loadUrl_on_currentTab(data->homePage);
    } else {
        ui->browserTabs->removeTab(index);
    }
}

// Load the url in the search bar if enter is pressed
void MainWindow::on_lineEdit_returnPressed()
{
    loadUrl_on_currentTab(QUrl(ui->lineEdit->text().toUtf8()));
}

// When the favorites button is clicked, add the current url to the favoritesList
void MainWindow::on_favoriteButton_clicked()
{
    QWebEngineView* pWebView = NULL;
    QWidget* pWidget = ui->browserTabs->widget(ui->browserTabs->currentIndex());
    pWebView = (QWebEngineView*)pWidget;

    Favorite newFavorite;
    newFavorite.url = pWebView->url();
    newFavorite.name = pWebView->title();

    // add the new favorite to the favorite list
    ui->favoritesListWidget->addItem(newFavorite.name);
    newFavorite.listItem = ui->favoritesListWidget->item(ui->favoritesListWidget->count() - 1);
    data->favoritesList << newFavorite;
    data->save_favoritesData();
}

// When return is pressed on homePageEdit, change the homePage
void MainWindow::on_homePageEdit_returnPressed()
{
    // Create a new url and change is to the homePage
    QString urlString = "http://" + ui->homePageEdit->text();
    data->homePage = data->homePage.fromEncoded(urlString.toUtf8());
    data->save_homePage();
}

//load a webpage on the current tab from history
void MainWindow::on_historyListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString urlString = item->text();
    loadUrl_on_currentTab(QUrl(urlString.toUtf8()));
}

// load the clicked favorite to the current tab
void MainWindow::on_favoritesListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    for( int i=0; i<data->favoritesList.count(); ++i )
    {
        Favorite favorite = data->favoritesList[i];
        // if the pointer saved in the favorite is the same as the current item, they match up
        if (item == favorite.listItem) {
            loadUrl_on_currentTab(favorite.url);
        }
    }
}

// remove all history data
void MainWindow::on_clearHistoryButton_clicked()
{
    data->clear_historyData();
    ui->historyListWidget->clear();
}

// go back a page for the tab
void MainWindow::on_backButton_clicked()
{
    // get current web view
    QWebEngineView* pWebView = NULL;
    QWidget* pWidget = ui->browserTabs->widget(ui->browserTabs->currentIndex());
    pWebView = (QWebEngineView*)pWidget;

    //load previous page;
    pWebView->back();
}

// go forward a page for the tab
void MainWindow::on_forwardButton_clicked()
{
    // get current web view
    QWebEngineView* pWebView = NULL;
    QWidget* pWidget = ui->browserTabs->widget(ui->browserTabs->currentIndex());
    pWebView = (QWebEngineView*)pWidget;

    //load next page;
    pWebView->forward();
}

// add a new favorite
void MainWindow::on_addButton_clicked()
{
    editWindow;
    editWindow.setWindowTitle("Add Favorite");
    editWindow.show();

    // create a new favorite
    Favorite newFavorite;
    data->favoritesList << newFavorite;
    ui->favoritesListWidget->addItem("");
    data->favoritesList[data->favoritesList.count() - 1].listItem = ui->favoritesListWidget->item(ui->favoritesListWidget->count() - 1);

    // edit the new favorite with the FavoriteEdit window
    editWindow.setEditItem(data->favoritesList[data->favoritesList.count() - 1], *data);
}

// Edit the currently selected favorite
void MainWindow::on_editButton_clicked()
{
    // if there is nothing selected
    if (ui->favoritesListWidget->currentRow() == -1) {
        return;
    }

    editWindow;
    editWindow.setWindowTitle("Edit Favorite");
    editWindow.show();

    // find the current favorite
    int index;
    QListWidgetItem *currentItem = ui->favoritesListWidget->currentItem();
    for( int i=0; i<data->favoritesList.count(); ++i )
    {
        Favorite favorite = data->favoritesList[i];
        // if the pointer saved in the favorite is the same as the current item, they match up
        if (currentItem == favorite.listItem) {
            index = i;
        }
    }

    // edit the new favorite with the FavoriteEdit window
    editWindow.setEditItem(data->favoritesList[index], *data);
}

// delete the selected favorite
void MainWindow::on_deleteButton_clicked()
{
    QListWidgetItem *currentItem = ui->favoritesListWidget->currentItem();
    for( int i=0; i<data->favoritesList.count(); ++i )
    {
        Favorite favorite = data->favoritesList[i];
        // if the pointer saved in the favorite is the same as the current item, they match up
        if (currentItem == favorite.listItem) {
            data->favoritesList.removeAt(i);
            ui->favoritesListWidget->takeItem(ui->favoritesListWidget->currentRow());
            data->save_favoritesData();
            return;
        }
    }
}
