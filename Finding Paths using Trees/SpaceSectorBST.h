#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

#include "Sector.h"

class SpaceSectorBST {
  
public:
    Sector *root;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void readSectorsFromFile(const std::string& filename); 
    void insertSectorByCoordinates(int x, int y, int z);
    Sector* insert(Sector* sector, int x, int y, int z);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void inorder(Sector* sector);
    void displaySectorsPreOrder();
    void preorder(Sector* sector);
    void displaySectorsPostOrder();
    void postorder(Sector* sector);
    Sector* findSector(Sector* sector, std::string value);
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);

    std::vector<Sector*> allSectors;
};

#endif // SPACESECTORBST_H
