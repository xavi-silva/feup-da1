#include "WaterSupply.h"
#include "Parser.h"
using namespace std;
/**
 * Definition of all the functions
 */
extern bool largeDataSet;
WaterSupply::WaterSupply() {
    if (largeDataSet){
        Parser::parseCities("../Proj\\Data\\Project1LargeDataSet\\Cities.csv",*this);
        Parser::parsePipes("../Proj\\Data\\Project1LargeDataSet\\Pipes.csv",*this);
        Parser::parseReservoirs("../Proj\\Data\\Project1LargeDataSet\\Reservoir.csv",*this);
        Parser::parseStations("../Proj\\Data\\Project1LargeDataSet\\Stations.csv",*this);
    }

    else{
        Parser::parseCities("../Proj\\Data\\Project1DataSetSmall\\Cities_Madeira.csv", *this);
        Parser::parsePipes("../Proj\\Data\\Project1DataSetSmall\\Pipes_Madeira.csv",*this);
        Parser::parseReservoirs("../Proj\\Data\\Project1DataSetSmall\\Reservoirs_Madeira.csv",*this);
        Parser::parseStations("../Proj\\Data\\Project1DataSetSmall\\Stations_Madeira.csv",*this);
    }

}


/**
 * Getter of the system pipes. It returns all pipes.
 * @return vector<Pipe>
 */
std::vector<Pipe> &WaterSupply::getPipes() {
    return Pipes;
}
/**
 * Getter of the system Delivery Sites. It returns all DS.
 * @return vector<City>
 */
std::unordered_map<int, City> &WaterSupply::getCities() {
    return Cities;
}
/**
 * Getter of the system Pumping Stations. It returns all PS.
 * @return vector<Stations>
 */
std::unordered_map<int, Station> &WaterSupply::getStations() {
    return Stations;
}
/**
 * Getter of the system Water Reservoirs. It returns all WR.
 * @return vector<Pipe>
 */
std::unordered_map<int, Reservoir> &WaterSupply::getReservoirs() {
    return Reservoirs;
}
/**
 * Add a City object to the network
 * @param city
 */
void WaterSupply::addCity(const City& city) {
    Cities.insert({city.id,city});
}
/**
 * Add a Station object to the network
 * @param station
 */
void WaterSupply::addStation(const Station& station) {
    Stations.insert({station.id,station});
}
/**
 * Add a Reservor object to the network.
 * @param reservoir
 */
void WaterSupply::addReservoir(const Reservoir& reservoir) {
    Reservoirs.insert({reservoir.id,reservoir});
}
/**
 * Add a Pipe object to the network.
 * @param pipe
 */
void WaterSupply::addPipe(const Pipe& pipe) {
    Pipes.push_back(pipe);
}
/**
 * Function that build the network, adding all the vertexs (Cities, Reservoirs and Stations) and edges (Pipes), and also settes the residual values to Cities
 */
void WaterSupply::buildNetwork() {
    Graph<std::string> g;
    network = g;
    //Add vertices
    for(const auto& city : Cities){
        network.addVertex(city.second.code);
    }
    for (const auto& reservoir : Reservoirs) {
        network.addVertex(reservoir.second.code);
    }
    for (const auto& station : Stations) {
        network.addVertex(station.second.code);
    }

    //Add edges
    for (const auto& pipe : Pipes){
        network.addEdge(pipe.A, pipe.B, pipe.capacity);
        //if the pipe is bidirect
        if(pipe.direction == 0){
            network.addEdge(pipe.B, pipe.A, pipe.capacity);
        }
    }

    for(const auto& city : Cities){
        auto v = network.findVertex(city.second.code);
        v->setResidual(city.second.demand);
    }
}

/******************************** Edmond-Karps - 2.1 ***********************************************/
bool largeDataSet = true;
std::unordered_map<std::string, double> cityF;
/**
 * Function that calculates the specific flow to a node
 * @param Graph<std::string>* g
 * @param const std::string& node
 * @return double totalFlow
 */
double WaterSupply::calculateFlowToNode(Graph<std::string>* g, const std::string& node){
    double totalFlow = 0;
    auto vertex = g->findVertex(node);
    if(vertex == nullptr) return totalFlow;

    for(auto e : vertex->getIncoming()){
        totalFlow += e->getFlow();
    }

    return totalFlow;
}

/**
 * Auxiliary function to reset the flows (setting them to 0) of the edges
 * @param Graph<std::string>* g
 */
void WaterSupply::resetFlows(Graph<std::string>* g){
    for(auto v : g->getVertexSet()){
        for(auto e : v->getAdj()){
            e->setFlow(0);
        }
    }
}

/**
 * Auxiliary function that calculates the flow incoming to a specific City
 * @param Graph<std::string>* g
 * @param std::string cityCode
 * @return double totalFlow
 */

double WaterSupply::calculateFlowToCity(Graph<std::string>* g, std::string cityCode){
    double totalFlow = 0;
    for(auto v : g->getVertexSet()){
        for(auto e : v->getAdj()){
            if(e->getDest()->getInfo() == cityCode){
                totalFlow += e->getFlow();
            }
        }
    }
    return totalFlow;
}
/**
 * Function to test the given vertex 'w' and visit it if the conditions are met
 * @param Graph<std::string> *g
 * @param std::queue<Vertex<std::string>*> &q
 * @param Edge<std::string> *e
 * @param Vertex<std::string> *w
 * @param double residual
 * @param WaterSupply ws
 */
void WaterSupply::testAndVisit(Graph<std::string> *g, std::queue<Vertex<std::string>*> &q, Edge<std::string> *e, Vertex<std::string> *w, double residual, WaterSupply ws){
    if(!w->isVisited() && residual > 0){
        //Checks if it is a City, and if it is, we check if the residual if less or equal to 0. If so, we exit the function.
        if(e->getOrig()->getInfo()[0] == 'C'){
            if(e->getOrig()->getResidual() <= 0){
                return;
            }
        }

        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

/**
 * Function to find an augmenting path using BFS.
 * @param Graph<std::string> *g
 * @param Vertex<std::string> *s
 * @param Vertex<std::string> *t
 * @param WaterSupply ws
 * @return bool
 */
bool WaterSupply::findAugmentingPath(Graph<std::string> *g, Vertex<std::string> *s, Vertex<std::string> *t, WaterSupply ws){
    //Mark all vertices as not visited
    for(auto v : g->getVertexSet()){
        v->setVisited(false);
    }
    //mark the source vertex as visited and enqueue it
    s->setVisited(true);
    std::queue<Vertex<std::string> *> q;
    q.push(s);

    //BFS to find an augmenting path
    while(!q.empty() && !t->isVisited()){
        Vertex<std::string>* v= q.front();
        q.pop();

        //Process outgoing edges
        for(auto e : v->getAdj()){
            testAndVisit(g,q,e,e->getDest(),e->getWeight()- e->getFlow(), ws);
        }

        //Process Incoming Edges
        for(auto e: v->getIncoming()){
            testAndVisit(g,q,e,e->getOrig(), e->getFlow(), ws);
        }
    }

    //Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

/**
 * Function to find the minimum residual capacity along the augmenting path
 * @param Vertex<std::string> *s
 * @param Vertex<std::string> *t
 * @return double minResidual
 */
double WaterSupply::findMinResidualAlongPath(Vertex<std::string> *s, Vertex<std::string> *t){
    double minResidual = std::numeric_limits<double>::max();
    // Traverse the augmenting path to find the minimum residual capacity
    for(auto v = t; v != s; ){
        auto e = v->getPath();
        double residual;

        if(e->getDest() == v){
            residual = e->getWeight() - e->getFlow();
            v = e->getOrig();
        }else{
            residual = e->getFlow();
            v = e->getDest();
        }
        if(residual < minResidual){
            minResidual = residual;
        }
    }
    return minResidual;
}

/**
 * Function to augment flow along the augmenting path with the given flow value
 * @param Vertex<std::string> *s
 * @param Vertex<std::string> *t
 * @param double f
 */
void WaterSupply::augmentFlowAlongPath(Vertex<std::string> *s, Vertex<std::string> *t, double f){
    //Traverse the augmenting path and update the flow values accordingly
    for(auto v = t; v != s;){
        auto e = v->getPath();
        double flow = e->getFlow();
        //If it's a city, we update the residual value as the result of the subtraction of the current value of it minus the flow value
        if(v->getInfo()[0] == 'C'){
            v->setResidual(v->getResidual() - f);
        }
        if(e->getDest() == v){
            e->setFlow(flow + f);
            v = e->getOrig();
        }else{
            e->setFlow(flow-f);
            v = e->getDest();
        }
    }
}

/**
 * Function that initializes all edge flows to zero, then repeatedly finds augmenting paths between the source and target vertices.
 * For each path found, it augments the flow along this path by the minimum residual capacity found on the path.
 *
 * @param Graph<std::string> *g
 * @param std::string source
 * @param std::string target
 * @param WaterSupply ws
 * @throws std::logic_error if parameters are invalid
 */
void WaterSupply::edmondsKarp(Graph<std::string> *g, std::string source, std::string target, WaterSupply ws) {
    //Find source and target vertices
    Vertex<std::string>* s= g->findVertex(source);
    Vertex<std::string>* t= g->findVertex(target);

    //validate source and target vertices
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid");

    //initialize flow on all edges to 0
    for(auto v : g->getVertexSet()){
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    //while there is an augmenting path, augment the flow along th path
    while(findAugmentingPath(g,s,t,ws)){
        double f= findMinResidualAlongPath(s,t);
        augmentFlowAlongPath(s,t,f);
    }
}
/**
 * Function that adds a super-source connected to all reservoirs and a super-sink connected to all cities. Runs the Edmonds-Karp
 * algorithm to find the total maximum flow from the super-source to the super-sink, effectively calculating the
 * total maximum water delivery to all cities from all reservoirs.
 * @param WaterSupply& ws
 */
void WaterSupply::edmondsKarp_big(WaterSupply& ws){
    auto g = &ws.network;
    double totalMaxFlowToCity = 0;

    Reservoir super_src = {"super_source", "SSource", -1,"sup", -1};
    City super_sink = {"super_sink", -2, "SSink", 1, 1};

    ws.addReservoir(super_src);
    ws.addCity(super_sink);

    g->addVertex(super_src.code);
    g->addVertex(super_sink.code);

    // Connect super_source to each reservoir
    for(auto& r : ws.getReservoirs()){
        g->addEdge(super_src.code, r.second.code, r.second.maxDelivery);
    }

    // Connect each city to super_sink
    for(auto& c : ws.getCities()){
        g->addEdge(c.second.code, super_sink.code, c.second.demand);
    }

    edmondsKarp(g, super_src.code, super_sink.code, ws);

    g->removeVertex(super_src.code);
    g->removeVertex(super_sink.code);
}

/**
 * Function that populates cityF with the maximum flow to each city
 * @param std::unordered_map<std::string, double>& cityF
 * @param WaterSupply& ws
 */
void WaterSupply::get_MaxFlow(std::unordered_map<std::string, double>& cityF, WaterSupply& ws) {
    edmondsKarp_big(ws);
    auto g = &ws.network;
    for(const auto& cityPair : ws.getCities()) {
        std::string cityCode = cityPair.second.code;
        double flow = calculateFlowToCity(g, cityPair.second.code);
        cityF[cityCode] = flow;
    }
}
/**
 * Function that prints the flow to a specific city using its city code
 * @param const std::unordered_map<std::string, double>& cityF
 * @param const std::string& cityCode
 */
void WaterSupply::printFlowToCityCode(const std::unordered_map<std::string, double>& cityF, const std::string& cityCode) {
    auto it = cityF.find(cityCode);
    if (it != cityF.end()) {
        if(cityCode != "sup" && cityCode != "SSink"){
        std::cout << "Flow to city " << cityCode << ": " << it->second << " units.\n";}
    } else {
        std::cout << "City code " << cityCode << "' not found in the network.\n";
    }
}
/**
 * Function that prints the flow to a specific city using the city name
 * @param WaterSupply& ws
 * @param const std::unordered_map<std::string, double>& cityF
 * @param const std::string& cityName
 */
void WaterSupply::printFlowToCitybyName(WaterSupply& ws,const std::unordered_map<std::string, double>& cityF, const std::string& cityName){
    string cityCode = "";
    for(const auto& c : ws.getCities()) {
        if (c.second.name == cityName) {
            cityCode = c.second.code;
        }
    }
    auto it = cityF.find(cityCode);
    if (it != cityF.end()) {
        std::cout << "Flow to city " << cityName << ": " << it->second << " units.\n";
    } else {
        std::cout << "City name " << cityCode << "' not found in the network.\n";
    }
}
/**
 * Function that calculates the total flow in the network
 * @param WaterSupply& ws
 * @param const std::unordered_map<std::string, double>& cityF
 */
void WaterSupply::maxFlowGeral(WaterSupply& ws, const std::unordered_map<std::string, double>& cityF){
    double res = 0;
    for(auto c : ws.getCities()){
        auto city_flow = cityF.find(c.second.code)->second;
        res += city_flow;

    }
    cout << " " << res;
}

/********************   T2.2    ***********************/
/**
 * Function that checks if there are cities that have  water sufficiency
 * @param WaterSupply& ws
 * @param const std::unordered_map<std::string, double>& cityF
 */
void WaterSupply::checkWaterSupplySufficiency(WaterSupply& ws, const std::unordered_map<std::string, double>& cityF) {
// First, run the Edmonds-Karp algorithm on the entire network to ensure we have the maximum flow values updated.
    for(auto c : ws.getCities()){
        auto flow_to_city = cityF.find(c.second.code)->second;
        double city_demand = c.second.demand;
        double res = city_demand - flow_to_city;
        if(res != 0 & c.second.id != -1 & c.second.id != -2){
            cout << c.second.name << "  has a deficit of " << (city_demand-flow_to_city) << " units" << endl;}
    }

}

/*************************** **********************/


/*T-3.1
Allow the user to selectively remove one reservoir and
list the affected cities whose water supply does not meet its demand*/
/**
 * @brief Remove um reservatório da rede e avalia o impacto que esta ação tem nos flows das cidades.
 * Esta função solicita ao usuário o código de um reservatório a ser removido da rede.
 * Em seguida, remove o vértice correspondente ao reservatório do grafo da instância atual.
 * Posteriormente, executa o algoritmo de Edmonds-Karp para calcular o fluxo máximo
 * nas duas instâncias de WaterSupply: a instância modificada sem o reservatório
 * e a instância original. Finalmente, verifica se há um decréscimo de flow e exibe o impacto nos fluxos das cidades.
 *
 * @param input código ou nome de um reservatório para remover.
 */
void WaterSupply::reservoirImpact(string input) {
    buildNetwork(); // Rebuild original network
    string reservoir_code;
    bool affected = false;
    for (auto x : Reservoirs){ // Find corresponding reservoir
        if (input == x.second.code || input == x.second.name) {
            reservoir_code = x.second.code;
            break;
        }
    }
    WaterSupply nova = WaterSupply(); // Creating mockup network and corresponding graph
    nova.buildNetwork();
    auto g = nova.network;
    auto v = g.findVertex(reservoir_code);
    if (v == nullptr) {
        std::cout << "Reservoir '" << reservoir_code << "' not found in the network.\n";
        return;
    }
    g.removeVertex(v->getInfo()); // Remove reservoir on mockup graph
    edmondsKarp_big(nova); // Calculate flows after removing
    edmondsKarp_big(*this);   // Calculate flows on original network (with reservoir)
    cout << "Removing " << reservoir_code << " ..." << endl;
    for(auto city : getCities()){
        double before = calculateFlowToCity(&network,city.second.code);
        double after = calculateFlowToCity(&g,city.second.code);
        double diff = before - after;
        if(diff > 0){ // If flow decreased -> city was affected
            cout<<city.second.name<< " flow has been affected. Before: "<< before <<"  Now: "<< after << "  Difference: " << diff << endl;
            affected = true;
        }
    }
    if (!affected) cout << "No cities affected.\n";
}

/*T-3.2
Allow the user to selectively remove one pumping station and
list the affected cities whose water supply does not meet its demand*/
/**
 * @brief Remove uma estação da rede e avalia o impacto que esta ação tem nos flows das cidades.
 * Esta função recebe o código de uma estação para remover da rede.
 * Em seguida, remove o vértice correspondente ao reservatório do grafo da instância atual.
 * Posteriormente, executa o algoritmo de Edmonds-Karp para calcular o fluxo máximo
 * nas duas instâncias de WaterSupply: a instância modificada sem o reservatório
 * e a instância original. Finalmente, verifica se há um decréscimo de flow e exibe o impacto nos fluxos das cidades.
 *
 * @param code código correspondente a uma pumping station para remover.
 */
void WaterSupply::checkRemovablePS(string code){
    buildNetwork(); // Rebuild original network
    bool affected = false;
    WaterSupply nova = WaterSupply();  // Creating mockup network and corresponding graph
    nova.buildNetwork();
    auto g = nova.network;
    auto v = g.findVertex(code);
    g.removeVertex(v->getInfo()); // Remove reservoir on mockup graph
    edmondsKarp_big(nova); // Calculate flows after removing
    edmondsKarp_big(*this); // Calculate flows on original network (with reservoir)
    cout << "Removing " << code << " ..." << endl;

    for(auto city : getCities()){
        double before = calculateFlowToCity(&network,city.second.code);
        double after = calculateFlowToCity(&g,city.second.code);
        double diff = before - after;
        if(diff > 0){ // If flow decreased -> city was affected
            cout<<city.second.name<< " flow has been affected. Before: "<< before <<"  Now: "<< after << "  Difference: " << diff << endl;
            affected = true;
        }
    }
    if (!affected) cout << "No cities affected.\n";

}

/*T-3.3
Allow the user to selectively remove one pipeline and
list the affected cities whose water supply does not meet its demand*/
/**
 * @brief Remove uma pipeline da rede e avalia o impacto que esta ação tem nos flows das cidades.
 * Esta função recebe o código de dois reservatórios ou pumping stations para remover da rede.
 * Em seguida, remove o edge correspondente no grafo da instância atual.
 * Posteriormente, executa o algoritmo de Edmonds-Karp para calcular o fluxo máximo
 * nas duas instâncias de WaterSupply: a instância modificada sem o reservatório
 * e a instância original. Finalmente, verifica se há um decréscimo de flow e exibe o impacto nos fluxos das cidades.
 *
 * @param codeA código correspondente a uma pumping station ou reservatorio.
 * @param codeB código correspondente a uma pumping station ou reservatorio.
 */
void WaterSupply::checkRemovablePipeline(std::string codeA, std::string codeB){
    buildNetwork(); // Rebuild original netowork
    bool affected = false;
    WaterSupply nova = WaterSupply(); // Creating mockup network and corresponding graph
    nova.buildNetwork();
    auto g = nova.network;

    g.removeEdge(codeA,codeB); // Remove reservoir on mockup graph
    edmondsKarp_big(nova); // Calculate flows after removing
    edmondsKarp_big(*this); // Calculate flows on original network (with reservoir)
    cout << "Removing " << codeA << "-" << codeB << " ..." << endl;

    for(auto city : getCities()){
        double before = calculateFlowToCity(&network,city.second.code);
        double after = calculateFlowToCity(&g,city.second.code);
        double diff = before - after;
        if(diff > 0){ // If flow decreased -> city was affected
            cout<<city.second.name<< " flow has been affected. Before: "<< before <<"  Now: "<< after << "  Difference: " << diff << endl;
            affected = true;
        }
    }
    if (!affected) cout << "No cities affected.\n";

}


