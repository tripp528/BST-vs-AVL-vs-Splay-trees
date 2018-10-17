//
// Created by Tripp Gordon on 9/12/18.
//
#include "City.h"

City::City() {
    name = "nocity";
    state_id = "NO";
    location.lat = 2;
    location.lng = 4;
    population = 200;
    density = 10;
    id = 2000;
}

City::City(string name, string state_id, Location location, int population, double density, int id) {
    this->name = name;
    this->state_id = state_id;
    this->location.lat = location.lat;
    this->location.lng = location.lng;
    this->population = population;
    this->density = density;
    this->id = id;
}

string City::getName() const {
    return name;
}

string City::getState_id() const {
    return state_id;
}

Location City::getLocation() const {
    return location;
}

int City::getPopulation() const {
    return population;
}

double City::getDensity() const {
    return density;
}

int City::getId() const {
    return id;
}

void City::setName(string name) {
    this->name = name;
}

void City::setPopulation(int population) {
    this->population = population;
}

void City::setDensity(double density) {
    this->density = density;
}

void City::setId(int id) {
    this->id = id;
}

bool operator>(const City &lhs, const City &rhs) {
    return lhs.getId() > rhs.getId();
}

bool operator<(const City &lhs, const City &rhs) {
    return lhs.getId() < rhs.getId();
}

// help from https://www.tutorialspoint.com/cplusplus/input_output_operators_overloading.htm
ostream operator<<(ostream &output,const City &city) {
    output << setw(23) << left << city.getName();
    output << setw(5)  << right << city.getState_id();
    output << setw(10) << fixed << setprecision(3) << city.getLocation().lat;
    output << setw(12) << city.getLocation().lng;
    output << setw(12) << city.getPopulation();
    output << setw(10) << city.getDensity();
    output << setw(10) << city.getId() << endl;
}

bool operator==(const City &lhs, const City &rhs) {
    if (lhs.getId() == rhs.getId()) {
        return true;
    }
    return false;
}

void importCities(string filename, vector<City> &cities) {
    // open database file
    ifstream f_in;
    f_in.open(filename);
    if (!f_in) {
        cout << "Could not open file " << filename;
    }

    // declare a variable for each attribute
    string city;
    string state_id;
    Location location;
    int population;
    double density;
    int id;
    char charJunk;
    string strJunk;

    // read from the file to variables. skip first line
    getline(f_in,strJunk);
    // while file stream is in good state and next char is not end of file
    while (f_in && f_in.peek() != EOF) {
        // store each variable, skipping commas and newline characters
        getline(f_in, city, ',');
        getline(f_in, state_id, ',');
        f_in >> location.lat >> charJunk >> location.lng >> charJunk
             >> population >> charJunk >> density
             >> charJunk >> id;
        if (!f_in) {
            f_in.clear();
        }
        getline(f_in,strJunk);

        // store each city into the cities array
        cities.push_back(City(city,state_id,location,population,density,id));
    }

    f_in.close();
}

void displayCities(const vector<City> &cities) {

    // output header row
    cout << setw(23) << left << endl << "City";
    cout << setw(5)  << right << "State";
    cout << setw(10) << "Latitude";
    cout << setw(12) << "Longitude";
    cout << setw(12) << "Population";
    cout << setw(10) << "Density";
    cout << setw(10) << "ID" << endl;

    // output info for each city
    for (City city : cities) {
        cout << setw(23) << left << city.getName();
        cout << setw(5)  << right << city.getState_id();
        cout << setw(10) << fixed << setprecision(3) << city.getLocation().lat;
        cout << setw(12) << city.getLocation().lng;
        cout << setw(12) << city.getPopulation();
        cout << setw(10) << city.getDensity();
        cout << setw(10) << city.getId() << endl;
    }
}

double calculateAvgPop(const vector<City> &cities) {
    double totalSum = 0;
    int count = 0;
    for (City city : cities) {
        totalSum += city.getPopulation();
        ++count;
    }
    return (totalSum / count);
}

void createIntFiles(const vector<City> &cities) {
    // create 3 integer files
    ofstream intFile1;
    ofstream intFile2;
    ofstream intFile3;
    intFile1.open("intFile1.csv");
    intFile2.open("intFile2.csv");
    intFile3.open("intFile3.csv");

    vector<int> intFile2Vector;

    for (int i = 0; i < cities.size(); ++i) {
        intFile1 << i << endl;
        intFile3 << i/5 << endl;
        intFile2Vector.push_back(i);
    }
    // random shuffle from http://www.cplusplus.com/reference/algorithm/random_shuffle/
    random_shuffle(intFile2Vector.begin(),intFile2Vector.end());
    for (int i : intFile2Vector) {
        intFile2 << i << endl;
    }
    intFile1.close();
    intFile2.close();
    intFile3.close();
}

vector<int> createIntVectorFromFile(string intFileName) {
    // open the intFile
    ifstream f_in;
    f_in.open(intFileName);
    if (!f_in) {
        cout << "Could not open file " << intFileName;
    }

    // declare an integer, a vector to store the integers, and a junk string
    int n;
    vector<int> intVector;
    string strJunk;
    // while file stream is in good state and next char is not end of file
    while (f_in && f_in.peek() != EOF) {
        // store the line into an integer
        f_in >> n;
        if (!f_in) {
            f_in.clear();
        }
        getline(f_in,strJunk);

        // store the integer into the intVector
        intVector.push_back(n);
    }
    f_in.close();
    return intVector;
}

void recordDepthsBST(BinarySearchTree<City>& tree,const vector<City>& cities) {
    // call helper function to create int vector from file
    vector<int> intVector1 = createIntVectorFromFile("intFile1.csv");
    vector<int> intVector2 = createIntVectorFromFile("intFile2.csv");
    vector<int> intVector3 = createIntVectorFromFile("intFile3.csv");

    // open result file for write
    ofstream bstIntFile1;
    ofstream bstIntFile2;
    ofstream bstIntFile3;
    bstIntFile1.open("bstIntFile1.csv");
    bstIntFile2.open("bstIntFile2.csv");
    bstIntFile3.open("bstIntFile3.csv");


    // search for each index in intVector, output depth to file
    for (int findIndex : intVector1) {
        bstIntFile1 << tree.find(cities[findIndex]).second << endl;
    } for (int findIndex : intVector2) {
        bstIntFile2 << tree.find(cities[findIndex]).second << endl;
    } for (int findIndex : intVector3) {
        bstIntFile3 << tree.find(cities[findIndex]).second << endl;
    }


    bstIntFile1.close();
    bstIntFile2.close();
    bstIntFile3.close();
}

void recordDepthsAVL(AVLTree<City>& tree, const vector<City>& cities) {
    // call helper function to create int vector from file
    vector<int> intVector1 = createIntVectorFromFile("intFile1.csv");
    vector<int> intVector2 = createIntVectorFromFile("intFile2.csv");
    vector<int> intVector3 = createIntVectorFromFile("intFile3.csv");

    // open result file for write
    ofstream avlIntFile1;
    ofstream avlIntFile2;
    ofstream avlIntFile3;
    avlIntFile1.open("avlIntFile1.csv");
    avlIntFile2.open("avlIntFile2.csv");
    avlIntFile3.open("avlIntFile3.csv");


    // search for each index in intVector, output depth to file
    for (int findIndex : intVector1) {
        avlIntFile1 << tree.find(cities[findIndex]).second << endl;
    } for (int findIndex : intVector2) {
        avlIntFile2 << tree.find(cities[findIndex]).second << endl;
    } for (int findIndex : intVector3) {
        avlIntFile3 << tree.find(cities[findIndex]).second << endl;
    }


    avlIntFile1.close();
    avlIntFile2.close();
    avlIntFile3.close();
}

void recordDepthsSPL(SplayTree<City>& tree,const vector<City>& cities) {
    // call helper function to create int vector from file
    vector<int> intVector1 = createIntVectorFromFile("intFile1.csv");
    vector<int> intVector2 = createIntVectorFromFile("intFile2.csv");
    vector<int> intVector3 = createIntVectorFromFile("intFile3.csv");

    // open result file for write
    ofstream splIntFile1;
    ofstream splIntFile2;
    ofstream splIntFile3;
    splIntFile1.open("splIntFile1.csv");
    splIntFile2.open("splIntFile2.csv");
    splIntFile3.open("splIntFile3.csv");


    // search for each index in intVector, output depth to file
    pair<bool,int> splayInfo;
    for (int findIndex : intVector1) {
        splayInfo = tree.find(cities[findIndex]);
        splIntFile1 << splayInfo.second << endl;
    } for (int findIndex : intVector2) {
        splayInfo = tree.find(cities[findIndex]);
        splIntFile2 << splayInfo.second << endl;
    } for (int findIndex : intVector3) {
        splayInfo = tree.find(cities[findIndex]);
        splIntFile3 << splayInfo.second << endl;
    }


    splIntFile1.close();
    splIntFile2.close();
    splIntFile3.close();
}

void recordInfo(BinarySearchTree<City> &citiesBST, AVLTree<City> &citiesAVL, SplayTree<City> &citiesSPLAY,
                vector<City> &cities) {
    // open and set up file for timed results
    ofstream additionalMetrics;
    additionalMetrics.open("additionalMetrics.csv");
    additionalMetrics << "tree,time,unit" << endl;

    // bst
    auto t1 = Clock::now();
    recordDepthsBST(citiesBST,cities);
    auto t2 = Clock::now();
    additionalMetrics << "bst," << chrono::duration_cast<chrono::microseconds>(t2 - t1).count()
         << ",microseconds" << endl;

    // avl
    t1 = Clock::now();
    recordDepthsAVL(citiesAVL,cities);
    t2 = Clock::now();
    additionalMetrics << "avl," << chrono::duration_cast<chrono::microseconds>(t2 - t1).count()
         << ",microseconds" << endl;

    // record splay and time it
    t1 = Clock::now();
    recordDepthsSPL(citiesSPLAY,cities);
    t2 = Clock::now();
    additionalMetrics << "splay," << chrono::duration_cast<chrono::microseconds>(t2 - t1).count()
         << ",microseconds" << endl;

    additionalMetrics.close();

}





