#include <iostream>
#include "Proj/WaterSupply.h" // Include the definition of the WaterSupply class.
#include "Proj/Menu.h" // Include the definition of the Menu class.

int main(){
    WaterSupply ws; // Create an instance of WaterSupply to manage the water supply network.
    Menu menu; // Create an instance of Menu to handle user interactions.

    menu.chooseDataSet(&ws); // Prompt the user to choose a data set for the water supply network.

    ws = WaterSupply(); // Re-initialize ws to reset or start with a new WaterSupply instance.
    ws.buildNetwork(); // Build the network graph based on the data set chosen or default data.

    ws.get_MaxFlow(cityF, ws); // Calculate the maximum flow from sources to sinks in the network.

    menu.mainMenu(ws); // Display the main menu of the application for further user interactions.

    return 0; // End the program.
}
