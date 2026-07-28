#include "EventRow.h"
#include "ActivityUtilities.h"
#include "Appointment.h"

EventRow::EventRow(Activity* a, QWidget* p) : ActivityRow(a, p){

    QWidget* CWidget = new QWidget();
    QVBoxLayout* CLayout = new QVBoxLayout(CWidget);

    /*this->setStyleSheet("background-color: red;");*/

    QLabel* desc = new QLabel(act->getDescription());
    CLayout->addWidget(desc);

    if(Appointment* ap = dynamic_cast<Appointment*>(a)){

        QString prefix = ap->getIsOnline() ? "Meeting: " : "Location: ";

        QLabel* LLabel = new QLabel();
        LLabel->setTextFormat(Qt::RichText);
        LLabel->setOpenExternalLinks(true); 
        LLabel->setText(prefix + QString("<a href='%1'>%2</a>").arg(safeURL(ap->getLink()), ap->getLink()));

        CLayout->addWidget(LLabel);
    }

    CLayout->addWidget(del);
    addContent(CWidget);
}