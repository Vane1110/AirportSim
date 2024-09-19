#include "Airport.h"
#include "Runway.h"
#include <iostream>
#include <fstream>
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::string airport_name;
    std::cout << "Enter your airport's 3-letter abbreviation: ";
    std::cin >> airport_name;

    Airport airport(airport_name);

    while (true) {
        airport.displayStatus();
        int choice;
        std::cout << "\n1. Start flight\n2. Buy airplane\n3. Buy runway\n4. Hire manager\n5. Bind airplane to rnway for\n6. Next day\n7. Save score & Exit\n";
        std::cout << "8. Display scoreboard\n";
        std::cout << "Choose an action: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                airport.startFlight();
                break;
            case 2:
                airport.buyAirplane();
                break;
            case 3:
                airport.buyRunway();
                break;
            case 4:
                airport.hireManager();
                break;
            case 5:
                airport.bindAirplaneToRunway();
                break;
            case 6:
                airport.nextDay();
                break;
            case 7:
                airport.saveScore();
                return 0;
            case 8:
                airport.displayScoreboard();
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}