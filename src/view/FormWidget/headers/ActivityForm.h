#ifndef ACTIVITYFORM_H
#define ACTIVITYFORM_H

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

class ActivityForm : public QWidget{
    Q_OBJECT

private:

    ActivityData collectData() const;

    // Activity in modifica
    Activity* editable;

    //-----------------------------------
    // Campi comuni
    //-----------------------------------

    QLineEdit* TitleField;
    QTextEdit* DescField;

    // Se true mostra il pannello Task
    QCheckBox* isAllDay;

    //-----------------------------------
    // Pannello Event
    //-----------------------------------

    QWidget* EventWidget;

    QDateEdit* DateField;
    QTimeEdit* StartField;
    QTimeEdit* EndField;

    QLineEdit* LinkField;
    QCheckBox* isOnlineField;

    //-----------------------------------
    // Pannello Task
    //-----------------------------------

    QWidget* TaskWidget;
    QVBoxLayout* SubTasks;
   
public:
    
    ActivityForm(Activity* toEdit = nullptr, QWidget* parent = nullptr);

signals:
    void submitCreate(const ActivityData& data);
    void submitEdit(const QUuid& id, const ActivityData& data);
    void cancelled();
};

#endif // ACTIVITYFORM_H