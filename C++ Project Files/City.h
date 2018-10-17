//
// Created by Tripp Gordon on 9/12/18.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;
typedef chrono::high_resolution_clock Clock;

#ifndef PROJECT2_CITY_H
#define PROJECT2_CITY_H

#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "SplayTree.h"

// struct to define geographic location
struct Location {
    double lat;
    double lng;
};

// class to define a city in the US
class City {
private:
    string name;
    string state_id;
    Location location;
    int population;
    double density;
    int id;

public:
    /* Constructors */
    City();
    City(string name,string state_id,Location location,
         int population,double density,int id);

    /* Getters */
    string getName() const;
    string getState_id() const;
    Location getLocation() const;
    int getPopulation() const;
    double getDensity() const;
    int getId() const;

    /* Setters */
    void setName(string name);
    void setPopulation(int population);
    void setDensity(double density);
    void setId(int id);

    // overload >, <, <<, and == operators
    // help from https://www.tutorialspoint.com/cplusplus/
    friend bool operator > (const City &lhs, const City &rhs);
    friend bool operator < (const City &lhs, const City &rhs);
    friend ostream operator << (ostream &output, const City &city);
    friend bool operator == (const City &lhs, const City &rhs);
};

// function to read the file
void importCities(string filename, vector<City> &cities);

// function to display the file
void displayCities(const vector<City> &cities);

// function to calculate avg population
double calculateAvgPop(const vector<City> &cities);

// function to create 3 integer files for searching
void createIntFiles(const vector<City> &cities);

// function to take intfile name, convert intfile to a vector
vector<int> createIntVectorFromFile(string intFileName);

// function to record find results from BST
void recordDepthsBST(BinarySearchTree<City>& tree,const vector<City>& cities);

// function to record find results from AVL tree
void recordDepthsAVL(AVLTree<City>& tree,const vector<City>& cities);

// function to record find results from Splay tree
void recordDepthsSPL(SplayTree<City>& tree,const vector<City>& cities);

// function to record all information from finding objects in the trees.
// Calls above helper functions, times it, and outputs results to a file.
void recordInfo(BinarySearchTree<City>& citiesBST,AVLTree<City>& citiesAVL,SplayTree<City>& citiesSPLAY,vector<City>&cities);


#endif //PROJECT2_CITY_H
