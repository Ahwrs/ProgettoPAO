#include "DaySelectorWidget.h"
#include <QBoxLayout>

namespace {
    const int DAYS_COUNT = 5;
    const int START_OFFSET = -2;
}

////////////////
// Costruttore
////////////////

DaySelectorWidget::DaySelectorWidget(QWidget* parent) : QWidget(parent) {

    QHBoxLayout* layout = new QHBoxLayout(this);
    setMaximumHeight(80);

    current = QDate::currentDate();

    // Pulsante "indietro"
    prevBtn = new QPushButton(this);
    prevBtn->setFixedSize(32, 32);
    prevBtn->setIcon(QIcon(":/Left.svg"));
    prevBtn->setIconSize(QSize(32, 32));
    prevBtn->setStyleSheet(
        "QPushButton {"
        "background-color: qradialgradient("
        "cx:0.5, cy:0.5,"
        "radius:0.8,"
        "fx:0.5, fy:0.5,"
        "stop:0 #5d39c9,"
        "stop:1 #24104f);"
        "border:2px solid #8c4dff;"
        "border-radius:16px;"
        "color:white;"
        "font-size:26px;"
        "font-weight:bold;"
        "padding:0px;"
        "}"
    );
    connect(prevBtn, &QPushButton::clicked, this, [this]() { refreshSelector(-1); });
    layout->addWidget(prevBtn);

    // Etichette dei giorni
    days.reserve(DAYS_COUNT);
    for (int i = 0; i < DAYS_COUNT; ++i) {
        days.push_back(new QLabel(this));
        days[i]->setFixedSize(60, 70);
        days[i]->setAlignment(Qt::AlignCenter);
        days[i]->setStyleSheet("border-radius: 12px; border: 1px solid rgba(150,150,180,150);" );
        layout->addWidget(days[i]);
    }
    updateDayLabels();

    // Evidenzia il giorno centrale
    int centerIndex = -START_OFFSET;
    days[centerIndex]->setStyleSheet(

        "border-radius: 12px; border: 3px solid rgba(167,139,250,255);"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "   stop:0 #7C3AED, stop:1 #7C3AED55);"
        "color: white;"
    );

    // Pulsante "avanti"
    nextBtn = new QPushButton(this);
    nextBtn->setFixedSize(32, 32);
    nextBtn->setIcon(QIcon(":/Right.svg"));
    nextBtn->setIconSize(QSize(32, 32));
    nextBtn->setStyleSheet(
        "QPushButton {"
        "background-color: qradialgradient("
        "cx:0.5, cy:0.5,"
        "radius:0.8,"
        "fx:0.5, fy:0.5,"
        "stop:0 #5d39c9,"
        "stop:1 #24104f);"
        "border:2px solid #8c4dff;"
        "border-radius:16px;"
        "color:white;"
        "font-size:26px;"
        "font-weight:bold;"
        "padding:0px;"
        "}"
    );
    connect(nextBtn, &QPushButton::clicked, this, [this]() { refreshSelector(1); });
    layout->addWidget(nextBtn);
}

////////////////
// Aggiornamento selettore
////////////////

void DaySelectorWidget::refreshSelector(int step) {

    current = current.addDays(step);
    updateDayLabels();
    emit dateChanged(current);
}

void DaySelectorWidget::goToDate(const QDate& date) {

    current = date;
    updateDayLabels();
    emit dateChanged(current);
}

////////////////
// Aggiornamento etichette
////////////////

void DaySelectorWidget::updateDayLabels() {

    for (int i = 0; i < DAYS_COUNT; ++i) {
        
        QDate d = current.addDays(i + START_OFFSET);
        days[i]->setText(QStringLiteral(
            "<span style='color:#A5B4FC;'>%1</span><br>"
            "<span style='color:white; font-size:14pt; font-weight:700;'>%2</span><br>"
            "<span style='color:rgba(255,255,255,120);'>%3</span>"
        ).arg(d.toString("ddd"))
         .arg(d.toString("dd"))
         .arg(d.toString("MMM")));
    }
}

////////////////
// Getter
////////////////

QDate DaySelectorWidget::currentDate() const{
    
    return current;
}