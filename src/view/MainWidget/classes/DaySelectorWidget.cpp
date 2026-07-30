#include "DaySelectorWidget.h"
#include <QBoxLayout>

namespace {
    const int DAYS_COUNT = 5;
    const int START_OFFSET = -2;
}

DaySelectorWidget::DaySelectorWidget(QWidget* parent) : QWidget(parent) {

    QHBoxLayout* box = new QHBoxLayout(this);
    setMaximumHeight(80);

    current = QDate::currentDate();

    last = new QPushButton(this);
    last->setIcon(QIcon(":/Left.svg"));
    last->setIconSize(QSize(32,32));
    connect(last, &QPushButton::clicked, this, [this] { refreshSelector(-1); });
    box->addWidget(last);

    days.reserve(DAYS_COUNT);
    for (int i = 0; i < DAYS_COUNT; ++i) {
        days.push_back(new QLabel(this));
        days[i]->setAlignment(Qt::AlignCenter);
        days[i]->setStyleSheet("border-radius: 8px; border: 1px solid #262526;");
        box->addWidget(days[i]);
    }
    updateDayLabels();

    int currentIndex = -START_OFFSET;
    days[currentIndex]->setStyleSheet("background-color: #7C3AED; color: white; border-radius: 8px;");

    next = new QPushButton(this);
    next->setIcon(QIcon(":/Right.svg"));
    next->setIconSize(QSize(32,32));
    connect(next, &QPushButton::clicked, this, [this] { refreshSelector(1); });
    box->addWidget(next);
}

void DaySelectorWidget::refreshSelector(int day) {
    current = current.addDays(day);
    updateDayLabels();
}

void DaySelectorWidget::updateDayLabels() {
    
    for (int i = 0; i < DAYS_COUNT; ++i) {
        QDate temp = current.addDays(i + START_OFFSET);
        days[i]->setText(QStringLiteral("%1<br><span style='font-size:16pt;'><b>%2</b></span>")
                         .arg(temp.toString("ddd"))
                         .arg(temp.toString("dd")));
    }
}