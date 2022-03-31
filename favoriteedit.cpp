#include "favoriteedit.h"
#include "ui_favoriteedit.h"
#include "qdebug.h"

FavoriteEdit::FavoriteEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FavoriteEdit)
{
    ui->setupUi(this);
}

FavoriteEdit::~FavoriteEdit()
{
    delete ui;
}

// set the edit item and get access to the browserData
void FavoriteEdit::setEditItem(Favorite& item, BrowserDataManager& data) {

    // fill window items with favorite information
    browserData = &data;
    editItem = &item;
    ui->nameEdit->setText(editItem->name);
    ui->urlEdit->setText(editItem->url.toString());
}

// If accept is chosen, add or edit the appropriate favorite
void FavoriteEdit::on_buttonBox_accepted()
{
    editItem->name = ui->nameEdit->text();
    editItem->url = QUrl(ui->urlEdit->text().toUtf8());
    editItem->listItem->setText(ui->nameEdit->text());
    browserData->save_favoritesData();
}

// If cancel is chosen, destroy the edit window
void FavoriteEdit::on_buttonBox_rejected()
{
    destroy();
}
