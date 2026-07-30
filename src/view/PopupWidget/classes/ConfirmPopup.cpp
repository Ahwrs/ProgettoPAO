#include "ConfirmPopup.h"
#include <QLabel>
#include <QPushButton>

ConfirmPopup::ConfirmPopup(const QString& msg, QWidget* parent) : PopupWidget(parent) {

    QWidget* content = new QWidget();
    QVBoxLayout* CLayout = new QVBoxLayout(content);

    QLabel* msgLabel = new QLabel(msg);
    CLayout->addWidget(msgLabel);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    QPushButton* yesBtn = new QPushButton("Conferma");
    QPushButton* noBtn = new QPushButton("Annulla");
    yesBtn->setObjectName("confirmBtn");
    noBtn->setObjectName("cancelBtn");

    connect(yesBtn, &QPushButton::clicked, this, [this]{ emit confirmed(); close(); });
    connect(noBtn, &QPushButton::clicked, this, [this]{ emit cancelled(); close(); });

    btnLayout->addWidget(noBtn);
    btnLayout->addWidget(yesBtn);
    CLayout->addLayout(btnLayout);

    addContent(content);
}