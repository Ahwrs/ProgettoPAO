// TaskRow.cpp
#include "TaskRow.h"

TaskRow::TaskRow(Activity* a, CompositeTask* parent, QWidget* p) : ActivityRow(a, p), prtComposite(parent) {
    
    QWidget* contentWidget = new QWidget();
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);

    if (SimpleTask* st = dynamic_cast<SimpleTask*>(act)) {

        QLabel* desc = new QLabel(act->getDescription());
        contentLayout->addWidget(desc);

        QPushButton* completeBtn = new QPushButton("Completa");
        completeBtn->setIcon(QIcon(":/Check.svg"));
        completeBtn->setStyleSheet(
            "QPushButton {"
            "   border: 2px solid #388E3C;"
            "   border-radius: 6px;"
            "   padding: 5px 10px;"
            "   color: #388E3C;"
            "   background-color: transparent;"
            "}"
            "QPushButton:pressed {"
            "   border: 2px solid green;"
            "   background-color: rgba(255, 255, 255, 25);"
            "}"
        );

        auto setCompleted = [this] {

            closeContent();
            this->setEnabled(false);
        };

        connect(completeBtn, &QPushButton::clicked, this, [this, setCompleted] {

            QString msg = prtComposite
                ? "Una volta completata l'attività non sarà più disponibile per l'interazione. Continuare?"
                : "Una volta completata l'attività non sarà più disponibile per l'interazione, e verrà eliminata al prossimo avvio dell'applicazione. Continuare?";
            
            if (QMessageBox::question(this, "Attenzione", msg) == QMessageBox::Yes) {
                
                setCompleted();
                emit completeReq(act->getID());
            }
        });

        if (st->isCompleted()) {

            setCompleted();
        }

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(completeBtn);
        buttonLayout->addWidget(del);
        contentLayout->addLayout(buttonLayout);
    }
    else if (CompositeTask* ct = dynamic_cast<CompositeTask*>(act)) {

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
            "}"
            "QProgressBar::chunk {"
            "   background-color: rgb(124,58,237);"
            "   border-radius: 5px;"
            "}"
        );

        bar->setTextVisible(false);
        contentLayout->addWidget(bar);

        for (const auto& sub : ct->getSubTasks()) {
            
            TaskRow* subRow = new TaskRow(sub.get(), ct);
            connect(subRow, &TaskRow::completeReq, this, &TaskRow::completeReq);
            connect(subRow, &ActivityRow::remove, this, &ActivityRow::remove);
            contentLayout->addWidget(subRow);
        }

        contentLayout->addWidget(del);
    }

    addContent(contentWidget);
}