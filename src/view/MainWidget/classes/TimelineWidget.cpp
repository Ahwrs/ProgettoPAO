#include "TimelineWidget.h"
#include "EventRow.h"
#include "Event.h"
#include "ActivityRow.h"

#include <QPainter>
#include <QResizeEvent>
#include <algorithm>
#include <unordered_map>

namespace {
    const int PIXELS_PER_MINUTE = 2;
    const int HOUR_COLUMN_WIDTH = 50;
}

////////////////
// Costruttore
////////////////

TimelineWidget::TimelineWidget(QWidget* parent) : QWidget(parent){

    setMinimumHeight(1440 * PIXELS_PER_MINUTE);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
}

////////////////
// Impostazione righe evento
////////////////

void TimelineWidget::setEventRows(const std::vector<ActivityRow*>& rows){

    // Rimuovi le vecchie righe
    for (EventRow* row : eventRows) {
        
        row->setParent(nullptr);
        row->deleteLater();
    }
    eventRows.clear();

    // Filtra solo EventRow e le aggiunge come figlie
    for (ActivityRow* row : rows) {
        
        if (auto* eventRow = dynamic_cast<EventRow*>(row)) {
            
            eventRow->setParent(this);
            eventRows.push_back(eventRow);
        }
    }
    repositionEvents();
}

////////////////
// Layout degli eventi (colonne)
////////////////

void TimelineWidget::repositionEvents(){

    if (eventRows.empty()) {
        
        update();
        return;
    }

    // Ordina per orario di inizio
    std::sort(eventRows.begin(), eventRows.end(), [](EventRow* a, EventRow* b) {
            return dynamic_cast<Event*>(a->getActivity())->getStartTime() <
                   dynamic_cast<Event*>(b->getActivity())->getStartTime();
    });

    // Algoritmo di layout a colonne per gestire sovrapposizioni tra eventi con orari simili (al minuto di differenza)
    std::unordered_map<EventRow*, int> columnOf;
    std::vector<int> colEndMin;

    for (auto* row : eventRows) {
        
        Event* ev = dynamic_cast<Event*>(row->getActivity());
        int start = ev->getStartTime().msecsSinceStartOfDay() / 60000;
        int end   = ev->getEndTime().msecsSinceStartOfDay() / 60000;

        int col = -1;
        for (int i = 0; i < (int)colEndMin.size(); ++i) {
            if (colEndMin[i] <= start) {
                
                col = i;
                break;
            }
        }
        if (col == -1) {
            
            col = colEndMin.size();
            colEndMin.push_back(0);
        }
        columnOf[row] = col;
        colEndMin[col] = end;
    }

    int maxCols = std::max(1, (int)colEndMin.size());
    int columnWidth = (this->width() - HOUR_COLUMN_WIDTH) / maxCols;

    // Posiziona ogni evento
    for (auto* row : eventRows) {
        
        Event* ev = dynamic_cast<Event*>(row->getActivity());
        int start = ev->getStartTime().msecsSinceStartOfDay() / 60000;
        int end   = ev->getEndTime().msecsSinceStartOfDay() / 60000;

        int naturalHeight = (end - start) * PIXELS_PER_MINUTE;
        int height = std::max(naturalHeight, row->minimumSizeHint().height());

        int x = HOUR_COLUMN_WIDTH + columnOf[row] * columnWidth;
        int y = start * PIXELS_PER_MINUTE + 20;

        row->setGeometry(x + 10, y, columnWidth - 10, height);
        row->show();
    }

    update();
}

////////////////
// Paint event (griglia + timeline)
////////////////

void TimelineWidget::paintEvent(QPaintEvent* event){

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    // Linea verticale delle ore
    painter.setPen(QPen(QColor(59, 130, 246, 100), 2));
    painter.drawLine(HOUR_COLUMN_WIDTH, 0, HOUR_COLUMN_WIDTH, height());

    // Griglia orizzontale e etichette orarie
    for (int minute = 0; minute < 1440; minute += 30) {

        bool isHour = (minute % 60 == 0);
        int y = minute * PIXELS_PER_MINUTE;

        // Linea orizzontale
        QColor lineColor(59, 130, 246, isHour ? 100 : 46);
        painter.setPen(QPen(lineColor, 1));
        painter.drawLine(0, y + 20, width(), y + 20);

        // Aggiunte estetiche per ogni ora (punto luminoso)
        if (isHour) {

            QPointF center(HOUR_COLUMN_WIDTH, y + 20);
            painter.setPen(Qt::NoPen);
            painter.setCompositionMode(QPainter::CompositionMode_Plus);

            // Bagliore ambientale 
            QRadialGradient ambientGlow(center, 40);
            ambientGlow.setColorAt(0.00, QColor(59, 130, 246, 35));
            ambientGlow.setColorAt(0.30, QColor(59, 130, 246, 12));
            ambientGlow.setColorAt(0.70, QColor(59, 130, 246, 3));
            ambientGlow.setColorAt(1.00, QColor(59, 130, 246, 0));
            painter.setBrush(ambientGlow);
            painter.drawEllipse(center, 40, 40);

            QRadialGradient intenseGlow(center, 14);
            intenseGlow.setColorAt(0.00, QColor(59, 130, 246, 160));
            intenseGlow.setColorAt(0.20, QColor(59, 130, 246, 90));
            intenseGlow.setColorAt(0.60, QColor(59, 130, 246, 25));
            intenseGlow.setColorAt(1.00, QColor(59, 130, 246, 0));
            painter.setBrush(intenseGlow);
            painter.drawEllipse(center, 14, 14);

            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setBrush(QColor(59, 130, 246));
            painter.drawEllipse(center, 3.5, 3.5);
        }

        // Testo dell'ora
        QString text = isHour
            ? QString("%1:00").arg(minute / 60, 2, 10, QChar('0'))
            : QString("%1:30").arg(minute / 60, 2, 10, QChar('0'));

        painter.setPen(QColor(255, 255, 255, isHour ? 160 : 90));
        QRect textRect(5, y, HOUR_COLUMN_WIDTH - 10, 20);
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
    }
}

////////////////
// Resize event
////////////////

void TimelineWidget::resizeEvent(QResizeEvent* event){
    
    QWidget::resizeEvent(event);
    repositionEvents();
}