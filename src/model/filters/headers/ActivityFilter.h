#ifndef ACTIVITY_FILTER_H
#define ACTIVITY_FILTER_H

#include "Activity.h"

class ActivityFilter {
public:
    virtual ~ActivityFilter() = default;
    virtual bool matches(const Activity* activity) const = 0;
};

#endif