#include "SpaceSectorLLRBT.h"

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

int isRed(Sector* sector){
    if (sector == nullptr)
        return 0;

    return (sector->color == true);
}


void swapColors(Sector* sector1, Sector* sector2)
{
    bool temp = sector1 -> color;
    sector1 -> color = sector2 -> color;
    sector2 -> color = temp;
}

Sector* rotateLeft(Sector* sector)
{
    Sector* child = sector -> right;
    Sector* childLeft = child -> left;

    child->left = sector;
    sector->right = childLeft;

    return child;
}


Sector* rotateRight(Sector* sector)
{
    Sector* child = sector -> left;
    Sector* childRight = child -> right;

    child->right = sector;
    sector->left = childRight;

    return child;
}


void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {

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

    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
    // according to the given comparison critera based on the sector coordinates.
}

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    for(int i = 0; i< allSectors.size(); i++){
        Sector* sector = allSectors[i];
        delete sector;
    }
    // TODO: Free any dynamically allocated memory in this class.
}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {

    if(root == nullptr){
        Sector *newSector = new Sector(x, y, z);
        allSectors.push_back(newSector);
        root = newSector;
    } else{
        root = insert(root, x, y, z);
        root->color = false;
    }

    // TODO: Instantiate and insert a new sector into the space sector LLRBT map 
    // according to the coordinates-based comparison criteria.
}

Sector* SpaceSectorLLRBT::insert(Sector* sector, int x, int y, int z){

    if (sector == nullptr){
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

    if (isRed(sector -> right) && !isRed(sector -> left)){
        sector = rotateLeft(sector);
        swapColors(sector, sector->left);
    }

    if (isRed(sector->left) && isRed(sector->left->left)){
        sector = rotateRight(sector);
        swapColors(sector, sector -> right);
    }

    if (isRed(sector->left) && isRed(sector->right)){
        sector->color = !sector->color;

        sector->left -> color = false;
        sector->right -> color = false;
    }

    return sector;

}

void SpaceSectorLLRBT::displaySectorsInOrder() {
    std::cout << "Space sectors inorder traversal:" << std::endl;
    inorder(root);
    std::cout << std::endl;
    // TODO: Traverse the space sector LLRBT map in-order and print the sectors 
    // to STDOUT in the given format.
}

void SpaceSectorLLRBT::inorder(Sector* sector){
    if (sector == nullptr) {
        return;
    }
    string clr;
    if(sector->color){
        clr = "RED";
    }
    else{
        clr = "BLACK";
    }
    inorder(sector->left);
    std::cout << clr << " sector: " << sector->sector_code << std::endl;
    inorder(sector->right);
}

void SpaceSectorLLRBT::displaySectorsPreOrder() {
    std::cout << "Space sectors preorder traversal:" << std::endl;
    preorder(root);
    std::cout << std::endl;
    // TODO: Traverse the space sector LLRBT map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
}

void SpaceSectorLLRBT::preorder(Sector* sector){
    if (sector == nullptr) {
        return;
    }
    string clr;
    if(sector->color){
        clr = "RED";
    }
    else{
        clr = "BLACK";
    }
    std::cout << clr << " sector: " << sector->sector_code << std::endl;
    preorder(sector->left);
    preorder(sector->right);
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    std::cout << "Space sectors postorder traversal:" << std::endl;
    postorder(root);
    std::cout << std::endl;
    // TODO: Traverse the space sector LLRBT map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
}

void SpaceSectorLLRBT::postorder(Sector* sector){
    if (sector == nullptr) {
        return;
    }
    string clr;
    if(sector->color){
        clr = "RED";
    }
    else{
        clr = "BLACK";
    }
    postorder(sector->left);
    postorder(sector->right);
    std::cout << clr << " sector: " << sector->sector_code << std::endl;
}

Sector* SpaceSectorLLRBT::findSector(Sector* sector, string value) {

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


std::vector<Sector*> SpaceSectorLLRBT::findPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    Sector* theSector = findSector(root, sector_code);
    if(theSector == nullptr){
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

    return path;
}

bool SpaceSectorLLRBT::inVector(std::vector<Sector*>& vector, Sector* member) {
    for (int i = 0; i < vector.size(); i++) {
        if (member == vector[i]) {
            return true;
        }
    }
    return false;
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;

    std::vector<Sector*> path1 = findPath("0SSS");
    std::vector<Sector*> path2 = findPath(sector_code);

    if(path2.size() == 0){
        std::cout << "A path to Dr. Elara could not be found." << std::endl;
        return path;
    }

    bool isBreak = false;
    for(int i = path1.size()-1; i >= 0; i--){
        path.push_back(path1[i]);
        if(inVector(path2,path1[i])){
            break;
        }
    }

    for(int i = 0; i < path2.size(); i++){
        if(inVector(path1, path2[i])){
            continue;
        }
        path.push_back(path2[i]);

    }


    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    return path;
}

void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
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