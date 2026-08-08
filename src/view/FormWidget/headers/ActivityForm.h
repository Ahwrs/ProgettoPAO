#ifndef ACTIVITY_FORM_H
#define ACTIVITY_FORM_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QBoxLayout>
#include <QLabel>

#include "ActivityUtilities.h"

class Activity;

////////////////
// ActivityForm
////////////////

class ActivityForm : public QWidget{
    Q_OBJECT

private:
    
    // Metodi di SetUp
    void setupUI();
    void setupConnections();
    void loadExistingData();
    QString styleSheetString() const;
    ActivityData collectData() const;

    // Dati in modifica (nullptr = nuova attività)
    Activity* editable;

    // Campi comuni
    QLineEdit* TitleField;
    QLabel* TitleLabel;
    QTextEdit* DescField;
    QLabel* DescLabel;
    QCheckBox* TaskMode;      // true = Task, false = Event

    // Pannello Event
    QWidget* EventPanel;
    QDateEdit* DateField;
    QTimeEdit* StartField;
    QTimeEdit* EndField;
    QLineEdit* LinkField;
    QCheckBox* OnlineCheck;

    // Pannello Task
    QWidget* TaskPanel;
    QVBoxLayout* SubTaskLayout;
    QPushButton* addSubBtn;
    QPushButton* removeSubBtn;

    // Pulsanti azione
    QPushButton* saveBtn;
    QPushButton* cancelBtn;

public:

    ActivityForm(Activity* toEdit = nullptr, QWidget* parent = nullptr);

signals:
    
    void submitCreate(const ActivityData& data);
    void submitEdit(const QUuid& id, const ActivityData& data);
    void cancelled();
};

#endif