#ifndef SUB_TASK_ENTRY_H
#define SUB_TASK_ENTRY_H

#include "Activity.h"
#include "ActivityUtilities.h"

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>

////////////////
// SubTaskEntry
////////////////

class SubTaskEntry : public QWidget {
    Q_OBJECT

private:

    Activity* editable;      // Attività associata (nullptr = nuova)
    QLineEdit* TitleField;
    QTextEdit* DescField;
    QUuid id;                // ID dell'attività (vuoto se nuova)

public:

    SubTaskEntry(Activity* act = nullptr, QWidget* parent = nullptr);
    SubTaskData collectData() const;
};

#endif