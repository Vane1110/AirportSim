
#ifndef AIRPORT_H
#define AIRPORT_H

#include <ostream>
#include "JustDays.h"
#include "Entities.h"
#include "Runway.h"
#include <string>
#include <vector>
#include <ostream>
#include <iostream>
class Airport: public JustDay{
public:
    Airport(const std::string& name);

    void buyAirplane();
    void buyRunway();
    void hireManager();
    void startFlight();
    void displayStatus();
    void nextDay();
    void bindAirplaneToRunway();
    void saveScore();
    void displayScoreboard();
    int flightCounter;


    friend std::ostream& operator<<(std::ostream& os, const Airport& airport);

private:
    void manageRunways();
    void checkAndRepairAirplanes();
    void payManagers();
    void incrementDayCounter();

    std::string name;
    double money;
    int day;
    int daysToNextCheck;
    std::vector<Airplane> airplanes;
    std::vector<Runway> runways;
    std::vector<Flight> flights;
    std::vector<Manager> managerPool;
    std::vector<Airplane> airplanePool;
};

inline std::ostream& operator<<(std::ostream& os, const Airport& airport) {
    os << "Airport Name: " << airport.name << std::endl;
    os << "Money: " << airport.money << std::endl;
    os << "Day: " << airport.day << std::endl;
    os << "Days to Next Check: " << airport.daysToNextCheck << std::endl;
    os << "Number of Airplanes: " << airport.airplanes.size() << std::endl;
    os << "Number of Runways: " << airport.runways.size() << std::endl;
    os << "Number of Flights: " << airport.flights.size() << std::endl;
    os << "Number of Managers: " << airport.managerPool.size() << std::endl;
    return os;
}

#endif // AIRPORT_H
