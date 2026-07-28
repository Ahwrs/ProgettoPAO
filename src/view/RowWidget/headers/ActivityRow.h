#ifndef ACTIVITY_ROW_H
#define ACTIVITY_ROW_H

#include "Activity.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QUuid>

class ActivityRow : public QWidget {
    Q_OBJECT

private:
    QLabel* header;
    QWidget* content;
    QPushButton* expand;
    QVBoxLayout* box;

public:
    ActivityRow(Activity* activity, QWidget* parent = nullptr);

    protected:
    Activity* act;
    QPushButton* del;

    void addContent(QWidget* content);
    void closeContent();

signals:
    void remove(const QUuid& id);

};

#endif