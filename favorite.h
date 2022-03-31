#ifndef FAVORITE_H
#define FAVORITE_H
#include <QUrl>
#include <QListWidgetItem>

class Favorite
{
public:
    Favorite();
    Favorite(QString, QUrl);
    QUrl url;
    QString name;
    QListWidgetItem *listItem;
};

#endif // FAVORITE_H
