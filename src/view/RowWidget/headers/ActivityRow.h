#ifndef ACTIVITY_ROW_H
#define ACTIVITY_ROW_H

#include "Activity.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QUuid>

////////////////
// ActivityRow (riga base per visualizzazione attività)
////////////////

class ActivityRow : public QWidget {
    Q_OBJECT

private:

    // Metodi privati
    void setupUI();
    void setupConnections();

    QPixmap colorSvgIcon(const QString& path, const QString& color);

    // Widget interni
    QLabel* header;
    QWidget* content;
    QLabel* complete;
    QPushButton* expand;
    QVBoxLayout* box;

    // Pulsanti azione (lazy initialization)
    QPushButton* del = nullptr;
    QPushButton* modify = nullptr;

protected:

    Activity* act;

    // Metodi protetti per classi derivate
    void addContent(QWidget* content);
    void closeContent();
    void markCompleted();

    QPushButton* getDeleteButton();
    QPushButton* getModifyButton();

public:

    ActivityRow(Activity* activity, QWidget* parent = nullptr);
    virtual Activity* getActivity() const;

signals:

    void remove(const QUuid& id);
    void edit(const QUuid& id);
    void contentToggled();
};

#endif