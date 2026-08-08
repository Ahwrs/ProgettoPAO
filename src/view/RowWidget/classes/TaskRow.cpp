#include "TaskRow.h"
#include "ConfirmPopup.h"

////////////////
// Costruttore per SimpleTask
////////////////

TaskRow::TaskRow(SimpleTask* st, CompositeTask* parent, QWidget* parentWidget) : ActivityRow(st, parentWidget), prtComposite(parent) {

    QWidget* contentWidget = new QWidget();
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);

    // Descrizione
    QLabel* desc = new QLabel(act->getDescription());
    desc->setWordWrap(true);
    contentLayout->addWidget(desc);

    // Pulsante Completa
    QPushButton* completeBtn = new QPushButton("Completa");
    completeBtn->setIcon(QIcon(":/Check.svg"));
    completeBtn->setIconSize(QSize(18, 18));
    completeBtn->setStyleSheet(
        "QPushButton {"
        "   border: 2px solid #388E3C;"
        "   border-radius: 6px;"
        "   padding: 5px 10px;"
        "   color: #388E3C;"
        "   background-color: transparent;"
        "   margin-top: 20%;"
        "}"
        "QPushButton:pressed, QPushButton:hover {"
        "   border: 2px solid green;"
        "   background-color: rgba(255, 255, 255, 25);"
        "}"
    );

    auto setCompleted = [this]() {

        closeContent();
        this->setEnabled(false);
        markCompleted();
    };

    connect(completeBtn, &QPushButton::clicked, this, [this, setCompleted]() {

        QString msg = prtComposite
            ? "Una volta completata l'attività non sarà più disponibile per l'interazione. \nContinuare?"
            : "Una volta completata l'attività non sarà più disponibile per l'interazione, \ne verrà eliminata al prossimo avvio dell'applicazione. Continuare?";

        ConfirmPopup* popup = new ConfirmPopup(msg, this);
        connect(popup, &ConfirmPopup::confirmed, this, [this, setCompleted]() {

            setCompleted();
            emit completeReq(act->getID());
        });

        popup->showCenteredTop(getDeleteButton());
    });

    // Se già completato, applica lo stato
    if (st->isCompleted()) {

        setCompleted();
    }

    // Pulsanti azione
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(completeBtn);
    if (!prtComposite) {

        buttonLayout->addWidget(getModifyButton());
    }
    buttonLayout->addWidget(getDeleteButton());
    contentLayout->addLayout(buttonLayout);

    addContent(contentWidget);
}

////////////////
// Costruttore per CompositeTask
////////////////

TaskRow::TaskRow(CompositeTask* ct, QWidget* parentWidget) : ActivityRow(ct, parentWidget), prtComposite(nullptr)
{
    QWidget* contentWidget = new QWidget();
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);

    // Etichetta e barra di completamento
    QLabel* barLabel = new QLabel("Completamento:");
    contentLayout->addWidget(barLabel);

    QProgressBar* bar = new QProgressBar();
    bar->setRange(0, 100);
    bar->setValue(static_cast<int>(ct->getCompletionPercentage()));
    bar->setStyleSheet(
        "QProgressBar {"
        "   border: none;"
        "   background-color: rgba(66, 66, 66, 0.5);"
        "   border-radius: 5px;"
        "   min-height: 10px;"
        "   max-height: 10px;"
        "   text-align: center;"
        "   margin-bottom: 20%;"
        "}"
        "QProgressBar::chunk {"
        "   background-color: rgb(124,58,237);"
        "   border-radius: 5px;"
        "}"
    );
    bar->setTextVisible(false);
    contentLayout->addWidget(bar);

    // Sotto-task ricorsivi
    for (const auto& sub : ct->getSubTasks()) {
        
        TaskRow* subRow = new TaskRow(sub.get(), ct);
        connect(subRow, &TaskRow::completeReq, this, &TaskRow::completeReq);
        connect(subRow, &ActivityRow::remove, this, &ActivityRow::remove);
        contentLayout->addWidget(subRow);
    }

    // Pulsanti azione
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(getModifyButton());
    btnLayout->addWidget(getDeleteButton());
    contentLayout->addLayout(btnLayout);

    addContent(contentWidget);
}