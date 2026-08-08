#include "MainWindow.h"
#include "DayViewWidget.h"
#include <QMenuBar>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {

    setMinimumSize(500, 600);
    setMaximumHeight(750);
    setStyleSheet("background-color: #070b0f; color: white;");

    // --- Menu ---
    QMenu* fileMenu = menuBar()->addMenu(QIcon(":/File.svg"), " File"); 
    fileMenu->setAttribute(Qt::WA_TranslucentBackground);
    menuBar()->setNativeMenuBar(false);

    workingFile = new QLabel("File corrente: Nessun file");
    menuBar()->setCornerWidget(workingFile, Qt::TopRightCorner);
    
    openAction = fileMenu->addAction("Apri file di lavoro...");
    connect(openAction, &QAction::triggered, this, [this]{ emit openWorkingFileRequested(); });

    QAction* saveAction = fileMenu->addAction("Salva...");
    connect(saveAction, &QAction::triggered, this, [this]{ emit saveRequested(); });

    setupShortcuts();

    menuBar()->setStyleSheet(
    "QMenuBar {"
    "   background-color: transparent;"
    "   spacing: 6px;"
    "   padding: 4px 8px;"
    "}"
    "QMenuBar::item {"
    "   background-color: transparent;"
    "   color: rgba(160,160,160,255);"
    "   border: 1px solid rgba(150,150,150,255);"
    "   border-radius: 6px;"
    "   padding: 4px 14px;"
    "}"
    "QMenuBar::item:selected {"
    "   background-color: rgba(255,255,255,12);"
    "   border-color: rgba(200,200,200,220);"
    "}"

    "QMenu {"
    "   background-color: rgb(15,17,21);"
    "   border: 1px solid rgba(150,150,150,200);"  
    "   border-radius: 8px;"
    "   padding: 4px;"
    "}"
    "QMenu::item {"
    "   background-color: transparent;"
    "   color: rgba(160,160,160,255);"
    "   padding: 6px 20px;"
    "   border: none;"                             
    "   border-radius: 4px;"
    "}"
    "QMenu::item:selected {"
    "   background-color: rgba(255,255,255,15);"
    "   color: white;"
    "}"

    "QLabel {"
    "   background-color: transparent;"
    "   border: 1px solid rgba(150,150,150,200);"
    "   border-radius: 6px;"
    "   spacing: 6px;"
    "   padding: 4px 8px;"
    "}"
);

    // --- Stack ---
    stack = new QStackedWidget();
    dayView = new DayViewWidget();
    stack->addWidget(dayView);
    stack->setCurrentIndex(0);

    setCentralWidget(stack);
}

DayViewWidget* MainWindow::getDayView() const {
    return dayView;
}

void MainWindow::showForm(QWidget* form) {

    formPage = form;
    stack->addWidget(formPage);
    stack->setCurrentWidget(formPage);
}

void MainWindow::showDayView() {

    stack->setCurrentWidget(dayView);
    if (formPage) {
        
        stack->removeWidget(formPage);
        formPage->deleteLater();
        formPage = nullptr;
    }
}

void MainWindow::closeEvent(QCloseEvent* event) {

    emit closing();
    QMainWindow::closeEvent(event);
}

void MainWindow::setCurrentFile(const QString& file){

    workingFile->setText("File corrente: " + file);
}

void MainWindow::setupShortcuts(){

    // CTRL + N -- Nuova attività
    QAction* newAction = new QAction(this);
    newAction->setShortcut(QKeySequence("Ctrl+N"));
    addAction(newAction);
    connect(newAction, &QAction::triggered, this, [this]{
        dayView->newActivityRequested();   
    });

    // CTRL + L -- Load Manuale
    openAction->setShortcut(QKeySequence("Ctrl+L"));

    // CTRL + D -- Data corrente
    QAction* todayAct = new QAction(this);
    todayAct->setShortcut(QKeySequence("Ctrl+D"));
    addAction(todayAct);
    connect(todayAct, &QAction::triggered, this, [this]{
        dayView->goToToday();   
    });

    // CTRL + R - Ricerca
    QAction* searchAct = new QAction(this);
    searchAct->setShortcut(QKeySequence("Ctrl+R"));
    addAction(searchAct);
    connect(searchAct, &QAction::triggered, this, [this]{ 
        dayView->focusSearch(); 
    });

    // CTRL + S -- Salva 
    QAction* saveAct = new QAction(this);
    saveAct->setShortcut(QKeySequence("Ctrl+S"));
    addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, [this]{ emit saveShortcut(); });

    // CTRL + SHIFT + S -- Salva con nome
    QAction* saveAsAct = new QAction(this);
    saveAsAct->setShortcut(QKeySequence("Ctrl+Shift+S"));
    addAction(saveAsAct);
    connect(saveAsAct, &QAction::triggered, this, [this]{ emit saveAsShortcut(); });

}