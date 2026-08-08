#ifndef ACTIVITY_FILTER_H
#define ACTIVITY_FILTER_H

#include "Activity.h"

////////////////
// ActivityFilter (interfaccia)
////////////////

class ActivityFilter {
public:
    virtual ~ActivityFilter() = default;
    virtual bool matches(const Activity* activity) const = 0;
};

#endif