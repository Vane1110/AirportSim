#include "Entities.h"

Flight::Flight(const std::string& dest, int earn) : destination(dest), earnings(earn) {}

Airplane::Airplane(const std::string& n, double mult, double c)
        : name(n), earnings_multiplier(mult), cost(c), repairPending(false) {}

Manager::Manager(const std::string& n, double ch, double p)
        : name(n), chance(ch), payment(p) {}