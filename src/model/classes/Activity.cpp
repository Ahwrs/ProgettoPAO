#include "../headers/Activity.h"
#include <QRandomGenerator>

    

Activity::Activity(const QString& t, const QString& d) : ID(QRandomGenerator::global()->bounded(0, INT_MAX)), title(t), description(d) {}
Activity::~Activity() {}

QString Activity::getTitle() const { return title; }
QString Activity::getDescription() const { return description; }