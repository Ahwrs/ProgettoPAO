#ifndef ACTIVITY_FORM_H
#define ACTIVITY_FORM_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QVBoxLayout>
#include "ActivityUtilities.h"

class Activity;

class ActivityForm : public QWidget {
    Q_OBJECT

private:

    Activity* editable;

    QLineEdit* TitleField;
    QTextEdit* DescField;
    QCheckBox* isAllDay;

    QDateEdit* DateField;
    QTimeEdit* StartField;
    QTimeEdit* EndField;
    QLineEdit* LinkField;
    QCheckBox* isOnlineField;

    QVBoxLayout* SubTasks;   

    ActivityData collectData() const;

public:
    
    ActivityForm(Activity* toEdit = nullptr, QWidget* parent = nullptr);

signals:
    
    void submitCreate(const ActivityData& data);
    void submitEdit(const QUuid& id, const ActivityData& data);
    void cancelled();

};

#endif