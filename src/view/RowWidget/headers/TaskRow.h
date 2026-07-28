#ifndef TASK_ROW_H
#define TASK_ROW_H

#include "ActivityRow.h"
#include "CompositeTask.h"
#include "SimpleTask.h"
#include <QProgressBar>

class TaskRow : public ActivityRow {
    Q_OBJECT

    CompositeTask* prtComposite;

public:

    TaskRow(Activity* a, CompositeTask* prtComposite = nullptr, QWidget* parent = nullptr);

signals:

    void completeReq(const QUuid& id);
};

#endif