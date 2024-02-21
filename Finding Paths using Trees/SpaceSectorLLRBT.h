#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

class SpaceSectorLLRBT {
public:
    Sector* root;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    Sector* insert(Sector* sector, int x, int y, int z);
    void displaySectorsInOrder();
    void inorder(Sector* sector);
    void displaySectorsPreOrder();
    void preorder(Sector* sector);
    void displaySectorsPostOrder();
    void postorder(Sector* sector);
    bool inVector(std::vector<Sector*>& vector, Sector* member);
    Sector* findSector(Sector* sector, std::string value);
    std::vector<Sector*> findPath(const std::string& sector_code);
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);

    std::vector<Sector*> allSectors;
};

#endif // SPACESECTORLLRBT_H
