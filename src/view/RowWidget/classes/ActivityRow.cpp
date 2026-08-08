#include "ActivityRow.h"
#include "ActivityUtilities.h"
#include "ConfirmPopup.h"

#include <QFile>
#include <QSvgRenderer>
#include <QPainter>
#include <QRegularExpression>

////////////////
// Costruttore
////////////////

ActivityRow::ActivityRow(Activity* activity, QWidget* parent) : QWidget(parent), act(activity), content(nullptr) {

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(categoryStyle(act->getCategory()));
    setObjectName("Root");

    setupUI();
    setupConnections();
}

////////////////
// Setup UI
////////////////

void ActivityRow::setupUI() {
    
    box = new QVBoxLayout(this);

    // Intestazione
    header = new QLabel();
    header->setText(act->getTitle());
    header->setWordWrap(true);
    header->setMinimumHeight(30);

    // Pulsante espandi/contrai
    expand = new QPushButton();
    expand->setIcon(QIcon(":/Right.svg"));
    expand->setIconSize(QSize(18, 18));
    expand->setFixedSize(20, 20);

    // Etichetta "Completata"
    complete = new QLabel("Completata");
    complete->setStyleSheet("font-style: italic; color: rgba(255,255,255,120); font-weight: 500;");
    complete->hide();

    // Icona colorata per categoria
    QLabel* iconLabel = new QLabel();
    iconLabel->setFixedSize(24, 24);

    QString iconPath;
    QString accentColor;
    switch (act->getCategory()) {

        case Activity::ActivityCategory::Event:

            iconPath = ":/Event.svg";
            accentColor = "#22C55E";
        break;

        case Activity::ActivityCategory::Appointment:

            iconPath = ":/Appointment.svg";
            accentColor = "#22D3EE";
        break;

        case Activity::ActivityCategory::SimpleTask:

            iconPath = ":/Task.svg";
            accentColor = "#7C3AED";
        break;

        case Activity::ActivityCategory::CompositeTask:

            iconPath = ":/Composite.svg";
            accentColor = "#F59E0B";
        break;
    }

    iconLabel->setPixmap(colorSvgIcon(iconPath, accentColor));

    // Badge categoria
    QLabel* categoryBadge = new QLabel(CatToString(act->getCategory()));
    categoryBadge->setObjectName("categoryBadge");

    // Layout testo (titolo + badge)
    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(header);
    textLayout->addWidget(categoryBadge, 0, Qt::AlignLeft);

    // Layout intestazione
    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->addWidget(iconLabel);
    headerLayout->addSpacing(10);
    headerLayout->addLayout(textLayout);
    headerLayout->addWidget(expand);
    headerLayout->addWidget(complete, Qt::AlignLeft);
    headerLayout->setAlignment(Qt::AlignTop);

    box->addLayout(headerLayout);
}

////////////////
// Setup Connessioni
////////////////

void ActivityRow::setupConnections()
{
    connect(expand, &QPushButton::clicked, this, [this]() {

        if (!content) return;

        bool isVisible = content->isVisible();
        content->setVisible(!isVisible);
        expand->setIcon(QIcon(isVisible ? ":/Right.svg" : ":/Down.svg"));
    });

    connect(expand, &QPushButton::clicked, this, [this]() {

        emit contentToggled();
    });
}

////////////////
// Lazy initialization dei pulsanti azione
////////////////

QPushButton* ActivityRow::getDeleteButton()
{
    if (!del) {

        del = new QPushButton("Elimina");
        del->setIcon(QIcon(":/Trash.svg"));
        del->setIconSize(QSize(18, 18));
        del->setStyleSheet(
            "QPushButton {"
            "   border: 2px solid #D32F2F;"
            "   border-radius: 6px;"
            "   padding: 5px 10px;"
            "   color: #D32F2F;"
            "   background-color: transparent;"
            "   margin-top: 20%;"
            "}"
            "QPushButton:pressed, QPushButton:hover {"
            "   border: 2px solid red;"
            "   background-color: rgba(255, 255, 255, 25);"
            "}"
        );

        connect(del, &QPushButton::clicked, this, [this]() {

            ConfirmPopup* popup = new ConfirmPopup("Procedendo si eliminerà l'attività definitivamente. \nContinuare?", this);
            connect(popup, &ConfirmPopup::confirmed, this, [this]() {

                emit remove(act->getID());
            });

            popup->showCenteredTop(del);
        });
    }
    return del;
}

QPushButton* ActivityRow::getModifyButton()
{
    if (!modify) {
        modify = new QPushButton("Modifica");
        modify->setIcon(QIcon(":/Edit.svg"));
        modify->setIconSize(QSize(18, 18));
        modify->setStyleSheet(
            "QPushButton {"
            "   border: 2px solid #E9ECEF;"
            "   border-radius: 6px;"
            "   padding: 5px 10px;"
            "   color: #E9ECEF;"
            "   background-color: transparent;"
            "   margin-top: 20%;"
            "}"
            "QPushButton:pressed, QPushButton:hover {"
            "   border: 2px solid #F8F9FA;"
            "   background-color: rgba(255, 255, 255, 25);"
            "}"
        );
        connect(modify, &QPushButton::clicked, this, [this]() {

            emit edit(act->getID());
        });
    }
    return modify;
}

////////////////
// Gestione contenuto espandibile
////////////////

void ActivityRow::addContent(QWidget* c)
{
    content = c;
    content->hide();
    box->addWidget(content);
}

void ActivityRow::closeContent()
{
    if (content) {

        content->hide();
        expand->setIcon(QIcon(":/Right.svg"));
    }
}

////////////////
// Marca come completata una task
////////////////

void ActivityRow::markCompleted()
{
    expand->hide();
    complete->setVisible(true);
}

////////////////
// Utility: colorazione SVG
////////////////

QPixmap ActivityRow::colorSvgIcon(const QString& path, const QString& color)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {

        return QPixmap();
    }

    QString svg = QString::fromUtf8(file.readAll());
    file.close();

    // Sostituisce il colore fill (escluso "none")
    svg.replace(QRegularExpression(R"(fill="(?!none)[^"]*")"), QString(R"(fill="%1")").arg(color));

    QSvgRenderer renderer(svg.toUtf8());
    QPixmap pixmap(24, 24);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    renderer.render(&painter);

    return pixmap;
}

////////////////
// Getter
////////////////

Activity* ActivityRow::getActivity() const
{
    return act;
}