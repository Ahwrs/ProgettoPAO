#include "EventDetailView.h"
#include "Event.h"
#include "Appointment.h"
#include "ConfirmPopup.h"
#include <QBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>

////////////////
// Costruttori
////////////////

EventDetailView::EventDetailView(Event* ev, QWidget* parent) : QWidget(parent), activityId(ev->getID()), category(ev->getCategory()){

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(detailStyle());

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Dettagli Attività");
    title->setObjectName("detailsTitle");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    addCommonFields(ev, layout);
    layout->addStretch();
    addButtons(layout);
}

EventDetailView::EventDetailView(Appointment* ap, QWidget* parent) : QWidget(parent), activityId(ap->getID()), category(ap->getCategory()){

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(detailStyle());

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Dettagli Attività");
    title->setObjectName("detailsTitle");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    addCommonFields(ap, layout);

    layout->addWidget(makeCard(ap->getIsOnline() ? "Link" : "Luogo", ap->getLink()));

    layout->addStretch();
    addButtons(layout);
}

////////////////
// Metodi privati
////////////////

QString EventDetailView::detailStyle() const
{
    QString accent = (category == Activity::ActivityCategory::Event)
                     ? "rgba(34,197,94,1)"
                     : "rgba(34,211,238,1)";

    QString style =
        "QWidget {" 
        "   background-color: transparent;" 
        "   color:white; font-family:Arial;" 
        "   font-size:14px;" 
        "}"

        "QLabel#detailsTitle { "
        "   color:white;" 
        "   font-size:24px;"
        "   border-bottom: 1px solid %1;" 
        "   padding-bottom: 5px;" 
        "   margin-bottom: 10px;" 
        "   font-weight:700;" 
        "}"

        "QFrame#card {" 
        "   border:2px solid transparent;" 
        "   border-radius:8px;"
        "   padding:8px 12px;" 
        "   background-color: #13151B;" 
        "   margin-top: 5px;" 
        "}"
        
        "QFrame#card QLabel {" 
        "   background:transparent;" 
        "   border:none; color:white;" 
        "   font-weight:700;" 
        "}"
        
        "QFrame#card QLabel#header {" 
        "   color: %1;" 
        "   font-size:12px;" 
        "}"
        
        "#deleteButton {" 
        "   border: 2px solid #D32F2F;"
        "   border-radius: 6px;" 
        "   padding: 5px 10px;" 
        "   color: #D32F2F;" 
        "   background-color: transparent;" 
        "}"

        "#deleteButton:pressed, #deleteButton:hover {" 
        "   border: 2px solid red;" 
        "   background-color: rgba(255,255,255,25);"
        "}"
        
        "#editButton {" 
        "   border: 2px solid #E9ECEF;" 
        "   border-radius: 6px;" 
        "   padding: 5px 10px;" 
        "   color: #E9ECEF;" 
        "   background-color: transparent;" 
        "}"
        
        "#editButton:pressed, #editButton:hover {" 
        "   border: 2px solid #F8F9FA;" 
        "   background-color: rgba(255,255,255,25);"
        "}"
        
        "#backButton {" 
        "   border: 2px solid #2563EB;"
        "   border-radius: 6px;" 
        "   padding: 5px 10px;" 
        "   color: #2563EB;" 
        "   background-color: transparent;" 
        "   font-weight: 700;" 
        "}"

        "#backButton:pressed, #backButton:hover {" 
        "   border: 2px solid #1D4ED8;" 
        "   background-color: rgba(255,255,255,25);"
        "}";

    return style.arg(accent);
}

QWidget* EventDetailView::makeCard(const QString& header, const QString& value){
    
    QFrame* card = new QFrame();
    card->setObjectName("card");

    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(12, 8, 12, 8);

    QLabel* h = new QLabel(header);
    h->setObjectName("header");

    QLabel* text = new QLabel(value);
    text->setWordWrap(true);
    text->setTextInteractionFlags(Qt::TextSelectableByMouse);

    cardLayout->addWidget(h);
    cardLayout->addWidget(text);

    return card;
}

void EventDetailView::addCommonFields(Event* ev, QVBoxLayout* layout){
    
    layout->addWidget(makeCard("Titolo", ev->getTitle()));

    QString desc = ev->getDescription();
    layout->addWidget(makeCard("Descrizione", desc.isEmpty() ? "Nessuna descrizione" : desc));

    layout->addWidget(makeCard("Data", ev->getDate().toString("dddd d MMMM yyyy")));
    layout->addWidget(makeCard("Orario", ev->getStartTime().toString("HH:mm") + " - " + ev->getEndTime().toString("HH:mm")));
}

void EventDetailView::addButtons(QVBoxLayout* layout){

    QHBoxLayout* btnLayout = new QHBoxLayout();

    QPushButton* backBtn = new QPushButton("Indietro");
    backBtn->setObjectName("backButton");
    backBtn->setIcon(QIcon(":/Left.svg"));
    backBtn->setIconSize(QSize(18, 18));

    QPushButton* modifyBtn = new QPushButton("Modifica");
    modifyBtn->setObjectName("editButton");
    modifyBtn->setIcon(QIcon(":/Edit.svg"));
    modifyBtn->setIconSize(QSize(18, 18));

    QPushButton* deleteBtn = new QPushButton("Elimina");
    deleteBtn->setObjectName("deleteButton");
    deleteBtn->setIcon(QIcon(":/Trash.svg"));
    deleteBtn->setIconSize(QSize(18, 18));

    btnLayout->addWidget(backBtn);
    btnLayout->addStretch();
    btnLayout->addWidget(modifyBtn);
    btnLayout->addWidget(deleteBtn);

    layout->addLayout(btnLayout);

    connect(backBtn, &QPushButton::clicked, this, [this]() { emit backRequested();});
    connect(modifyBtn, &QPushButton::clicked, this, [this]() { emit editRequested(activityId);});

    connect(deleteBtn, &QPushButton::clicked, this, [this]() {
        
        ConfirmPopup* popup = new ConfirmPopup("Procedendo si eliminerà l'attività definitivamente.\nContinuare?", this);

        connect(popup, &ConfirmPopup::confirmed, this, [this]() {
            
            emit deleteRequested(activityId);
        });
        popup->showCenteredTop(this);
    });
}