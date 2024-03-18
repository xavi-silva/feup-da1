#import "functions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cmath>

using namespace std;

void clearConsole(){
    for (int i=0;i<50;i++){
        cout << " " << endl;
    }
}

void readCities(){
    ifstream file("Data/Project1LargeDataSet/Cities.csv");

    if (!file.is_open()) {
        cout << "Error opening the file!" << endl;
        return;
    }

    string line;
    bool flagFirstLine = true;
    while (getline(file, line)) {
        vector<string> row; // vector para guardar cada palavra de uma linha do ficheiro
        istringstream lineStream(line);
        string word;
        while (getline(lineStream, word, ',')) {
            row.push_back(word);
        }



        flagFirstLine=false;
    }
}

void readPipes(){
    ifstream file("Data/Project1LargeDataSet/Pipes.csv");

    if (!file.is_open()) {
        cout << "Error opening the file!" << endl;
        return;
    }

    string line;
    bool flagFirstLine = true;
    while (getline(file, line)) {
        vector<string> row; // vector para guardar cada palavra de uma linha do ficheiro
        istringstream lineStream(line);
        string word;
        while (getline(lineStream, word, ',')) {
            row.push_back(word);
        }



        flagFirstLine=false;
    }
}

void readreservoir(){
    ifstream file("Data/Project1LargeDataSet/Reservoir.csv");

    if (!file.is_open()) {
        cout << "Error opening the file!" << endl;
        return;
    }

    string line;
    bool flagFirstLine = true;
    while (getline(file, line)) {
        vector<string> row; // vector para guardar cada palavra de uma linha do ficheiro
        istringstream lineStream(line);
        string word;
        while (getline(lineStream, word, ',')) {
            row.push_back(word);
        }



        flagFirstLine=false;
    }
}

void readStations(){
    ifstream file("Data/Project1LargeDataSet/Stations.csv");

    if (!file.is_open()) {
        cout << "Error opening the file!" << endl;
        return;
    }

    string line;
    bool flagFirstLine = true;
    while (getline(file, line)) {
        vector<string> row; // vector para guardar cada palavra de uma linha do ficheiro
        istringstream lineStream(line);
        string word;
        while (getline(lineStream, word, ',')) {
            row.push_back(word);
        }



        flagFirstLine=false;
    }
}