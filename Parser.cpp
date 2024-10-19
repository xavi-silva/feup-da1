#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser.h"
#include "WaterSupply.h"
#include <string>
#include "data_structures/Graph.h"

/**
 * @brief Parses cities from a CSV file and adds them to the WaterSupply system.
 *
 * Opens and reads a CSV file specified by the Cities_cvs parameter. Each line in the file
 * represents a city with its details separated by commas. The function skips the header line,
 * then iterates over each subsequent line to extract city details, which are used to create a City
 * struct that is then added to the WaterSupply instance.
 *
 * @param Cities_cvs Path to the CSV file containing cities information.
 * @param ws Reference to the WaterSupply instance where parsed cities will be added.
 */
void Parser::parseCities(const std::string& Cities_cvs,WaterSupply& ws){
    std::ifstream file(Cities_cvs);

    if (!file.is_open()) {
        std::cout << "Error opening the file!" << std::endl;
        return;
    }

    std::string line;
    getline(file,line); //ignorar header
    while (getline(file, line)) {
        std::string name;
        std::string code;
        std::string id;
        std::string demand;
        std::string population;
        std::istringstream ss(line);
        std::getline(ss, name, ',');
        std::getline(ss, id, ',');
        std::getline(ss, code, ',');
        std::getline(ss, demand, ',');
        std::getline(ss, population, ',');

        City  city={name,stoi(id),code,stof(demand),stoi(population)};
        ws.addCity(city);
    }

}
/**
 * @brief Parses reservoirs from a CSV file and adds them to the WaterSupply system.
 *
 * This function behaves similarly to parseCities, tailored for reservoir information. It expects a CSV
 * file where each line contains a reservoir's details. The function creates a Reservoir struct for each
 * line and adds it to the WaterSupply instance.
 *
 * @param Reservoirs_cvs Path to the CSV file containing reservoirs information.
 * @param ws Reference to the WaterSupply instance where parsed reservoirs will be added.
 */
void Parser::parseReservoirs(const std::string& Reservoirs_cvs,WaterSupply& ws){
    std::ifstream file(Reservoirs_cvs);

    if (!file.is_open()) {
        std::cout << "Error opening the file!" << std::endl;
        return;
    }

    std::string line;
    getline(file,line); //ignorar header
    while (getline(file, line)) {
        std::string name;
        std::string municipality;
        std::string id;
        std::string code;
        std::string maxDelivery;
        std::istringstream ss(line);
        std::getline(ss, name, ',');
        std::getline(ss, municipality, ',');
        std::getline(ss, id, ',');
        std::getline(ss, code, ',');
        std::getline(ss, maxDelivery, ',');

        Reservoir  reservoir={name,municipality,stoi(id),code,stoi(maxDelivery)};
        ws.addReservoir(reservoir);
    }
}
/**
 * @brief Parses stations from a CSV file and adds them to the WaterSupply system.
 *
 * Opens and reads station data from the specified CSV file, creating and adding Station structs
 * to the WaterSupply instance for each station described in the file.
 *
 * @param Stations_cvs Path to the CSV file containing stations information.
 * @param ws Reference to the WaterSupply instance where parsed stations will be added.
 */
void Parser::parseStations(const std::string& Stations_cvs,WaterSupply& ws){
    std::ifstream file(Stations_cvs);

    if (!file.is_open()) {
        std::cout << "Error opening the file!" << std::endl;
        return;
    }

    std::string line;
    getline(file,line); //ignorar header
    while (getline(file, line)) {
        std::string code;
        std::string id;
        std::istringstream ss(line);
        std::getline(ss, id, ',');
        std::getline(ss, code, ',');

        Station station={stoi(id),code};
        ws.addStation(station);
    }
}

/**
 * @brief Parses pipes from a CSV file and adds them to the WaterSupply system.
 *
 * Reads pipe data from the given CSV file, where each line includes details about a single pipe.
 * For each line, a Pipe struct is created and added to the WaterSupply instance, representing
 * connections between nodes in the water supply network.
 *
 * @param Pipes_cvs Path to the CSV file containing pipes information.
 * @param ws Reference to the WaterSupply instance where parsed pipes will be added.
 */
void Parser::parsePipes(const std::string& Pipes_cvs,WaterSupply& ws){
    std::ifstream file(Pipes_cvs);

    if (!file.is_open()) {
        std::cout << "Error opening the file!" << std::endl;
        return;
    }

    std::string line;
    getline(file,line); //ignorar header
    while (getline(file, line)) {
        std::string A;
        std::string B;
        std::string capacity;
        std::string direction;
        std::istringstream ss(line);
        std::getline(ss, A, ',');
        std::getline(ss, B, ',');
        std::getline(ss, capacity, ',');
        std::getline(ss, direction, ',');

        Pipe  pipe={A,B,stoi(capacity),stoi(direction)};
        ws.addPipe(pipe);
    }
}
