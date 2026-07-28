#include "ActivityRow.h"
#include "ActivityUtilities.h"

ActivityRow::ActivityRow(Activity* a, QWidget* p) : QWidget(p), act(a), content(nullptr) {
    
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(categoryStyle(act->getCategory()));

    box = new QVBoxLayout(this);

    header = new QLabel();
    header->setText(a->getTitle());

    expand = new QPushButton();
    expand->setIcon(QIcon(":/Right.svg"));
    expand->setIconSize(QSize(18, 18));
    expand->setFixedSize(20, 20);
    connect(expand, &QPushButton::clicked, this, [this] {
        
        if (!content) return;
        bool isVisible = content->isVisible();
        content->setVisible(!isVisible);
        expand->setIcon(QIcon(isVisible ? ":/Right.svg" : ":/Down.svg"));
    });

    del = new QPushButton("Elimina");
    del->setIcon(QIcon(":/Trash.svg"));
    del->setIconSize(QSize(18, 18));
    del->setStyleSheet(
        "QPushButton {"
        "   border: 2px solid #D32F2F;"
        "   border-radius: 6px;"
        "   padding: 5px 10px;"
        "   color: #D32F2F;"
        "   background-color: transparent;"
        "}"
        "QPushButton:pressed {"
        "   border: 2px solid red;"
        "   background-color: rgba(255, 255, 255, 25);"
        "}"
    );

    connect(del, &QPushButton::clicked, this, [this] {
        QString msg = "Procedendo si eliminerà l'attività definitivamente. Continuare?";
        if (QMessageBox::question(this, "Attenzione", msg) == QMessageBox::Yes) {
            emit remove(act->getID());
        }
    });

    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->addWidget(header);
    headerLayout->addStretch();
    headerLayout->addWidget(expand);
    box->addLayout(headerLayout);
}

void ActivityRow::addContent(QWidget* c) {

    content = c;
    content->hide();
    box->addWidget(content);
}

void ActivityRow::closeContent() {
    
    if (content) {
        content->hide();
        expand->setIcon(QIcon(":/Right.svg"));
    }
}