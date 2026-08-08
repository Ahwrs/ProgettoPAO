#ifndef TASK_ROW_H
#define TASK_ROW_H

#include "ActivityRow.h"
#include "CompositeTask.h"
#include "SimpleTask.h"

#include <QProgressBar>

////////////////
// TaskRow (riga per visualizzazione Task)
////////////////

class TaskRow : public ActivityRow {
    Q_OBJECT

private:
    CompositeTask* prtComposite;   // CompositeTask padre (nullptr se è una task normale)

public:

    // Costruttori
    TaskRow(SimpleTask* st, CompositeTask* parentComposite = nullptr, QWidget* parent = nullptr);
    TaskRow(CompositeTask* task, QWidget* parent = nullptr);

signals:
    void completeReq(const QUuid& id);
};

#endif