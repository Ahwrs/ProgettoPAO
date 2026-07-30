#ifndef SUB_TASK_ENTRY_H
#define SUB_TASK_ENTRY_H

#include "Activity.h"
#include "ActivityUtilities.h"
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>

class SubTaskEntry : public QWidget {
    Q_OBJECT

private:

    Activity* editable;
    QLineEdit* TitleField;
    QTextEdit* DescField;
    QUuid id;

public:

    SubTaskEntry(Activity* act = nullptr, QWidget* parent = nullptr);
    SubTaskData collectData() const;

};

#endif