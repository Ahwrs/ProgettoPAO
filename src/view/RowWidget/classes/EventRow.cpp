#include "EventRow.h"
#include "ActivityUtilities.h"
#include "Appointment.h"

EventRow::EventRow(Activity* a, QWidget* p) : ActivityRow(a, p) {

    QWidget* contentWidget = new QWidget();
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);

    QLabel* desc = new QLabel(act->getDescription());
    contentLayout->addWidget(desc);

    Event* ev = dynamic_cast<Event*>(a);
    if (!ev) return;

    QHBoxLayout* dateLayout = new QHBoxLayout();
    QLabel* dateIcon = new QLabel();
    dateIcon->setPixmap(QIcon(":/Date.svg").pixmap(16, 16));
    QLabel* dateLabel = new QLabel(
    QLocale().toString(ev->getDate(), "dddd d MMMM yyyy")
                .replace(0, 1,
                        QLocale().toString(ev->getDate(), "dddd")
                            .left(1).toUpper())
    );
    dateLayout->addWidget(dateIcon);
    dateLayout->addWidget(dateLabel);
    dateLayout->addStretch();

    QHBoxLayout* timeLayout = new QHBoxLayout();
    QLabel* timeIcon = new QLabel();
    timeIcon->setPixmap(QIcon(":/Time.svg").pixmap(16, 16));
    QLabel* timeLabel = new QLabel(ev->getStartTime().toString("HH:mm") + " - " + ev->getEndTime().toString("HH:mm"));
    timeLayout->addWidget(timeIcon);
    timeLayout->addWidget(timeLabel);
    timeLayout->addStretch();

    contentLayout->addLayout(dateLayout);
    contentLayout->addLayout(timeLayout);

    if (Appointment* ap = dynamic_cast<Appointment*>(ev)) {

        QHBoxLayout* linkLayout = new QHBoxLayout();
        bool isOnline = ap->getIsOnline();

        QLabel* linkIcon = new QLabel();
        linkIcon->setPixmap(QIcon(isOnline ? ":/Link.svg" : ":/Globe.svg").pixmap(16, 16));
        linkLayout->addWidget(linkIcon);

        QString prefix = isOnline ? "Meeting: " : "Location: ";
        QLabel* linkLabel = new QLabel();
        linkLabel->setTextFormat(Qt::RichText);
        linkLabel->setOpenExternalLinks(true);
        linkLabel->setText(prefix + QString("<a href='%1'>%2</a>").arg(safeURL(ap->getLink()), ap->getLink()));
        linkLayout->addWidget(linkLabel);
        linkLayout->addStretch();

        contentLayout->addLayout(linkLayout);
    }

    contentLayout->addWidget(modify);
    contentLayout->addWidget(del);
    addContent(contentWidget);
}