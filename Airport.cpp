#include "Airport.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>

// rewrite manager pool and airplanepool
Airport::Airport(const std::string& n) : name(n), money(1000), day(1), daysToNextCheck(10), flightCounter(0) {
    runways.push_back(Runway(1));
    // Initialize manager pool with random managers
    managerPool.push_back(Manager("Alice", 0.9, 200));
    managerPool.push_back(Manager("Bob", 0.75, 150));
    managerPool.push_back(Manager("Charlie", 0.6, 100));
    managerPool.push_back(Manager("Diana", 0.85, 180));
    managerPool.push_back(Manager("Eve", 0.5, 80));

    // Initialize airplane pool with random airplanes
    airplanePool.push_back(Airplane("Boeing 747", 1.5, 500));
    airplanePool.push_back(Airplane("Airbus A320", 1.2, 300));
    airplanePool.push_back(Airplane("Cessna 172", 0.8, 100));
    airplanePool.push_back(Airplane("Gulfstream G650", 2.0, 800));
    airplanePool.push_back(Airplane("Bombardier CRJ200", 1.0, 200));
}

void Airport::buyAirplane() {
    int airplane_index;

    std::cout << "\nAvailable airplanes:\n";
    for (size_t i = 0; i < airplanePool.size(); ++i) {
        std::cout << i + 1 << ". " << airplanePool[i].name << " (Multiplier: " << airplanePool[i].earnings_multiplier
                  << ", Cost: " << airplanePool[i].cost << ")\n";
    }
    std::cout << "Enter airplane index to buy: ";
    std::cin >> airplane_index;

    if (airplane_index > 0 && airplane_index <= airplanePool.size()) {
        Airplane selectedAirplane = airplanePool[airplane_index - 1];
        if (money >= selectedAirplane.cost) {
            money -= selectedAirplane.cost;
            airplanes.push_back(selectedAirplane);
            std::cout << "Airplane " << selectedAirplane.name << " bought successfully.\n";
            system("CLS");
        } else {
            std::cout << "Not enough money to buy this airplane.\n";
            system("CLS");
        }
    } else {
        std::cout << "Invalid airplane index.\n";
        system("CLS");
    }
}

void Airport::buyRunway() {
    runways.push_back(Runway(runways.size() + 1));
    std::cout << "Runway " << runways.size() << " bought successfully.\n";
}

void Airport::hireManager() {
    int manager_index;
    int runway_id;

    std::cout << "\nAvailable managers:\n";
    for (size_t i = 0; i < managerPool.size(); ++i) {
        std::cout << i + 1 << ". " << managerPool[i].name << " (Chance: " << managerPool[i].chance
                  << ", Payment: " << managerPool[i].payment << ")\n";
    }
    std::cout << "Enter manager index to hire: ";
    std::cin >> manager_index;

    std::cout << "Enter runway ID to assign manager to: ";
    std::cin >> runway_id;

    if (manager_index > 0 && manager_index <= managerPool.size() &&
        runway_id > 0 && runway_id <= runways.size() && runways[runway_id - 1].manager == nullptr) {

        runways[runway_id - 1].manager = new Manager(managerPool[manager_index - 1]);
        std::cout << "Manager " << managerPool[manager_index - 1].name << " hired and assigned to runway " << runway_id << ".\n";
        managerPool.erase(managerPool.begin() + manager_index - 1);
        system("CLS");
    } else {
        std::cout << "Invalid manager index or runway ID, or runway already has a manager.\n";
        system("CLS");
    }
}

void Airport::startFlight() {
    std::vector<std::string> destinations = {"NYC", "LAX", "ORD", "DFW", "DEN","JFK","ATL","HND"};
    flights.clear();
    for (int i = 0; i < 8; ++i) {
        int earnings = rand() % 401 + 100;
        flights.push_back(Flight(destinations[rand() % destinations.size()], earnings));
    }
    flightCounter++;

    std::cout << "\nAvailable flights:\n";
    for (size_t i = 0; i < flights.size(); ++i) {
        std::cout << i + 1 << ". To " << flights[i].destination << ", Earnings: " << flights[i].earnings << "\n";
    }
    std::cout << "6. Exit\n";

    std::cout << "\nAvailable runways:\n";
    for (size_t i = 0; i < runways.size(); ++i) {
        std::cout << "Runway " << runways[i].id;
        if (runways[i].manager != nullptr) {
            std::cout << " (Managed by " << runways[i].manager->name << ")";
        }
        if (runways[i].airplane != nullptr) {
            std::cout << " (Airplane: " << runways[i].airplane->name << ")";
        }
        if (runways[i].usedToday) {
            std::cout << " [Used today]";
        }
        std::cout << "\n";
    }
    std::cout << "0. Exit\n";

    int runway_id, flight_index;
    std::cout << "Enter runway ID (or 0 to exit): ";
    std::cin >> runway_id;
    if (runway_id == 0) {
        return;
    }

    std::cout << "Enter flight index (or 6 to exit): ";
    std::cin >> flight_index;
    if (flight_index == 6) {
        return;
    }

    if (runway_id > 0 && runway_id <= runways.size() && flight_index > 0 && flight_index <= flights.size() && !runways[runway_id - 1].usedToday) {
        Flight* flight = &flights[flight_index - 1];
        if (runways[runway_id - 1].manager != nullptr) {
            std::cout << "Manager handling flight to " << flight->destination << "\n";
        } else {
            system("CLS");
            std::cout << "Flight to " << flight->destination << " started manually.\n \n";
        }
        double earnings = flight->earnings;
        if (runways[runway_id - 1].airplane != nullptr) {
            earnings *= runways[runway_id - 1].airplane->earnings_multiplier;
        }
        money += earnings;
        std::cout << "Current money: " << money << "\n";
        runways[runway_id - 1].usedToday = true;
    } else {
        system("CLS");
        std::cout << "Invalid runway ID, flight index, or runway has already been used today.\n \n";
    }
}

void Airport::displayStatus() {
    std::cout << "Airport: " << name << "\n";
    std::cout << "Money: " << money << "\n";
    std::cout << "Number of airplanes: " << airplanes.size() << "\n";
    std::cout << "Number of runways: " << runways.size() << "\n";
    std::cout << "Day: " << day << "\n";
    std::cout << "Days to next airplane check: " << daysToNextCheck << "\n";
}

void Airport::nextDay() {
    manageRunways();
    payManagers();
    incrementDayCounter();
    day++;
    system("CLS");;

    for (Runway& runway : runways) {
        runway.usedToday = false;
    }

    std::cout << "\n--- Day " << day << " ---\n";
}

void Airport::incrementDayCounter() {
    daysToNextCheck--;

    if (daysToNextCheck == 0) {
        daysToNextCheck = 10;
        checkAndRepairAirplanes();
    }
}

void Airport::manageRunways() {
    for (Runway& runway : runways) {
        if (runway.manager != nullptr) {
            std::vector<std::string> destinations = {"NYC", "LAX", "ORD", "DFW", "DEN"};
            flights.clear();
            for (int i = 0; i < 5; ++i) {
                int earnings = rand() % 401 + 100;
                flights.push_back(Flight(destinations[rand() % destinations.size()], earnings));
            }
            Flight* best_flight = nullptr;
            for (Flight& flight : flights) {
                if (best_flight == nullptr || flight.earnings > best_flight->earnings) {
                    best_flight = &flight;
                }
            }
            if (best_flight != nullptr && !runway.usedToday) {
                double earnings = best_flight->earnings;
                if (runway.airplane != nullptr) {
                    earnings *= runway.airplane->earnings_multiplier;
                }
                std::cout << "Manager " << runway.manager->name << " chose flight to " << best_flight->destination
                          << " with earnings " << earnings << "\n";
                money += earnings;
                runway.usedToday = true;
            }
        }
    }
}

void Airport::payManagers() {
    for (Runway& runway : runways) {
        if (runway.manager != nullptr) {
            if (money >= runway.manager->payment) {
                money -= runway.manager->payment;
                std::cout << "Paid " << runway.manager->name << " $" << runway.manager->payment << " for managing.\n";
            } else {
                std::cout << "Not enough money to pay manager " << runway.manager->name << ".\n";
                delete runway.manager;
                runway.manager = nullptr;
            }
        }
    }
}

void Airport::checkAndRepairAirplanes() {
    for (Airplane& airplane : airplanes) {
        if (airplane.repairPending) {
            std::cout << "Airplane " << airplane.name << " is pending repair and is unavailable.\n";
            continue;
        }
        double check_cost = airplane.cost * 0.05;
        double repair_cost = airplane.cost * 0.3;
        if (money >= check_cost) {
            money -= check_cost;
            std::cout << "Airplane " << airplane.name << " checked for " << check_cost << ".\n";
            if (rand() % 10 == 0) {
                if (money >= repair_cost) {
                    money -= repair_cost;
                    airplane.repairPending = false;
                    std::cout << "Airplane " << airplane.name << " repaired for " << repair_cost << ".\n";
                } else {
                    std::cout << "Not enough money to repair airplane " << airplane.name << ".\n";
                    airplane.repairPending = true;
                }
            } else {
                std::cout << "Airplane " << airplane.name << " is in good condition.\n";
            }
        } else {
            std::cout << "Not enough money to check airplane " << airplane.name << ".\n";
            airplane.repairPending = true;
        }
    }
}

void Airport::bindAirplaneToRunway() {
    int airplane_index, runway_id;

    std::cout << "\nAvailable airplanes:\n";
    for (size_t i = 0; i < airplanes.size(); ++i) {
        std::cout << i + 1 << ". " << airplanes[i].name << " (Multiplier: " << airplanes[i].earnings_multiplier << ")\n";
    }
    std::cout << "Enter airplane index to bind: ";
    std::cin >> airplane_index;

    std::cout << "Enter runway ID to bind airplane to: ";
    std::cin >> runway_id;

    if (airplane_index > 0 && airplane_index <= airplanes.size() && runway_id > 0 && runway_id <= runways.size()) {
        runways[runway_id - 1].airplane = &airplanes[airplane_index - 1];
        std::cout << "Airplane " << airplanes[airplane_index - 1].name << " bound to runway " << runway_id << ".\n";
        system("CLS");
    } else {
        system("CLS");
        std::cout << "Invalid airplane index or runway ID.\n \n";
    }
}
void Airport::saveScore() {
    std::ofstream outFile("scores.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << "Airport: " << name << ", Money: " << money << ", Day: " << day << std::endl;
        outFile.close();
        std::cout << "Score saved successfully.\n";
    } else {
        std::cout << "Unable to open file for saving score.\n";
    }
}
#include <fstream>
#include <sstream>

void Airport::displayScoreboard() {
    std::ifstream scoreFile("scores.txt");
    if (!scoreFile.is_open()) {
        std::cerr << "Failed to open score.txt\n";
        return;
    }

    int totalFlights = 0;
    int totalEarnings = 0;
    int flightCount = 0;
    std::string line;
    system("CLS");
    std::cout << "------------ Scoreboard ------------\n";
    while (std::getline(scoreFile, line)) {
        std::stringstream ss(line);
        std::string destination;
        int earnings;

        ss >> destination >> earnings;
        if (ss.fail()) {
            std::cerr << "Score: " << line << "\n";
            continue;
        }

        totalFlights++;
        totalEarnings += earnings;
    }
    scoreFile.close();

    flightCounter += totalFlights;

    std::cout << "Your Current Flights: " << totalFlights << "\n";
    std::cout << "------------------------------------\n";
}