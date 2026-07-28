#ifndef ACTIVITY_ROW__H
#define ACTIVITY_ROW__H

#include "Activity.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QStyle>

class ActivityRow : public QWidget{
    Q_OBJECT
    
private:
    QLabel* header;
    QWidget* content;
    QPushButton* expand;
    QVBoxLayout* box;

protected:
    Activity* act;
    QPushButton* del;
    void addContent(QWidget* c);
    void closeContent();

public:

    ActivityRow(Activity* activity, QWidget* parent = nullptr);

signals:

    void remove(const QUuid& idx);

};

#endif