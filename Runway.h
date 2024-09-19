#ifndef RUNWAY_H
#define RUNWAY_H

#include "Entities.h"

class Runway {
public:
    Runway(int id);
    int id;
    Manager* manager;
    Airplane* airplane;
    bool usedToday;
};
#endif // RUNWAY_H