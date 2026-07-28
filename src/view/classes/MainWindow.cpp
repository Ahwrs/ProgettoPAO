#include "MainWindow.h"
#include "DaySelectorWidget.h"
#include "ActivityRow.h"
#include "TaskRow.h"
#include "EventRow.h"

//Temporanei Forse
#include "Appointment.h"
#include "CompositeTask.h"
#include "SimpleTask.h"

#include <QBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QScrollArea>

MainWindow::MainWindow(ActivityManager* m) : manager(m) {

    setMinimumSize(500, 600);
    setStyleSheet("background-color: #070b0f; color: white;");

    stack = new QStackedWidget();

    DaySelectorWidget* selector = new DaySelectorWidget();

    // --- Event/Appointment: EventRow non esiste ancora, restano ActivityRow "nude" ---
    Event* e = new Event("Prova1", "Descrizione PR1", QDate::currentDate(),
            QTime::currentTime().addSecs(-1), QTime::currentTime().addSecs(1));
    Appointment* a = new Appointment("Prova2", "Descrizione PR2", QDate::currentDate(),
            QTime::currentTime().addSecs(-1), QTime::currentTime().addSecs(1), "maps.com", false);

    // --- SimpleTask isolata, non completata ---
    SimpleTask* isolata = new SimpleTask("Task isolata", "Prova descrizione");

    // --- SimpleTask isolata, GIA' completata: deve apparire subito disabilitata ---
    SimpleTask* isolataFatta = new SimpleTask("Task isolata (gia' completata)", "Prova", true);

    // --- CompositeTask con 3 sotto-task, una gia' completata ---
    CompositeTask* cp = new CompositeTask("Progetto di prova");
    cp->addTask(std::make_unique<SimpleTask>("Sub 1", "Descrizione sub 1", false));
    cp->addTask(std::make_unique<SimpleTask>("Sub 2 (gia' completata)", "Descrizione sub 2", true));
    cp->addTask(std::make_unique<SimpleTask>("Sub 3", "Descrizione sub 3", false));

    ActivityRow* rEvent = new EventRow(e);
    ActivityRow* rAppointment = new EventRow(a);
    TaskRow* rIsolata = new TaskRow(isolata);
    TaskRow* rIsolataFatta = new TaskRow(isolataFatta);
    TaskRow* rComposite = new TaskRow(cp);

    // collegamento provvisorio, solo per vedere che "remove" scatti con l'ID giusto
    connect(rIsolata, &ActivityRow::remove, this, [](const QUuid& id){
        qDebug() << "remove richiesto per:" << id;
    });
    connect(rComposite, &ActivityRow::remove, this, [](const QUuid& id){
        qDebug() << "remove richiesto per:" << id;
    });

    

    QWidget* acty = new QWidget();
    QVBoxLayout* ActivityLayout = new QVBoxLayout(acty);
    ActivityLayout->addWidget(rEvent);
    ActivityLayout->addWidget(rAppointment);
    ActivityLayout->addWidget(rIsolata);
    ActivityLayout->addWidget(rIsolataFatta);
    ActivityLayout->addWidget(rComposite);
    ActivityLayout->addStretch();
    
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(acty);
    scrollArea->setWidgetResizable(true);   
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    stack->addWidget(selector);
    stack->addWidget(scrollArea);   
    stack->setCurrentIndex(1);

    setCentralWidget(stack);
}