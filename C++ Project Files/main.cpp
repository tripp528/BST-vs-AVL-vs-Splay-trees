//
// Created by Tripp Gordon on 9/12/18.
//

#include "City.h"


int main() {
    // create vector of cities from file and display
    vector<City> cities;
    importCities("cities.csv", cities);

    // put cities in BST, AVL, and SPLAY Trees
    BinarySearchTree<City> citiesBST;
    AVLTree<City> citiesAVL;
    SplayTree<City> citiesSPLAY;
    for (City city : cities) {
        citiesBST.add(city);
        citiesAVL.add(city);
        citiesSPLAY.add(city);
    }

    // create and add 3 dummy objects to vector
    for (int i = 0; i < 3; ++i) {
        City dummy;
        dummy.setId(1045 + i);
        dummy.setName("dummy" + to_string(i+1));
        cities.push_back(dummy);
    }

    // display contents of vector
    displayCities(cities);

    // create the 3 integer files
    createIntFiles(cities);

    /**
     * record depths
     * (and how long it takes)
     */
    recordInfo(citiesBST,citiesAVL,citiesSPLAY,cities);

    return 0;
}