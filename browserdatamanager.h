#ifndef BROWSERDATAMANAGER_H
#define BROWSERDATAMANAGER_H
#include <QList>
#include "favorite.h"


class BrowserDataManager
{
public:
    BrowserDataManager();
    QList<Favorite> favoritesList;
    QList<QUrl> historyList;
    QUrl homePage;
    void load_favoritesData();
    void load_historyData();
    void load_homePage();
    void save_favoritesData();
    void save_historyData();
    void save_homePage();
    void clear_favoritesData();
    void clear_historyData();
};

#endif // BROWSERDATAMANAGER_H
