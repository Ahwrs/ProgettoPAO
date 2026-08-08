#ifndef POPUP_WIDGET_H
#define POPUP_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>

////////////////
// PopupWidget (classe base)
////////////////

class PopupWidget : public QWidget {
    Q_OBJECT

private:

    QVBoxLayout* box;

protected:

    void addContent(QWidget* content);

public:

    PopupWidget(QWidget* parent = nullptr);

    void showCenteredTop(QWidget* mainWidget, int topMargin = 20);
    void showBelow(QWidget* anchor);
};

#endif