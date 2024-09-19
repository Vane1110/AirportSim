#ifndef ENTITIES_H
#define ENTITIES_H

#include <string>

class Flight {
public:
    Flight(const std::string& dest, int earn);
    std::string destination;
    int earnings;
};

class Airplane {
public:
    Airplane(const std::string& n, double mult, double c);
    std::string name;
    double earnings_multiplier;
    double cost;
    bool repairPending;
};

class Manager {
public:
    Manager(const std::string& n, double ch, double p);
    std::string name;
    double chance;
    double payment;
};

#endif // ENTITIES_H