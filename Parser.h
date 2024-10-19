#ifndef UNTITLED5_PARSER_H
#define UNTITLED5_PARSER_H
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include "DataTypes.h"

/**
 * @class Parser
 * @brief Handles parsing of network components from CSV formatted strings.
 *
 * This class provides static methods to parse cities, reservoirs, stations, and pipes information
 * from given CSV formatted strings and populate them into a WaterSupply object. Each method
 * expects a specific CSV format corresponding to its respective network component.
 */
class WaterSupply;
class Parser {
public:
    Parser()=default;
    /**
     * @brief Default constructor.
     */
    /**
     * @brief Parses pipe information from a CSV string and adds them to the WaterSupply instance.
     *
     * @param Pipes_cvs The CSV string containing pipe data. Expected format: "A,B,capacity,direction".
     * @param ws Reference to the WaterSupply instance where parsed pipes will be added.
     */
    static void parsePipes(const std::string& Pipes_cvs, WaterSupply& ws);

    /**
     * @brief Parses city information from a CSV string and adds them to the WaterSupply instance.
     *
     * @param Cities_cvs The CSV string containing city data. Expected format: "name,id,code,demand,population".
     * @param ws Reference to the WaterSupply instance where parsed cities will be added.
     */
    static void parseCities(const std::string& Cities_cvs, WaterSupply& ws);

    /**
     * @brief Parses station information from a CSV string and adds them to the WaterSupply instance.
     *
     * @param Stations_cvs The CSV string containing station data. Expected format: "id,code".
     * @param ws Reference to the WaterSupply instance where parsed stations will be added.
     */
    static void parseStations(const std::string& Stations_cvs, WaterSupply& ws);

    /**
     * @brief Parses reservoir information from a CSV string and adds them to the WaterSupply instance.
     *
     * @param Reservoirs_cvs The CSV string containing reservoir data. Expected format: "name,municipality,id,code,maxDelivery".
     * @param ws Reference to the WaterSupply instance where parsed reservoirs will be added.
     */
    static void parseReservoirs(const std::string& Reservoirs_cvs, WaterSupply& ws);
};

#endif //UNTITLED5_PARSER_H
