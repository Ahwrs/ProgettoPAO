#include "DaySelectorWidget.h"
#include <QBoxLayout>

DaySelectorWidget::DaySelectorWidget(QWidget* parent) : QWidget(parent){

    QHBoxLayout* box = new QHBoxLayout(this);
    setMaximumHeight(80);
    current = QDate::currentDate();
    QDate temp;
    
    last = new QPushButton(this);
    last->setText(QString::fromUtf8("⮜"));
    last->setStyleSheet("font-size: 16pt;");
    connect(last, &QPushButton::clicked, this, [this]{ refreshSelector(-1);});
    box->addWidget(last);

    for(int i = 0, j = -2; i < 5; ++i, ++j){

        temp = current.addDays(j);
        days.push_back(new QLabel(this));
        days[i]->setText(QString("<b><span>"+temp.toString("ddd")+"</span><br><span style='font-size:16pt;'>%1</span></b>")
                        .arg(temp.toString("dd")));
        days[i]->setAlignment(Qt::AlignCenter);
        days[i]->setStyleSheet("border-radius: 8px; border: 1px solid #262526;");

        if(j == 0){days[i]->setStyleSheet("background-color: #7C3AED; color: white; border-radius: 8px;");}

        box->addWidget(days[i]);
    }

    next = new QPushButton(this);
    next->setText(QString::fromUtf8("⮞"));
    next->setStyleSheet("font-size: 16pt;");
    connect(next, &QPushButton::clicked, this, [this]{ refreshSelector(1);});
    box->addWidget(next);
    
}

void DaySelectorWidget::refreshSelector(int day){

    current = current.addDays(day);
    for(int i = 0, j = -2; i < 5; ++i, ++j){

        days[i]->setText(QString("%1<br><span style='font-size:16pt;'><b>%2</b></span>")
                        .arg(current.addDays(j).toString("ddd"))
                        .arg(current.addDays(j).toString("dd")));
    }
}