#include "TaskRow.h"

TaskRow::TaskRow(Activity* a, CompositeTask* parent, QWidget* p) : ActivityRow(a, p), prtComposite(parent){
    
    QWidget* CWidget = new QWidget();
    QVBoxLayout* CLayout = new QVBoxLayout(CWidget);

    if (SimpleTask* st = dynamic_cast<SimpleTask*>(act)) {
        
        QPushButton* complete = new QPushButton("Completa");
        complete->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogApplyButton));

        complete->setStyleSheet(
            "QPushButton {"
            "   border: 2px solid #388E3C;"  
            "   border-radius: 6px;"
            "   padding: 5px 10px;"
            "   color: #388E3C;"            
            "   background-color: transparent;"
            "}"
            "QPushButton:hover {"
            "   background-color: #E8F5E9;" 
            "}"
            "QPushButton:pressed {"
            "   background-color: #C8E6C9;"
            "}"
        );
        
        QLabel* desc = new QLabel();
        desc->setText(act->getDescription());
        CLayout->addWidget(desc);
        QHBoxLayout* BTNLayout = new QHBoxLayout();

        connect(complete, &QPushButton::clicked, this, [this]{

            QString msg = prtComposite 
            ? "Una volta completata l'attivita' non sara' piu' disponibile per l'interazione. Continuare?"
            : "Una volta completata l'attivita' non sara' piu' disponibile per l'interazione, e verra' eliminata al prossimo avvio dell'applicazione. Continuare?";
        
            if(QMessageBox::question(this, "Attenzione", msg) == QMessageBox::Yes){

                closeContent();
                this->setEnabled(false);
                this->setStyleSheet("QWidget:disabled { background-color: #006400;}");
                emit completeReq(act->getID());
            }
        });

        if(st->isCompleted()){

            closeContent();
            this->setStyleSheet("QWidget:disabled { background-color: #006400;}");
            this->setEnabled(false);
        }

        BTNLayout->addWidget(complete);
        BTNLayout->addWidget(del);
        CLayout->addLayout(BTNLayout);

    } else if (CompositeTask* ct = dynamic_cast<CompositeTask*>(act)) {
       
        QProgressBar* bar = new QProgressBar();
        bar->setRange(0, 100);
        bar->setValue(static_cast<int>(ct->getCompletionPercentage()));
        CLayout->addWidget(bar);

        for(const auto& sub : ct->getSubTasks()){

            TaskRow* subRow = new TaskRow(sub.get(), ct); 
            connect(subRow, &TaskRow::completeReq, this, &TaskRow::completeReq);
            connect(subRow, &ActivityRow::remove, this, &ActivityRow::remove);
            CLayout->addWidget(subRow);
        }

        CLayout->addWidget(del);
    }

    addContent(CWidget);
}