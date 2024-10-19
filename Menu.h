#ifndef PROJ_MENU_H
#define PROJ_MENU_H

#ifndef AED_PROJECT2_MENU_H
#define AED_PROJECT2_MENU_H

#include <iostream>
#include <limits>
#include <cmath>
#include <climits>
#include <vector>
#include "WaterSupply.h"
/**
 * @class Menu
 * @brief Provides an interface for user interaction with the WaterSupply system.
 *
 * The Menu class offers various functionalities through a console interface that allows users
 * to interact with and manipulate the WaterSupply system. It enables choosing data sets, viewing
 * and modifying the water supply network, and assessing its reliability and flow metrics.
 */
class Menu {
public:
    /**
     * Prompts the user to choose between a large or small data set for initializing the water supply system.
     * @param ws Pointer to the WaterSupply system to be initialized with the chosen data set.
     */
    void chooseDataSet(WaterSupply *ws);
    /**
    * Displays the main menu and handles user input for navigating through different functionalities.
    * @param ws An instance of the WaterSupply system for operations.
    */
    void mainMenu(WaterSupply ws);
private:
    /**
    * Displays the basic service metrics menu for viewing and analyzing flow data.
    * @param ws An instance of the WaterSupply system for retrieving flow information.
    */
    void basicMenu(WaterSupply ws);
    /**
     * Displays the reliability menu for simulating failures and their impacts on the network.
     * @param ws Reference to the WaterSupply system for performing reliability analysis.
     */
    void reliabilityMenu(WaterSupply &ws);
    /**
    * Displays the maximum flow menu for detailed flow analysis of cities.
    * @param ws An instance of the WaterSupply system for maximum flow operations.
    */
    void maxFlowMenu(WaterSupply ws);

    // Auxiliary functions for menu operations
    void chooseCity(WaterSupply ws);
    void chooseReservoir(WaterSupply ws);
    void chooseStation(WaterSupply ws);
    void choosePipeline(WaterSupply ws);

    void reservoirRemove(WaterSupply ws);
    void stationRemove(WaterSupply ws);
    void pipelineRemove(WaterSupply ws);
    /**
     * Handles invalid inputs by clearing the error state and discarding the input until a newline is found.
     * @param inputs A vector of valid input integers for guidance.
     * @param last The last valid integer input to guide the user.
     */
    void invalidInputHandler(std::vector<int> inputs, int last);
};

extern bool largeDataSet; ///< Global flag indicating if a large data set is chosen.

void Menu::chooseDataSet(WaterSupply *ws){
    std::cout << "Choose Data Set:" << std::endl <<
              "1. Large Data Set" << std::endl <<
              "2. Small Data Set" << std::endl <<
              "0. Quit Service" << std::endl;
    int input;
    while(!(std::cin >> input) || (input < 0 || input > 2)){
        invalidInputHandler({0,1},2);
    }

    if (input == 0) return;

    if (input == 1){
        largeDataSet = true;
    }
    else{
        largeDataSet = false;
    }
}

void Menu::mainMenu(WaterSupply ws) {
    while(true){
        std::cout << "1. Basic Service Metrics" << std::endl
                  << "2. Reliability and Sensitivity to Failures" << std::endl
                  << "0. Quit service" << std::endl;
        int input;
        while(!(std::cin >> input) || (input < 0 || input > 2)){
            invalidInputHandler({0,1},2);
        }
        if (input == 0){
            return;
        }
        else if (input == 1){
            basicMenu(ws);
        }
        else if (input == 2){
            reliabilityMenu(ws);
        }
    }
}

void Menu::basicMenu(WaterSupply ws){
    std::cout << "1. Max flow" << std::endl
              << "2. List every delivery site that is not receiving enough supply" << std::endl
              << "3. Describe algorithm to minimize difference between capacity and flow" << std::endl
              << "0. Quit" << std::endl;
    int input;
    while (!(std::cin >> input) || input < 0 || input > 3){
        invalidInputHandler({0,1,2},3);
    }

    int input2;
    switch(input) {
        case 0:
            return;
        case 1:
            maxFlowMenu(ws);
            return;
        case 2:
            ws.checkWaterSupplySufficiency(ws, cityF);
            break;
        case 3:
            std::cout << "Step 1: Use the Edmonds-Karp algorithm to get the initial flow values\n"
                         "Step 2: Iterate over each pipeline and calculate the difference between capacity and flow\n"
                         "Step 3: Identify the pipelines with bigger differences\n"
                         "Step 4: Increase these pipelines' flows\n"
                         "Step 5: Verify changes on the system using the Edmonds-Karp algorithm\n"
                         "Repete until no changes are made on step 5\n";
            break;
    }
    std::string dummy;
    std::cout << "(Enter anything to continue):";
    std::cin >> dummy;
}

void Menu::reliabilityMenu(WaterSupply &ws){
    std::cout << "1. Check the outcome of removing a reservoir" << std::endl
              << "2. Check the outcome of removing a pumping station" << std::endl
              << "3. Check the outcome of removing a pipeline" << std::endl
              << "0. Quit" << std::endl;
    int input;
    while (!(std::cin >> input) || input < 0 || input > 3){
        invalidInputHandler({0,1,2},3);
    }
    switch (input){
        case 0:
            return;
        case 1:
            reservoirRemove(ws);
            break;
        case 2:
            stationRemove(ws);
            break;
        case 3:
            pipelineRemove(ws);
            break;
    }
}

void Menu::maxFlowMenu(WaterSupply ws){
    std::cout << "1. List maximum flow of every city" << std::endl
              << "2. Choose a city to check its maximum flow" << std::endl
              << "0. Quit" << std::endl;
    int input;
    while (!(std::cin >> input) || input < 0 || input > 2){
        invalidInputHandler({0,1},2);
    }
    switch (input){
        case 0:
            return;
        case 1:
            for (auto city : ws.getCities()){
                ws.printFlowToCityCode(cityF,city.second.code);
            }
            break;
        case 2:
            chooseCity(ws);
            return;
    }
    std::string dummy;
    std::cout << "(Enter anything to continue):";
    std::cin >> dummy;
}

void Menu::reservoirRemove(WaterSupply ws){
    std::cout << "1. Test removing each reservoir" << std::endl
              << "2. Choose a reservoir to remove" << std::endl
              << "0. Quit" << std::endl;
    int input;
    while (!(std::cin >> input) || input < 0 || input > 2){
        invalidInputHandler({0,1},2);
    }
    switch (input){
        case 0:
            return;
        case 1:
            for (auto x : ws.getReservoirs()){
                if (x.second.code == "sup") continue;
                ws.reservoirImpact(x.second.code);
                std::cout << std::endl;
            }
            break;
        case 2:
            chooseReservoir(ws);
            return;
    }
    std::string dummy;
    std::cout << "(Enter anything to continue):";
    std::cin >> dummy;
}

void Menu::stationRemove(WaterSupply ws){
    std::cout << "1. Test removing each station" << std::endl
              << "2. Choose a station to remove" << std::endl
              << "0. Quit" << std::endl;
    int input;
    while (!(std::cin >> input) || input < 0 || input > 2){
        invalidInputHandler({0,1},2);
    }
    switch (input){
        case 0:
            return;
        case 1:
            for (auto x : ws.getStations()){
                if (x.second.code == "sup") continue;
                ws.checkRemovablePS(x.second.code);
                std::cout << std::endl;
            }
            break;
        case 2:
            chooseStation(ws);
            break;
    }
    std::string dummy;
    std::cout << "(Enter anything to continue):";
    std::cin >> dummy;
}

void Menu::pipelineRemove(WaterSupply ws){
    std::cout << "1. Test removing each pipeline" << std::endl
              << "2. Choose a pipeline to remove" << std::endl
              << "0. Quit" << std::endl;
    int input;
    while (!(std::cin >> input) || input < 0 || input > 2){
        invalidInputHandler({0,1,2},3);
    }
    switch (input){
        case 0:
            return;
        case 1:
            for (auto x : ws.getPipes()){
                ws.checkRemovablePipeline(x.A,x.B);
                std::cout << std::endl;
            }
            break;
        case 2:
            choosePipeline(ws);
            break;
    }
    std::string dummy;
    std::cout << "(Enter anything to continue):";
    std::cin >> dummy;
}

void Menu::chooseCity(WaterSupply ws){
    std::string input;
    std::cout << "Enter the name or the code of the city you want (0 to abort): ";
    std::cin.ignore();
    while(true){
        getline(std::cin, input);
        for (auto x : ws.getCities()){
            if (x.second.code == input){
                ws.printFlowToCityCode(cityF, input);
                return;
            }
            else if(x.second.name == input){
                ws.printFlowToCitybyName(ws, cityF, input);
                return;
            }
        }
        std::cout << "City not found.. Please insert a valid city:";
        }
}

void Menu::chooseReservoir(WaterSupply ws){
    std::string input;
    std::cout << "Enter the name or the code of the reservoir you want (0 to abort): ";
    std::cin.ignore();
    while(true){
        getline(std::cin, input);
        for (auto x : ws.getReservoirs()){
            if (x.second.code == input || x.second.name == input){
                ws.reservoirImpact(input);
                return;
            }
        }
        std::cout << "Reservoir not found.. Please insert a valid reservoir:";
        }
}
void Menu::chooseStation(WaterSupply ws){
    std::cout << "Enter the code of the station you want (0 to abort): ";
    std::string input;
    std::cin >> input;
    if (input == "0") return;
    for (auto station : ws.getStations()){
        if (station.second.code == input) {
            ws.checkRemovablePS(input);
            return;
        }
    }
    std::cout << "Station not found.";
    invalidInputHandler({},0);
    chooseStation(ws);
}

void Menu::choosePipeline(WaterSupply ws){
    std::string input, input1;
    std::cout << "Enter the code of the connected stations (0 to abort).\n"
                 "First:";
    std::cin >> input;
    std::cout << "Second:";
    std::cin >> input1;
    if (input == "0" || input1 == "0") return;
    for (auto pipe : ws.getPipes()){
        if (pipe.A == input && pipe.B == input1){
            ws.checkRemovablePipeline(input,input1);
            return;
        }
        if (pipe.B == input && pipe.A == input1){
            ws.checkRemovablePipeline(input1,input);
            return;
        }
    }
    std::cout << "Pipeline not found.";
    invalidInputHandler({},0);
    choosePipeline(ws);
}



void Menu::invalidInputHandler(std::vector<int> inputs, int last){
    if (last != 0) {
        std::cout << "Invalid input. Accepted inputs: ";
        for (int x: inputs) {
            std::cout << x << ", ";
        }
        std::cout << last << "." << std::endl;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

#endif //AED_PROJECT2_MENU_H


#endif //PROJ_MENU_H
