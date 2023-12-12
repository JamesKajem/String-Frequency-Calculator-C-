#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <limits>

//Function for menu display
void displayMenu() {
    std::cout << "\nMenu Options:\n"
              << "1 - Search for a specific item \n"
              << "2 - Retrieve all items \n"
              << "3 - Retrieve Histogram of all items \n"
              << "4 - Exit Program and Save Data \n";
}

//Function making strings lowercase, to avoid case insenitivies from behalf of user
std::string toLowercase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function for printing the list, formatted by frequency.
// This is the format that is saved in frequency.dat and displayed for menu 2, so I made it its own function
void frequencyList(const std::map<std::string, int>& itemFrequency) {
    std::cout << "\nList with the frequency of all items:\n";
    for (const auto& pair : itemFrequency) {
        std::cout << pair.first << " " << pair.second << "\n";
    }
}

// Function for frequency.dat, this saves the frequency to the file
void saveDataToFile(const std::map<std::string, int>& itemFrequency) {
    //output file frequency.dat
    std::ofstream outputFile("frequency.dat");
    //Opens file
    if (outputFile.is_open()) {
        for (const auto& pair : itemFrequency) {
            outputFile << pair.first << " " << pair.second << "\n";
        }
        outputFile.close();
        std::cout << "Data saved to frequency.dat.\n";
    } else {
        //Error catch
        std::cerr << "Error: frequency.dat was not found.\n";
    }
}

//Main code line
int main() {
    //Input file is opened
    std::ifstream inputFile("CS210_Project_Three_Input_File.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: CS210_Project_Three_Input_File.txt was not found.\n";
        return 1;
    }

    //Reads the text provided by file
    std::string input, line;
    while (std::getline(inputFile, line)) {
        input += line + " ";
    }
    inputFile.close();

    //transforms string to lowercase
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    //'tokenizes' input string into seperate word variables
    std::stringstream ss(input);
    std::string word;
    //establishes frequency map variable
    std::map<std::string, int> itemFrequency;
    //Counts frequency of each word and stored to the map itemFrequency
    while (ss >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
        itemFrequency[word]++;
    }

    // Displays the initial welcome when program starts
    std::cout << "Welcome to Corner Grocer\n";
    std::cout << "Press Enter to Continue\n";

    int choice;
    do {
        // Clears any error messages and ignores invalid user input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        displayMenu();

        // Requests user input for menu choice
        std::cout << "Enter your choice (1-4): ";

        // Verification for user input
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        //user Inputs for menu choice are realized here
        switch (choice) {
            //Specific Item is searched for based on User Input
            case 1: {
                //Prompts for input
                std::string searchedItem;
                std::cout << "Enter the item you wish to look for: ";
                std::cin >> searchedItem;
                //lowercases input
                searchedItem = toLowercase(searchedItem);

                //searches for searchedItem frequency from previously established itemFrequency list
                auto iteration = itemFrequency.find(searchedItem);
                //If found, data is reported
                if (iteration != itemFrequency.end()) {
                    std::cout << "Frequency of '" << searchedItem << "': " << iteration->second << " times\n";
                } else {
                    //if input is not found
                    std::cout << "'" << searchedItem << "' not found in the input.\n";
                }
                break;
            }
            //Menu 2 is a list of every item's frequency using previously established frequency list function
            case 2:
                frequencyList(itemFrequency);
                break;
            //Menu 3 displays the itemFrequency list, but in the form of a histogram
            case 3:
                std::cout << "\nHistogram of Frequencies:\n";
                //Simple loop that assigns an asterick for each item iteration
                for (const auto& pair : itemFrequency) {
                    std::cout << pair.first << " ";
                    std::cout << std::string(pair.second, '*') << "\n";
                }
                break;
            //Exits program and saves data
            case 4:
                // Save frequency data to frequency.dat on exit
                saveDataToFile(itemFrequency);
                std::cout << "Exiting the program.\n";
                break;

            //catch for invalid numeric input
            default:
                std::cout << "Follow instruction\n";
        }

    } while (choice != 4);

    return 0;
}
