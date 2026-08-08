#include "DayViewWidget.h"
#include "DaySelectorWidget.h"
#include "EventRow.h"
#include "Event.h"
#include "DatePopup.h"

////////////////
// Costruttore
////////////////

DayViewWidget::DayViewWidget(QWidget* parent) : QWidget(parent){
    
    setupUI();
    setupConnections();
    repositionAddButton();
}

////////////////
// Setup UI
////////////////

void DayViewWidget::setupUI(){

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Selettore giorno
    selector = new DaySelectorWidget();

    // Pulsante per aprire il calendario
    datePickerBtn = new QPushButton("Seleziona Data");
    datePickerBtn->setStyleSheet(
        "QPushButton {"
        "   border: 1px solid rgba(150,150,150,150);"
        "   border-radius: 6px;"
        "   background-color: transparent;"
        "   padding: 4px 8px;"
        "   margin: 8px 0px;"
        "}"
        "QPushButton:hover { background-color: rgba(255,255,255,15); }"
    );

    // Barra di ricerca
    searchBar = new SearchWidget();

    // Area scrollabile
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFrameShape(QFrame::NoFrame);

    timeline = new TimelineWidget();

    // Contenitore dello scroll
    QWidget* scrollContent = new QWidget();
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);

    // Container per i risultati di ricerca
    searchContainer = new QWidget();
    searchLayout = new QVBoxLayout(searchContainer);
    searchContainer->hide();
    scrollLayout->addWidget(searchContainer);
    scrollLayout->addSpacing(10);

    // Container per i Task
    taskContainer = new QWidget();
    taskContainer->setObjectName("taskContainer");
    taskContainer->setAttribute(Qt::WA_StyledBackground, true);
    taskContainer->setStyleSheet(
        "#taskContainer {"
        "   border: 1px solid rgb(77, 40, 131);"
        "   border-radius: 6px;"
        "}"
    );

    QHBoxLayout* taskHeader = new QHBoxLayout();
    QLabel* taskIcon = new QLabel();
    taskIcon->setPixmap(QIcon(":/Task.svg").pixmap(20, 20));
    QLabel* taskLabel = new QLabel("Tasks");
    taskLabel->setStyleSheet("color: white; font-weight: 700; font-size: 11pt; font-family: Arial;");
    taskHeader->addWidget(taskIcon);
    taskHeader->addWidget(taskLabel);
    taskHeader->addStretch();

    taskLayout = new QVBoxLayout(taskContainer);
    taskLayout->addLayout(taskHeader);
    taskLayout->setContentsMargins(8, 8, 8, 8);
    taskLayout->addSpacing(10);

    scrollLayout->addWidget(taskContainer);
    scrollLayout->addSpacing(10);

    // Container per gli Event (con timeline)
    eventSection = new QWidget();
    eventSection->setObjectName("eventsSection");
    eventSection->setAttribute(Qt::WA_StyledBackground, true);
    eventSection->setStyleSheet(
        "#eventsSection {"
        "   border: 1px solid rgb(55, 112, 195);"
        "   border-radius: 6px;"
        "   background-color: transparent;"
        "}"
    );
    QVBoxLayout* eventLayout = new QVBoxLayout(eventSection);

    QHBoxLayout* eventHeader = new QHBoxLayout();
    QLabel* eventIcon = new QLabel();
    eventIcon->setPixmap(QIcon(":/Events.svg").pixmap(20, 20));
    QLabel* eventsLabel = new QLabel("Events");
    eventsLabel->setStyleSheet("color: white; font-weight: 700; font-family: Arial; font-size: 11pt;");
    eventHeader->addWidget(eventIcon);
    eventHeader->addWidget(eventsLabel);
    eventHeader->addStretch();

    eventLayout->addLayout(eventHeader);
    eventLayout->addSpacing(10);
    eventLayout->addWidget(timeline);

    scrollLayout->addWidget(eventSection);

    scrollArea->setWidget(scrollContent);

    // Aggiunge i widget principali al layout
    mainLayout->addWidget(selector);
    mainLayout->addWidget(datePickerBtn, 0, Qt::AlignHCenter);
    mainLayout->addWidget(searchBar, 0, Qt::AlignHCenter);
    mainLayout->addWidget(scrollArea);

    // Pulsante "Aggiungi" 
    addBtn = new QPushButton(this);
    addBtn->setFixedSize(40, 40);
    addBtn->setIcon(QIcon(":/Add.svg"));
    addBtn->setIconSize(QSize(20, 20));
    addBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #7C3AED;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 20px;"
        "   font-size: 24pt;"
        "}"
        "QPushButton:hover { background-color: #6D28D9; }"
    );
    addBtn->raise();
}

////////////////
// Setup connessioni
////////////////

void DayViewWidget::setupConnections(){

    connect(selector, &DaySelectorWidget::dateChanged, this, &DayViewWidget::dayChanged);

    connect(datePickerBtn, &QPushButton::clicked, this, [this]() {
        
        DatePopup* popup = new DatePopup(this);
        connect(popup, &DatePopup::dateSelected, this, [this](QDate date) {
            
            selector->goToDate(date);
        });
        popup->showBelow(datePickerBtn);
    });

    connect(searchBar, &SearchWidget::criteriaChanged, this, &DayViewWidget::searchCriteriaChanged);

    connect(addBtn, &QPushButton::clicked, this, [this]() {
        
        emit newActivityRequested();
    });
}

////////////////
// Metodi pubblici
////////////////

void DayViewWidget::setTaskRows(const std::vector<ActivityRow*>& rows){

    // Rimuove tutte le righe tranne l'header (indice 0)
    QLayoutItem* item;
    while ((item = taskLayout->takeAt(1)) != nullptr) {

        if (item->widget()) {
            
            item->widget()->deleteLater();
        }
        delete item;
    }

    for (ActivityRow* row : rows) {
        
        taskLayout->addWidget(row);
        taskLayout->addSpacing(5);
    }
}

void DayViewWidget::setEventRows(const std::vector<ActivityRow*>& rows){

    timeline->setEventRows(rows);
}

void DayViewWidget::setSearchResults(const std::vector<ActivityRow*>& rows){
    
    // Svuota il container di ricerca
    QLayoutItem* item;
    while ((item = searchLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            
            item->widget()->deleteLater();
        }
        delete item;
    }

    for (ActivityRow* row : rows) {
        searchLayout->addWidget(row);
    }
    searchLayout->addStretch();

    // Nasconde i container normali e mostra i risultati
    taskContainer->hide();
    eventSection->hide();
    timeline->hide();
    searchContainer->show();
}

void DayViewWidget::clearSearch(){

    searchContainer->hide();
    taskContainer->show();
    eventSection->show();
    timeline->show();
}

QDate DayViewWidget::currentDate() const{

    return selector->currentDate();
}

void DayViewWidget::goToToday(){

    selector->goToDate(QDate::currentDate());
}

void DayViewWidget::focusSearch(){

    searchBar->openPanel();
}

////////////////
// Eventi di resize
////////////////

void DayViewWidget::resizeEvent(QResizeEvent* event){

    QWidget::resizeEvent(event);
    repositionAddButton();
}

void DayViewWidget::repositionAddButton(){

    int margin = 20;
    addBtn->move(width() - addBtn->width() - margin, height() - addBtn->height() - margin);
}