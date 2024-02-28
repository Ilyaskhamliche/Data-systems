#include <iostream>
#include <sqlite3.h>

// Function to execute SQL query
int executeQuery(sqlite3* db, const char* query) {
    char* errMsg;
    int result = sqlite3_exec(db, query, 0, 0, &errMsg);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    return result;
}

// Function to display menu options
void displayMenu() {
    std::cout << "NBA Database Menu\n";
    std::cout << "1. View teams in a division\n";
    std::cout << "2. Add a new team\n";
    std::cout << "3. Add a new player\n";
    std::cout << "4. View roster for a team\n";
    std::cout << "5. View game information\n";
    std::cout << "6. Add game information\n";
    std::cout << "7. Exit\n";
}

// Function to view teams in a division
void viewTeamsInDivision(sqlite3* db) {
    int divisionID;
    std::cout << "Enter Division ID: ";
    std::cin >> divisionID;

    // Execute SQL query to retrieve teams in the specified division
    std::string query = "SELECT Name FROM Team WHERE Division_ID = " + std::to_string(divisionID);
    executeQuery(db, query.c_str());
}

// Function to add a new team
void addNewTeam(sqlite3* db) {
    std::string name, mascot, city, state, arena;
    int divisionID, coachID;

    std::cout << "Enter Team Name: ";
    std::cin >> name;
    std::cout << "Enter Mascot: ";
    std::cin >> mascot;
    std::cout << "Enter City: ";
    std::cin >> city;
    std::cout << "Enter State: ";
    std::cin >> state;
    std::cout << "Enter Arena: ";
    std::cin >> arena;
    std::cout << "Enter Division ID: ";
    std::cin >> divisionID;
    std::cout << "Enter Coach ID: ";
    std::cin >> coachID;

    // Execute SQL query to insert a new team into the database
    std::string query = "INSERT INTO Team (Name, Mascot, City, State, Arena, Division_ID, Coach_ID) VALUES ('" + name + "', '" + mascot + "', '" + city + "', '" + state + "', '" + arena + "', " + std::to_string(divisionID) + ", " + std::to_string(coachID) + ")";
    executeQuery(db, query.c_str());
}

// Function to add a new player
void addNewPlayer(sqlite3* db) {
    std::string firstName, lastName;
    int number, teamID;

    std::cout << "Enter First Name: ";
    std::cin >> firstName;
    std::cout << "Enter Last Name: ";
    std::cin >> lastName;
    std::cout << "Enter Number: ";
    std::cin >> number;
    std::cout << "Enter Team ID: ";
    std::cin >> teamID;

    // Execute SQL query to insert a new player into the database
    std::string query = "INSERT INTO Player (First_Name, Last_Name, Number, Team_ID) VALUES ('" + firstName + "', '" + lastName + "', " + std::to_string(number) + ", " + std::to_string(teamID) + ")";
    executeQuery(db, query.c_str());
}

// Function to view roster for a team
void viewRosterForTeam(sqlite3* db) {
    int teamID;
    std::cout << "Enter Team ID: ";
    std::cin >> teamID;

    // Execute SQL query to retrieve roster for the specified team
    std::string query = "SELECT First_Name, Last_Name, Number FROM Player WHERE Team_ID = " + std::to_string(teamID);
    executeQuery(db, query.c_str());
}

// Function to view game information
void viewGameInformation(sqlite3* db) {
    // Execute SQL query to retrieve game information
    std::string query = "SELECT * FROM Game";
    executeQuery(db, query.c_str());
}

// Function to add game information
void addGameInformation(sqlite3* db) {
    std::string dateTime;
    int homeTeamID, awayTeamID, homeTeamScore, awayTeamScore;

    std::cout << "Enter Date/Time (YYYY-MM-DD HH:MM:SS): ";
    std::cin >> dateTime;
    std::cout << "Enter Home Team ID: ";
    std::cin >> homeTeamID;
    std::cout << "Enter Away Team ID: ";
    std::cin >> awayTeamID;
    std::cout << "Enter Home Team Score: ";
    std::cin >> homeTeamScore;
    std::cout << "Enter Away Team Score: ";
    std::cin >> awayTeamScore;

    // Execute SQL query to insert game information into the database
    std::string query = "INSERT INTO Game (Date_Time, Home_Team_ID, Away_Team_ID, Home_Team_Score, Away_Team_Score) VALUES ('" + dateTime + "', " + std::to_string(homeTeamID) + ", " + std::to_string(awayTeamID) + ", " + std::to_string(homeTeamScore) + ", " + std::to_string(awayTeamScore) + ")";
    executeQuery(db, query.c_str());
}

int main() {
    sqlite3* db;
    int rc = sqlite3_open("nba_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1: {
                viewTeamsInDivision(db);
                break;
            }
            case 2: {
                addNewTeam(db);
                break;
            }
            case 3: {
                addNewPlayer(db);
                break;
            }
            case 4: {
                viewRosterForTeam(db);
                break;
            }
            case 5: {
                viewGameInformation(db);
                break;
            }
            case 6: {
                addGameInformation(db);
                break;
            }
            case 7: {
                std::cout << "Exiting program.\n";
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    } while (choice != 7);

    sqlite3_close(db);
    return 0;
}
