#ifndef FAVORITEEDIT_H
#define FAVORITEEDIT_H
#include "favorite.h"
#include "browserdatamanager.h"
#include <QDialog>

namespace Ui {
class FavoriteEdit;
}

class FavoriteEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FavoriteEdit(QWidget *parent = 0);
    ~FavoriteEdit();
    Favorite *editItem;
    BrowserDataManager *browserData;
    void setEditItem(Favorite&, BrowserDataManager&);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::FavoriteEdit *ui;
};

#endif // FAVORITEEDIT_H
