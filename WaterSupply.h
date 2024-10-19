#ifndef UNTITLED5_WATERSUPPLY_H
#define UNTITLED5_WATERSUPPLY_H

#include <fstream>
#include <sstream>
#include <vector>
#include "unordered_map"
#include "data_structures/Graph.h"
#include "DataTypes.h"
#include <utility>

/**
 * @class WaterSupply
 * @brief Manages the water supply network, including cities, stations, reservoirs, and pipes.
 *
 * This class encompasses the functionality to construct and manipulate a graph-based representation
 * of a water supply network. It allows for the addition of cities, stations, reservoirs, and pipes,
 * building the network graph, and running flow calculations across the network.
 */
class WaterSupply {
private:
    std::unordered_map<int, City> Cities; ///< Stores cities in the network by their IDs.
    std::unordered_map<int, Station> Stations; ///< Stores stations in the network by their IDs.
    std::unordered_map<int, Reservoir> Reservoirs; ///< Stores reservoirs in the network by their IDs.
    std::vector<Pipe> Pipes; ///< Stores all pipes in the network.

public:
    WaterSupply(); ///< Constructor initializes a WaterSupply object.

    /**
     * Constructs the graph representing the water supply network.
     */
    void buildNetwork();

    // Accessors
    std::unordered_map<int, City>& getCities();
    std::unordered_map<int, Station>& getStations();
    std::unordered_map<int, Reservoir>& getReservoirs();
    std::vector<Pipe>& getPipes();

    // Modifiers
    void addCity(const City& city);
    void addStation(const Station& station);
    void addReservoir(const Reservoir& reservoir);
    void addPipe(const Pipe& pipe);

    Graph<std::string> network; ///< The graph representing the water supply network.

    // Flow calculation and manipulation methods
    void resetFlows(Graph<std::string>* g);
    double calculateFlowToNode(Graph<std::string>* g, const std::string& node);
    double calculateFlowToCity(Graph<std::string>* g, std::string cityCode);
    void testAndVisit(Graph<std::string>* g, std::queue<Vertex<std::string>*>& q, Edge<std::string>* e, Vertex<std::string>* w, double residual, WaterSupply ws);
    bool findAugmentingPath(Graph<std::string>* g, Vertex<std::string>* s, Vertex<std::string>* t, WaterSupply ws);
    double findMinResidualAlongPath(Vertex<std::string>* s, Vertex<std::string>* t);
    void augmentFlowAlongPath(Vertex<std::string>* s, Vertex<std::string>* t, double f);
    void edmondsKarp(Graph<std::string>* g, std::string source, std::string target, WaterSupply ws);
    void edmondsKarp_big(WaterSupply& ws);
    void get_MaxFlow(std::unordered_map<std::string, double>& cityF, WaterSupply& ws);
    void printFlowToCityCode(const std::unordered_map<std::string, double>& cityF, const std::string& cityCode);
    void printFlowToCitybyName(WaterSupply& ws, const std::unordered_map<std::string, double>& cityF, const std::string& cityName);
    void maxFlowGeral(WaterSupply& ws, const std::unordered_map<std::string, double>& cityF);
    void checkWaterSupplySufficiency(WaterSupply& ws, const std::unordered_map<std::string, double>& cityF);
    void reservoirImpact(std::string input);
    void checkRemovablePS(std::string code);
    void checkRemovablePipeline(std::string codeA, std::string codeB);
};

extern std::unordered_map<std::string, double> cityF; ///< Global map tracking the maximum flow to each city.

void reservoirImpact(WaterSupply& ws); ///< Evaluates the impact of removing a reservoir from the network.

#endif // UNTITLED5_WATERSUPPLY_H

