#include "Solution.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <fstream>

S01 S01::_solution;

using namespace std;

vector<int> dist;  // The distance of some animal to root of the set it is in
vector<int> path;  // The path of some animal to root of the set it is in

int findRoot(int animal) {
    // IF {animal} is not the root of the set:
    if (path[animal] != animal) {
        int temp = findRoot(path[animal]);   // Find root
        dist[animal] += dist[path[animal]];  // Upadate distance
        path[animal] = temp;                 // Fold the path
    }
    return path[animal];
}

int S01::solve(const std::string& fileLoc) const {
    ifstream fileIn(fileLoc);                     // Create an ifstream instance with file in {fileLoc}
    if (!fileIn.is_open()) return -1;             // Failed to open the file

    int numOfAnimals, numOfPropositions;
    fileIn >> numOfAnimals >> numOfPropositions;  // Read number of animals and propositions
    dist.resize((size_t)numOfAnimals + 1, 0);
    path.resize((size_t)numOfAnimals + 1);
    iota(path.begin(), path.end(), 0);            // Initialize the vector with each element's index

    int numOfFake{ 0 };

    while (numOfPropositions--)
    {
        int option;
        int animalX, animalY;
        fileIn >> option >> animalX >> animalY;   // Read option and animals

        // IF either animal is out of range:
        if (animalX > numOfAnimals || animalX < 0 || animalY > numOfAnimals || animalY < 0) {
            numOfFake++;  // Must be fake
            continue;     // Go to next loop
        }

        int rootX = findRoot(animalX);  // Root of the set {animalX} is in
        int rootY = findRoot(animalY);  // Root of the set {animalY} is in

        switch (option) {
        case 1: {  // Proposition says {animalX} and {animalY} have no predation relationship
            // [Note]---------------------------------------------------------------------------
            // | When two animals are in the same set, their 'root' shoule be the same.
            // |
            // | Moreover, if the DIFFERENCE VALUE of the DISTANCEs between the two animals and
            // | their common 'root' is an integral multiple of 3, it can be sure that the two
            // | shares no predation relationship.
            // +--------------------------------------------------------------------------------
            // IF {animalX} and {animalY} are in the same set, and they do share
            // a predation relationship ({(dist[animalX] - dist[animalY]) % 3} is not zero):
            if (rootX == rootY && (dist[animalX] - dist[animalY]) % 3 != 0) { numOfFake++; }
            // ELSE IF {animalX} and {animalY} are not in the same set:
            else if (rootX != rootY) {
                path[rootX] = rootY;  // Merge set of {animalX} to set of {animalY}
                dist[rootX] = dist[animalY] - dist[animalX];  // Update the distance of {rootX}
            }
            break;
        }
        case 2: { // Proposition says {animalX} is a predator of {animalY}
            // IF {animalX} and {animalY} are in the same set, and  {animalX} is not the predator
            // of {animalY}:
            if (rootX == rootY && (dist[animalX] - dist[animalY] - 1) % 3 != 0) { numOfFake++; }
            // ELSE IF the 2 are not in the same set:
            else if (rootX != rootY) {
                path[rootX] = rootY;  // Merge set of {animalX} to set of {animalY}
                dist[rootX] = dist[animalY] + 1 - dist[animalX];  // Update the distance of {rootY}
            }
            break;
        }
        default: break;
        }
    }
    fileIn.close();
    return numOfFake;
}