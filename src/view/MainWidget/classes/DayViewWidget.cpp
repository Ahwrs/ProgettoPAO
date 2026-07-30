#include "DayViewWidget.h"
#include <QScrollArea>

DayViewWidget::DayViewWidget(QWidget* p) : QWidget(p){

    QVBoxLayout* box = new QVBoxLayout(this);
    QScrollArea* scrollArea = new QScrollArea();
    QWidget* scrollContent = new QWidget();
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);

    selector = new DaySelectorWidget();
    QWidget* TContent = new QWidget();
    TLayout = new QVBoxLayout(TContent);
    QWidget* EContent = new QWidget();
    ELayout = new QVBoxLayout(EContent);


    scrollLayout->addWidget(TContent);
    scrollLayout->addWidget(EContent);
    scrollLayout->addStretch();

    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    box->addWidget(selector);
    box->addWidget(scrollArea);

    Add = new QPushButton(this);   // parent = this, MAI aggiunto a "box" o altro layout
    Add->setFixedSize(40, 40);
    Add->setStyleSheet(
        "QPushButton {"
        "   background-color: #7C3AED;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 20px;"   // metà della dimensione fissa = cerchio perfetto
        "   font-size: 24pt;"
        "}"
        "QPushButton:hover { background-color: #6D28D9; }"
    );
    Add->raise();   // garantisce che resti disegnato SOPRA scrollArea

    connect(Add, &QPushButton::clicked, this, [this]{ emit newActivityRequested(); });

    repositionAddButton();
}


void DayViewWidget::replaceLayoutContents(QBoxLayout* layout, const std::vector<ActivityRow*>& rows) {
    
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if(item->widget()) item->widget()->deleteLater();
        delete item;
    }
    for (ActivityRow* row : rows) layout->addWidget(row);
}

void DayViewWidget::setTaskRows(const std::vector<ActivityRow*>& rows) {
    replaceLayoutContents(TLayout, rows);
}

void DayViewWidget::setEventRows(const std::vector<ActivityRow*>& rows) {
    replaceLayoutContents(ELayout, rows);
}

// DayViewWidget.cpp — nuovi metodi
void DayViewWidget::resizeEvent(QResizeEvent* event) {

    QWidget::resizeEvent(event);
    repositionAddButton();
}

void DayViewWidget::repositionAddButton() {

    int margin = 20;
    Add->move(width() - Add->width() - margin, height() - Add->height() - margin);
}