#include "PopupWidget.h"

////////////////
// Costruttore
////////////////

PopupWidget::PopupWidget(QWidget* parent) : QWidget(parent){

    setAttribute(Qt::WA_StyledBackground, true);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(Qt::Popup);

    box = new QVBoxLayout(this);
}

////////////////
// Metodi di posizionamento
////////////////

// Top
void PopupWidget::showCenteredTop(QWidget* mainWidget, int topMargin){

    QWidget* topLevel = mainWidget->window();

    QPoint origin = topLevel->mapToGlobal(QPoint(0, 0));
    adjustSize();

    int x = origin.x() + (topLevel->width() - width()) / 2;
    int y = origin.y() + topMargin;

    move(x, y);
    show();
}

// Bottom
void PopupWidget::showBelow(QWidget* anchor){

    adjustSize();

    QPoint anchorBottomLeft = anchor->mapToGlobal(QPoint(0, anchor->height()));
    int x = anchorBottomLeft.x() + (anchor->width() - width()) / 2;
    int y = anchorBottomLeft.y();

    move(x, y);
    show();
}

////////////////
// Aggiunta contenuto
////////////////

void PopupWidget::addContent(QWidget* content)
{
    box->addWidget(content);
}