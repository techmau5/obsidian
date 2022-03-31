#include "browserdatamanager.h"
#include <QTextStream>
#include <QFile>
#include "qdebug.h"

BrowserDataManager::BrowserDataManager()
{
    load_favoritesData();
    load_historyData();
    load_homePage();
}

// load the favorites from a file
void BrowserDataManager::load_favoritesData() {

    //open the file if it exists
    QFile file("favorites.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream stream(&file);

    QString name;
    QString url;
    do {
       name = stream.readLine();
       url = stream.readLine();
       if (!name.isNull() && !url.isNull()) {
           Favorite newFavorite = Favorite();
           newFavorite.name = name;
           newFavorite.url = QUrl(url.toUtf8());
           favoritesList << newFavorite;
       }
    } while(!name.isNull());

    file.close();
}

// load the history from a file
void BrowserDataManager::load_historyData() {

    //open the file if it exists
    QFile file("history.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream stream(&file);

    QString url;
    do {
       url = stream.readLine();
       if (!url.isNull()) {
           QUrl newUrl = QUrl(url.toUtf8());
           historyList << newUrl;
       }
    } while(!url.isNull());

    file.close();
}

// save the favorites to a file
void BrowserDataManager::save_favoritesData() {

    // create a favorites.txt
    QFile file("favorites.txt");
    file.open(QIODevice::WriteOnly);

    // to output to file
    QTextStream qout(&file);

    // cycle through each of the items in the list and add them to the file
    // add the string "#*$" in between the name and the url to separate them later
    foreach( Favorite item, favoritesList )
    {
        QString data = QString(item.name) + "\n" + QString(item.url.toString());
        qout << data << endl;
    }

    file.close();
}

// save the history to a file
void BrowserDataManager::save_historyData() {

    // create a history.txt
    QFile file("history.txt");
    file.open(QIODevice::WriteOnly);

    // to output to file
    QTextStream qout(&file);

    // cycle through each of the items in the list and add them to the file
    foreach( QUrl item, historyList )
    {
        QString data = item.toString();
        qout << data << endl;
    }

    file.close();
}

// load the homePage
void BrowserDataManager::load_homePage() {

    //open the file if it exists
    QFile file("homepage.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //if the file does not exist, load google as homepage
        QString defaultHomePage = QStringLiteral("http://www.google.com/");
        homePage = QUrl(defaultHomePage.toUtf8());
        return;
    }

    QTextStream stream(&file);

    // set the homepage to the file's url if there is one, otherwise load google
    QString urlString = stream.readLine();
    if (!urlString.isNull()) {
        homePage = QUrl(urlString.toUtf8());
    } else {
        QString defaultHomePage = QStringLiteral("http://www.google.com/");
        homePage = QUrl(defaultHomePage.toUtf8());
    }

    file.close();
}

void BrowserDataManager::save_homePage() {
    // create a homepage.txt
    QFile file("homepage.txt");
    file.open(QIODevice::WriteOnly);

    // to output to file
    QTextStream qout(&file);

    // set the file text to the homepage url
    qout << homePage.toString();

    file.close();
}

void BrowserDataManager::clear_favoritesData() {
    favoritesList.clear();
    save_favoritesData();
}

void BrowserDataManager::clear_historyData() {
    historyList.clear();
    save_historyData();
}
