#include <iostream>
#include <fstream>
#include <vector>

void replaceCSV(const std::string& sourceFile, const std::string& targetFile) {

    std::ifstream source(sourceFile);  // Automatically opens the source file
    std::ofstream target(targetFile);  // Automatically opens the target file

    std::string line;
    while (getline(source, line)) {
        target << line << std::endl;
    }

    source.close();  // Close the source file
    target.close();  // Close the target file
}


int main() {
    // reset geometry and forces
    replaceCSV("geometryOrig.csv","geometry.csv");
    replaceCSV("forcesOrig.csv","forces.csv");
    // define geometry 
        // consider making this function so vars get deleted sooner
        // open file
        std::ofstream geometry;
        geometry.open("geometry.csv", std::ios_base::app);
        // write geometry
        std::cout << "How many points (excluding the origin) are there?: ";
        int numPoints;
        std::cin >> numPoints;
        // skip this if no points
        std::cout << "Enter names of points in order of entry, comma seperated: ";
        std::string pointOrder;
        std::cin.ignore();
        getline(std::cin, pointOrder);
        std::cout << std::endl;
        

        std::vector<double> tempVect{0,0}; // x y
        for (int i =  1; i <= numPoints; i++) {
            std::cout << "For point " << pointOrder.at(2*i - 2) << ", enter following: \n";
            // add option to chose what point to reference // also to select unknown
            std::cout << "x-dist from origin: ";
            std::cin >> tempVect[0];
            std::cout << std::endl;
            std::cout << "y-dist from origin: ";
            std::cin >> tempVect[1];
            std::cout << std::endl;

            // actually write
            geometry << pointOrder.at(2*i - 2) << "," << tempVect[0] << "," << tempVect[1] << std::endl;

            // reset temp vect
            tempVect = {0,0};
        }
        geometry.close();

    // define forces
        // include more types later, rn only when know components fx,fy,d_point,theta,N,d_point,xslopeTri,yslopeTri,N,d_point
        // also include option to select distance from point
        // also add distance option to have distance from A on beam AB in the hypotneuse direction
        std::ofstream forces;
        forces.open("forces.csv", std::ios_base::app);
        std::cout << "How many forces: ";
        int numForces;
        std::cin >> numForces;
        //std::vector<std::string> forceInfo(numForces,4);  // Changed to string to handle unknowns
        std::string forceInfo[numForces][4];
    
    for (int i = 0; i < numForces; i++) {
        std::cout << "For force " << i << " of " <<numForces<< ", enter the following (use '?' for unknown values): \n";
        // add option to choose what point to reference
        std::cout << "x-component: ";
        std::cin >> forceInfo[i][0];
        std::cout << std::endl;
        
        std::cout << "y-component: ";
        std::cin >> forceInfo[i][1];
        std::cout << std::endl;

        std::cout << "x-distance from origin: ";
        std::cin >> forceInfo[i][2];
        std::cout << std::endl;

        std::cout << "y-distance from origin: ";
        std::cin >> forceInfo[i][3];
        std::cout << std::endl;

        

        // Reset the vector
        //forceInfo = {"?", "?", "?", "?"};  // Initialize with '?' to show unknowns if the user wants
    }
    // try random, loop through to check value does exist in csv, value using to third line of numLines
    int unknownSignifier = rand() % 1000; // this is risky, fix this pls or else results will sometimes be bad

    for (int i = 0; i < numForces; i++) {
        for (int j = 0; j < 4; j++) {
            if (forceInfo[i][j] == "?") {
                forceInfo[i][j] = std::to_string(unknownSignifier);
            }
        }
    }


    // Write to the CSV file THIS ISNT RIGHT RN
    for (int i = 0; i < numForces; i++) {
        forces << forceInfo[i][0] << "," << forceInfo[i][1] << "," << forceInfo[i][2] << "," << forceInfo[i][3] << "," << std::endl;
    }
    forces.close();

    // deal with number of lines
    std::ofstream nLines;
    nLines.open("numLines.txt",std::ios_base::trunc);
    nLines << numForces << std::endl << numPoints << std::endl << unknownSignifier;

    
    return 0;
}