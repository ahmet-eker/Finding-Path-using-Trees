#include "SpaceSectorBST.h"

using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    for(int i = 0; i< allSectors.size(); i++){
        Sector* sector = allSectors[i];
        delete sector;
    }
    // Free any dynamically allocated memory in this class.
}

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {

    string filePath = filename;
    ifstream inputFile(filePath);

    vector<string> sectors_strings;
    string line;
    while (std::getline(inputFile, line)) {
        if(line.find_first_of("\r") != std::string::npos){
            line.pop_back();
        }
        sectors_strings.push_back(line);
    }
    if (!sectors_strings.empty()) {
        sectors_strings.erase(sectors_strings.begin());
    }
    inputFile.close();

    for(int i = 0; i < sectors_strings.size(); i++){
        std::istringstream iss(sectors_strings[i]);

        std::string part1, part2, part3;
        std::getline(iss, part1, ',');
        std::getline(iss, part2, ',');
        std::getline(iss, part3, ',');

        int Xint = std::stoi(part1);
        int Yint = std::stoi(part2);
        int Zint = std::stoi(part3);

        insertSectorByCoordinates(Xint, Yint, Zint);

    }

    // TODO: read the sectors from the input file and insert them into the BST sector map
    // according to the given comparison critera based on the sector coordinates.
}

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {

    if(root == nullptr){
        Sector *newSector = new Sector(x, y, z);
        allSectors.push_back(newSector);
        root = newSector;
    } else{
        insert(root, x, y, z);
    }

    // Instantiate and insert a new sector into the space sector BST map according to the 
    // coordinates-based comparison criteria.
}


Sector* SpaceSectorBST::insert(Sector* sector, int x, int y, int z) {
    if (sector == nullptr) {
        Sector *newSector = new Sector(x, y, z);
        allSectors.push_back(newSector);
        return newSector;
    }

    if (x < sector->x) {
        sector->left = insert(sector->left, x, y, z);
    } else if (x > sector->x) {
        sector->right = insert(sector->right, x, y, z);
    } else {
        if (y < sector->y) {
            sector->left = insert(sector->left, x, y, z);
        } else if (y > sector->y) {
            sector->right = insert(sector->right, x, y, z);
        } else {
            if (z < sector->z) {
                sector->left = insert(sector->left, x, y, z);
            } else if (z > sector->z) {
                sector->right = insert(sector->right, x, y, z);
            }
        }
    }

    return sector;
}



void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    // TODO: Delete the sector given by its sector_code from the BST.
}

void SpaceSectorBST::displaySectorsInOrder() {
    std::cout << "Space sectors inorder traversal:" << std::endl;
    inorder(root);
    std::cout << std::endl;
    // TODO: Traverse the space sector BST map in-order and print the sectors 
    // to STDOUT in the given format.
}

void SpaceSectorBST::inorder(Sector* sector){
    if (sector == nullptr) {
        return;
    }
    inorder(sector->left);
    std::cout << sector->sector_code << std::endl;
    inorder(sector->right);
}


void SpaceSectorBST::displaySectorsPreOrder() {
    std::cout << "Space sectors preorder traversal:" << std::endl;
    preorder(root);
    std::cout << std::endl;
    // TODO: Traverse the space sector BST map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
}


void SpaceSectorBST::preorder(Sector* sector){
    if (sector == nullptr) {
        return;
    }
    std::cout << sector->sector_code << std::endl;
    preorder(sector->left);
    preorder(sector->right);
}


void SpaceSectorBST::displaySectorsPostOrder() {
    std::cout << "Space sectors postorder traversal:" << std::endl;
    postorder(root);
    std::cout << std::endl;
    // TODO: Traverse the space sector BST map in post-order traversal and print
    // the sectors to STDOUT in the given format.
}


void SpaceSectorBST::postorder(Sector* sector){
    if (sector == nullptr) {
        return;
    }
    postorder(sector->left);
    postorder(sector->right);
    std::cout << sector->sector_code << std::endl;
}


Sector* SpaceSectorBST::findSector(Sector* sector, string value) {

    if (sector == nullptr || sector->sector_code == value) {
        return sector;
    }

    Sector* left = findSector(sector->left, value);
    if(left == nullptr){
        return findSector(sector->right, value);
    } else{
        return left;
    }
}


std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    Sector* theSector = findSector(root, sector_code);
    if(theSector == nullptr){
        std::cout << "A path to Dr. Elara could not be found." << std::endl;
        return path;
    }
    path.push_back(root);
    Sector* control = root;

    while(control->sector_code != sector_code){
        if (theSector->x < control->x) {
            control = control->left;
        } else if (theSector->x > control->x) {
            control = control->right;
        } else if (theSector->x == control->x & theSector->y < control->y) {
            control = control->left;
        } else if (theSector->x == control->x & theSector->y > control->y) {
            control = control->right;
        } else if (theSector->x == control->x & theSector->y == control->y & theSector->z < control->z) {
            control = control->left;
        } else if (theSector->x == control->x & theSector->y == control->y & theSector->z > control->z) {
            control = control->right;
        }
        path.push_back(control);
    }

    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    return path;
}


void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
    if(path.size() == 0){
        return;
    }
    std::cout << "The stellar path to Dr. Elara: ";

    for(int i = 0; i < path.size(); i++){
        if(i != path.size()-1){
            std::cout << path[i]->sector_code << "->";
        } else{
            std::cout << path[i]->sector_code << std::endl;
        }
    }

    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.
}


