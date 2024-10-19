#ifndef UNTITLED5_DATATYPES_H
#define UNTITLED5_DATATYPES_H

#include <string>
/**
 * @struct City
 * @brief Represents a city in the water supply network.
 *
 * Stores information about a city including its name, id, code, water demand, and population size.
 */
struct City{
    std::string name;
    int id;
    std::string code;
    float demand;
    int population;
};
/**
 * @struct Reservoir
 * @brief Represents a water reservoir.
 *
 * Contains details about a reservoir such as its name, the municipality it serves,
 * id, code in the network, and its maximum delivery capacity.
 */
struct Reservoir{
    std::string name;
    std::string municipality;
    int id;
    std::string code;
    int maxDelivery;
};
/**
 * @struct Station
 * @brief Represents a pumping or relay station in the network.
 *
 * Holds the unique identifier and code for a station in the water supply network.
 */
struct Station{
    int id;
    std::string code;
};
/**
 * @struct Pipe
 * @brief Represents a connection (pipe) between two network nodes.
 *
 * Describes a pipe in the network, including the start and end nodes, its capacity,
 * and the direction of water flow (1 for unidirectional, 0 for bidirectional).
 */
struct Pipe{
    std::string A;
    std::string B;
    int capacity;
    int direction; //1 ou 0
};
#endif //UNTITLED5_DATATYPES_H
