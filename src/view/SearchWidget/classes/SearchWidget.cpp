#include "SearchWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

const QDate SearchWidget::SENTINEL = QDate(2000, 1, 1);

////////////////
// Costruttore
////////////////

SearchWidget::SearchWidget(QWidget* parent) : QWidget(parent) {
    
    setupUI();
    setupConnections();
}

////////////////
// Setup UI
////////////////

void SearchWidget::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QWidget* mainContent = new QWidget();
    mainContent->setObjectName("mainContent");
    mainContent->setContentsMargins(0, 0, 0, 0);
    mainContent->setMinimumWidth(480);

    QVBoxLayout* contentLayout = new QVBoxLayout(mainContent);
    mainContent->setStyleSheet(
        "#mainContent {"
        "   padding: 8px 12px;"
        "   border: 1px solid rgba(59,130,246,80);"
        "   border-radius: 6px;"
        "   background-color: rgba(255,255,255,10);"
        "}"
        "#mainContent QWidget { background-color: transparent; }"
        "#mainContent QLabel { color: rgba(255,255,255,150); }"
        "#mainContent QLineEdit,"
        "#mainContent QComboBox {"
        "   background-color: #171A21;"
        "   color: white;"
        "   border: 1px solid #3A3F4B;"
        "   border-radius: 8px;"
        "   padding: 6px 10px;"
        "}"
        "#mainContent QLineEdit:focus,"
        "#mainContent QComboBox:focus { border: 1px solid #8B5CF6; }"
        "#mainContent QDateEdit {"
        "   background-color: #171A21;"
        "   color: #F2F2F2;"
        "   border: 1px solid #3A3F4B;"
        "   border-radius: 8px;"
        "   padding-left: 12px;"
        "   padding-right: 0px;"
        "   min-height: 32px;"
        "}"
        "#mainContent QDateEdit:hover { border-color: #6B7280; }"
        "#mainContent QDateEdit:focus { border: 1px solid #8B5CF6; }"
        "#mainContent QDateEdit::up-button {"
        "   subcontrol-position: top right;"
        "   width: 20px;"
        "   height: 20px;"
        "   margin: 0px 10px -10px 0px;"
        "   background: transparent;"
        "}"
        "#mainContent QDateEdit::down-button {"
        "   subcontrol-position: bottom right;"
        "   width: 20px;"
        "   height: 20px;"
        "   margin: -10px 10px 0px 0px;"
        "   background: transparent;"
        "}"
        "#mainContent QDateEdit::up-arrow {"
        "   image: url(:/Up.svg);"
        "   width: 15px;"
        "   height: 15px;"
        "}"
        "#mainContent QDateEdit::down-arrow {"
        "   image: url(:/Down.svg);"
        "   width: 15px;"
        "   height: 15px;"
        "}"
        "#mainContent QDateEdit:disabled {"
        "   background-color: #101318;"
        "   color: rgba(255,255,255,80);"
        "   border: 1px solid #2C313C;"
        "}"
        "#mainContent QDateEdit::up-button:disabled,"
        "#mainContent QDateEdit::down-button:disabled { background: transparent; }"
        "#mainContent QPushButton { text-align: left; margin: 0px; }"
        "#mainContent QComboBox::drop-down { border: none; }"
        "#mainContent QCheckBox {"
        "   spacing: 8px;"
        "   color: #E5E5E5;"
        "   background-color: transparent;"
        "}"
        "QCheckBox::indicator {"
        "   width: 17px;"
        "   height: 17px;"
        "   border-radius: 5px;"
        "   border: 1px solid #555B68;"
        "   background-color: #171A21;"
        "}"
        "QCheckBox::indicator:hover { border-color: #8B5CF6; }"
        "QCheckBox::indicator:checked { background: #8B5CF6; border-color: #8B5CF6; }"
    );

    // Barra di ricerca (pulsante)
    QHBoxLayout* searchLayout = new QHBoxLayout();
    QPushButton* searchBarBtn = new QPushButton("Cerca attività...");
    searchBarBtn->setMinimumWidth(150);
    searchBarBtn->setIcon(QIcon(":/Search.svg"));
    searchBarBtn->setIconSize(QSize(18, 18));

    searchLayout->addWidget(searchBarBtn);

    exclusiveCheckbox = new QCheckBox("Filtri Esclusivi");
    exclusiveCheckbox->setFixedWidth(100);
    exclusiveCheckbox->hide();

    searchLayout->addWidget(exclusiveCheckbox);
    contentLayout->addLayout(searchLayout);

    // Contenitore dei filtri (inizialmente nascosto)
    content = new QWidget();
    QVBoxLayout* filterLayout = new QVBoxLayout(content);
    filterLayout->setSpacing(20);

    // Titolo
    QHBoxLayout* titleLayout = new QHBoxLayout();
    QLabel* titleLabel = new QLabel("Titolo");
    titleField = new QLineEdit();
    titleField->setPlaceholderText("Titolo attività...");
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(titleField);
    filterLayout->addLayout(titleLayout);

    // Categoria
    QHBoxLayout* categoryLayout = new QHBoxLayout();
    QLabel* categoryIcon = new QLabel();
    categoryIcon->setPixmap(QIcon(":/Category.svg").pixmap(16, 16));
    categoryIcon->setFixedSize(18, 18);

    QLabel* categoryLabel = new QLabel("Categoria");
    categoryLabel->setMaximumWidth(65);

    categoryCombo = new QComboBox();
    categoryCombo->addItem("Tutte le categorie", -1);
    categoryCombo->addItem("Event", static_cast<int>(Activity::ActivityCategory::Event));
    categoryCombo->addItem("Appointment", static_cast<int>(Activity::ActivityCategory::Appointment));
    categoryCombo->addItem("Simple Task", static_cast<int>(Activity::ActivityCategory::SimpleTask));
    categoryCombo->addItem("Composite Task", static_cast<int>(Activity::ActivityCategory::CompositeTask));

    categoryLayout->addWidget(categoryIcon);
    categoryLayout->addWidget(categoryLabel);
    categoryLayout->addWidget(categoryCombo);
    filterLayout->addLayout(categoryLayout);

    // Date
    QHBoxLayout* dateLayout = new QHBoxLayout();

    QLabel* dateIcon = new QLabel();
    dateIcon->setPixmap(QIcon(":/Date.svg").pixmap(16, 16));
    dateIcon->setFixedSize(18, 18);

    QVBoxLayout* datesStack = new QVBoxLayout();

    // Data inizio
    QHBoxLayout* startRow = new QHBoxLayout();
    QLabel* startLabel = new QLabel("Dal");
    startDateField = new QDateEdit();
    startDateField->setMinimumDate(SENTINEL);
    startDateField->setDate(SENTINEL);
    startRow->addWidget(startLabel);
    startRow->addStretch();
    startRow->addWidget(startDateField);
    datesStack->addLayout(startRow);

    // Data fine
    QHBoxLayout* endRow = new QHBoxLayout();
    QLabel* endLabel = new QLabel("Al");
    endDateField = new QDateEdit();
    endDateField->setMinimumDate(SENTINEL);
    endDateField->setDate(SENTINEL);
    endRow->addWidget(endLabel);
    endRow->addStretch();
    endRow->addWidget(endDateField);
    datesStack->addLayout(endRow);

    dateLayout->addWidget(dateIcon, 0, Qt::AlignVCenter);
    dateLayout->addLayout(datesStack);
    dateLayout->addStretch();

    filterLayout->addLayout(dateLayout);

    contentLayout->addWidget(content);
    mainLayout->addWidget(mainContent);

    // All'inizio i filtri sono nascosti
    content->hide();
}

////////////////
// Setup connessioni
////////////////

void SearchWidget::setupConnections()
{
    // Pulsante di apertura/chiusura pannello
    QPushButton* searchBarBtn = findChild<QPushButton*>();
    if (searchBarBtn) {
        
        connect(searchBarBtn, &QPushButton::clicked, this, [this]() {
            
            bool isVisible = content->isVisible();
            content->setVisible(!isVisible);
            exclusiveCheckbox->setVisible(!isVisible);
        });
    }

    // Checkbox "Filtri Esclusivi"
    connect(exclusiveCheckbox, &QCheckBox::toggled, this, [this]() {
        
        clearAllExcept(nullptr);
        emit criteriaChanged(collectCriteria());
    });

    // Campo titolo
    connect(titleField, &QLineEdit::textChanged, this, [this](const QString& text) {
        
        if (exclusiveCheckbox->isChecked() && !text.isEmpty()) {
            
            clearAllExcept(titleField);
        }
        emit criteriaChanged(collectCriteria());
    });

    // Combo categoria
    connect(categoryCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index) {
        
        if (exclusiveCheckbox->isChecked() && index != 0) {
            
            clearAllExcept(categoryCombo);
        }

        int catValue = categoryCombo->currentData().toInt();
        bool isTaskCategory = (catValue == static_cast<int>(Activity::ActivityCategory::SimpleTask) ||
                               catValue == static_cast<int>(Activity::ActivityCategory::CompositeTask));

        startDateField->setEnabled(!isTaskCategory);
        endDateField->setEnabled(!isTaskCategory);

        if (isTaskCategory) {
            
            startDateField->setDate(SENTINEL);
            endDateField->setDate(SENTINEL);
        }

        emit criteriaChanged(collectCriteria());
    });

    // Data inizio
    connect(startDateField, &QDateEdit::dateChanged, this, [this](const QDate& d) {
        
        if (exclusiveCheckbox->isChecked() && d != SENTINEL) {
            
            clearAllExcept(startDateField);
        }
        emit criteriaChanged(collectCriteria());
    });

    // Data fine
    connect(endDateField, &QDateEdit::dateChanged, this, [this](const QDate& d) {
        
        if (exclusiveCheckbox->isChecked() && d != SENTINEL) {
            
            clearAllExcept(endDateField);
        }
        emit criteriaChanged(collectCriteria());
    });
}

////////////////
// Clear di tutti i campi (tranne except)
////////////////

void SearchWidget::clearAllExcept(QWidget* except)
{
    if (titleField != except) { titleField->clear(); }
    if (categoryCombo != except) { categoryCombo->setCurrentIndex(0); }
    if (startDateField != except) { startDateField->setDate(SENTINEL); }
    if (endDateField != except) { endDateField->setDate(SENTINEL); }
}

////////////////
// Raccolta criteri di ricerca
////////////////

SearchCriteria SearchWidget::collectCriteria() const {
    
    SearchCriteria c;
    c.title = titleField->text();

    if (categoryCombo->currentIndex() != 0) {
        c.hasCategory = true;
        c.category = static_cast<Activity::ActivityCategory>(categoryCombo->currentData().toInt());
    }

    if (startDateField->date() != SENTINEL) {
        c.hasStartDate = true;
        c.startDate = startDateField->date();
    }

    if (endDateField->date() != SENTINEL) {
        c.hasEndDate = true;
        c.endDate = endDateField->date();
    }

    return c;
}

////////////////
// Apri pannello e metti focus sul titolo
////////////////

void SearchWidget::openPanel() {
    
    content->setVisible(true);
    exclusiveCheckbox->setVisible(true);
    titleField->setFocus();
}