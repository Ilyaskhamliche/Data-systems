#include <fstream>
#include <string>
#include <iostream>

struct Pet {
    std::string name;
    std::string species;
    std::string breed;
    std::string color;
};

int main() {
    int choice;

    std::ofstream outFile("pet_data.txt", std::ios::app);  // Opens file for writing w/o erasing current contents
    std::ifstream inFile("pet_data.txt");  // Open file for reading

    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add a pet\n";
        std::cout << "2. View pets\n";
        std::cout << "3. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Pet newPet;

                std::cout << "Enter pet's name: ";
                std::cin >> newPet.name;

                std::cout << "Enter pet's species: ";
                std::cin >> newPet.species;

                std::cout << "Enter pet's breed: ";
                std::cin >> newPet.breed;

                std::cout << "Enter pet's color: ";
                std::cin >> newPet.color;

                // pet record to the file
                outFile << newPet.name << " " << newPet.species << " " << newPet.breed << " " << newPet.color << std::endl;
                std::cout << "Pet added successfully!\n";
                break;
            }

            case 2: {
                std::string petRecord;

                // Read and print all pet records from the file
                std::cout << "List of pets:\n";
                while (std::getline(inFile, petRecord)) {
                    std::cout << petRecord << std::endl;
                }
                break;
            }

            case 3:
                std::cout << "Exiting program.\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 3);

    outFile.close();
    inFile.close();

    return 0;
}
