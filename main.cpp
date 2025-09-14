#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

// Function to clear the terminal screen
void clearScreen() {
    cout << "\033[2J\033[H";
}

// Function to trim whitespace from a string
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

int main() {
    int lib_size;
    cout << "Enter number of boxes you have: ";
    cin >> lib_size;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    int book_number = 0;
    vector<vector<string>> Books(lib_size, vector<string>(8));
    
    // Initialize array
    for (int i = 0; i < lib_size; i++) {
        Books[i][7] = "hide";
    }
    
    int choice = 0;
    int index;
    string ID;
    string input;
    
    // Things we need to be entered
    vector<string> Entered_things = {"title", "author's name", "publication date", "publisher", " ", "description"};
    
    clearScreen();
    
    // Start the program's infinite runtime loop
    while (choice != 8) {
        cout << "Welcome to the Library Management System!" << endl;
        cout << "1.  Add a Book" << endl;
        cout << "2.  Search for a Book (by Title or ID)" << endl;
        cout << "3.  Issue a Book (by ID)" << endl;
        cout << "4.  Return a Book (by ID)" << endl;
        cout << "5.  Delete a Book (by ID)" << endl;
        cout << "6.  Edit a Book's details (Title/Description by ID)" << endl;
        cout << "7.  View all Books" << endl;
        cout << "8.  Exit" << endl;
        
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            // Adding a Books
            case 1: {
                clearScreen();
                if (book_number == lib_size) {
                    cout << "Sorry, the library is full" << endl;
                    int sub_choice;
                    do {
                        cout << "1.  Return to Main Menu" << endl;
                        cout << "2.  Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> sub_choice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        
                        if (sub_choice > 2 || sub_choice < 1) {
                            cout << "Invalid Choice (1 - 2)" << endl;
                        } else if (sub_choice == 2) {
                            return 0;
                        }
                    } while (sub_choice > 2 || sub_choice < 1);
                    
                    if (sub_choice == 1) {
                        clearScreen();
                        continue;
                    }
                }
                
                // Ask user for all details except ID and availability
                for (int i = 0; i < 6; i++) {
                    // Initialize the availability index
                    if (i == 4) {
                        Books[book_number][5] = "Available";
                        continue;
                    }
                    
                    string input_without_spaces = "";
                    do {
                        cout << "Enter the " << Entered_things[i] << ": ";
                        getline(cin, input);
                        
                        input_without_spaces = trim(input);
                        if (!input_without_spaces.empty()) {
                            Books[book_number][i + 1] = input;
                        } else {
                            cout << "Please enter a real " << Entered_things[i] << endl;
                        }
                    } while (input_without_spaces.empty());
                }
                
                // Set ID to Books number after all info is correct
                Books[book_number][0] = to_string(book_number + 1);
                cout << "Book successfully added" << endl;
                Books[book_number][7] = "show";
                book_number++;
                
                int sub_choice;
                do {
                    cout << "1.  Return to Main Menu" << endl;
                    cout << "2.  Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> sub_choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    if (sub_choice > 2 || sub_choice < 1) {
                        cout << "Invalid Choice (1 - 2)" << endl;
                    } else if (sub_choice == 2) {
                        return 0;
                    }
                } while (sub_choice > 2 || sub_choice < 1);
                
                clearScreen();
                break;
            }
            
            // Searching for a Book
            case 2: {
                clearScreen();
                // checking if there is any book in the library
                if (book_number == 0) {
                    cout << "There are no books in the library" << endl;
                    int sub_choice;
                    do {
                        cout << "1.  Return to Main Menu" << endl;
                        cout << "2.  Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> sub_choice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        
                        if (sub_choice > 2 || sub_choice < 1) {
                            cout << "Invalid Choice (1 - 2)" << endl;
                        } else if (sub_choice == 2) {
                            return 0;
                        }
                    } while (sub_choice > 2 || sub_choice < 1);
                    
                    if (sub_choice == 1) {
                        clearScreen();
                        continue;
                    }
                }
                
                // if there are books in the library
                cout << "Enter ID or title to find the book: ";
                string ID_or_title;
                getline(cin, ID_or_title);
                
                // declare a flag will be equal to the book row if we found the book in our library
                int book_row = -1;
                for (int i = 0; i < book_number; i++) {
                    if (ID_or_title == Books[i][0]) {
                        book_row = i;
                        break;
                    }
                    if (ID_or_title == Books[i][1]) {
                        book_row = i;
                        break;
                    }
                }
                
                if (book_row != -1 && Books[book_row][7] == "hide") {
                    book_row = -1;
                }
                
                if (book_row != -1) {
                    clearScreen();
                    // char lengths: ID 11, Title 42, Author 28, Availability 100
                    cout << " ID        | Title                                  | Author                     | Availability " << endl;
                    cout << "------------------------------------------------------------------------------------------------" << endl;
                    
                    // Print the Book id
                    cout << " " << Books[book_row][0];
                    for (int j = 0; j < (10 - (int) Books[book_row][0].length()); j++) {
                        cout << " ";
                    }
                    cout << "|";
                    
                    // Print Title and fill the remaining blank with whitespace
                    cout << " " << Books[book_row][1];
                    for (int j = 0; j < (39 - (int) Books[book_row][1].length()); j++) {
                        cout << " ";
                    }
                    cout << "|";
                    
                    // Print Author and fill the blank with whitespace
                    cout << " " << Books[book_row][2];
                    for (int j = 0; j < (27 - (int) Books[book_row][2].length()); j++) {
                        cout << " ";
                    }
                    cout << "|";
                    
                    // Print Additional Info
                    cout << " " << Books[book_row][5] << endl;
                    cout << "           - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -          " << endl;
                    cout << " Publication Date: " << Books[book_row][3] << endl;
                    cout << " Publisher: " << Books[book_row][4] << endl;
                    cout << " Description: " << endl;
                    cout << " ";
                    
                    // Print Description and only move to the next line after 90 characters and the word is finished
                    string description = Books[book_row][6];
                    for (size_t j = 0; j < description.length(); j++) {
                        cout << description[j];
                        if ((j + 1) % 90 == 0) {
                            for (size_t k = j + 1; k < description.length(); k++) {
                                cout << description[k];
                                if (description[k] == ' ') {
                                    j = k;
                                    break;
                                }
                                j = k;
                            }
                            cout << endl;
                        }
                    }
                    cout << endl;
                    cout << "------------------------------------------------------------------------------------------------" << endl;
                    
                    int sub_choice;
                    do {
                        cout << "1.  Return to Main Menu" << endl;
                        cout << "2.  Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> sub_choice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        
                        if (sub_choice > 2 || sub_choice < 1) {
                            cout << "Invalid Choice (1 - 2)" << endl;
                        } else if (sub_choice == 2) {
                            return 0;
                        }
                    } while (sub_choice > 2 || sub_choice < 1);
                    
                    clearScreen();
                } else {
                    cout << "Not found !" << endl;
                }
                break;
            }
            
            // Issue a Book
            case 3: {
                clearScreen();
                cout << "Enter ID: ";
                cin >> ID;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                index = -1;
                
                for (int i = 0; i < book_number; i++) {
                    if (Books[i][7] == "show" && Books[i][0] == ID) {
                        index = i;
                        break;
                    }
                }
                
                if (index < 0) {
                    cout << "ID not found" << endl;
                    int sub_choice;
                    do {
                        cout << "1.  Return to main menu" << endl;
                        cout << "2.  Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> sub_choice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        
                        if (sub_choice > 2 || sub_choice < 1) {
                            cout << "Invalid choice (1 - 2)" << endl;
                        } else if (sub_choice == 2) {
                            return 0;
                        }
                    } while (sub_choice > 2 || sub_choice < 1);
                    
                    clearScreen();
                    break;
                }
                
                if (Books[index][5] == "Available") {
                    Books[index][5] = "Unavailable";
                    cout << "\"" << Books[index][1] << "\" has been successfully issued." << endl;
                } else {
                    cout << "the book is currently unavailable" << endl;
                }
                
                int sub_choice;
                do {
                    cout << "1.  Return to Main Menu" << endl;
                    cout << "2.  Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> sub_choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    if (sub_choice > 2 || sub_choice < 1) {
                        cout << "Invalid Choice (1 - 2)" << endl;
                    } else if (sub_choice == 2) {
                        return 0;
                    }
                } while (sub_choice > 2 || sub_choice < 1);
                
                clearScreen();
                break;
            }
            
            // Return a Book
            case 4: {
                clearScreen();
                cout << "Enter ID: ";
                cin >> ID;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                index = -1;
                
                // Search linearly for ID and if it matches and isn't hidden then return the ID
                for (int i = 0; i < book_number; i++) {
                    if (Books[i][7] == "show" && Books[i][0] == ID) {
                        index = i;
                        break;
                    }
                }
                
                if (index < 0) {
                    cout << "ID Not found" << endl;
                    break;
                }
                
                if (Books[index][5] == "Unavailable") {
                    Books[index][5] = "Available";
                    cout << "\"" << Books[index][1] << "\" has been successfully returned." << endl;
                } else {
                    cout << "This book is already available" << endl;
                }
                
                int sub_choice;
                do {
                    cout << "1.  Return to main menu" << endl;
                    cout << "2.  Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> sub_choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    if (sub_choice > 2 || sub_choice < 1) {
                        cout << "Invalid Choice (1 - 2)" << endl;
                    } else if (sub_choice == 2) {
                        return 0;
                    }
                } while (sub_choice > 2 || sub_choice < 1);
                
                clearScreen();
                break;
            }
            
            // Delete a Book
            case 5: {
                clearScreen();
                cout << "Enter ID: ";
                cin >> ID;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                index = -1;
                
                // Search linearly for ID and if it matches and isn't hidden then return the ID
                for (int i = 0; i < book_number; i++) {
                    if (Books[i][7] == "show" && Books[i][0] == ID) {
                        index = i;
                        break;
                    }
                }
                
                if (index < 0) {
                    cout << "ID Not found" << endl;
                    break;
                }
                
                // Hide the Book from being viewed or searched by the user without permanently deleting it
                Books[index][7] = "hide";
                cout << "Successfully Removed Book!" << endl;
                
                int sub_choice;
                do {
                    cout << "1.  Return to Main Menu" << endl;
                    cout << "2.  Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> sub_choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    if (sub_choice > 2 || sub_choice < 1) {
                        cout << "Invalid Choice (1 - 2)" << endl;
                    } else if (sub_choice == 2) {
                        return 0;
                    }
                } while (sub_choice > 2 || sub_choice < 1);
                
                break;
            }
            
            // Edit a Books details
            case 6: {
                clearScreen();
                cout << "Enter ID: ";
                cin >> ID;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                index = -1;
                
                // Search linearly for ID and if it matches and isn't hidden then return the ID
                for (int i = 0; i < book_number; i++) {
                    if (Books[i][7] == "show" && Books[i][0] == ID) {
                        index = i;
                        break;
                    }
                }
                
                if (index < 0) {
                    cout << "ID Not found" << endl;
                    break;
                }
                
                cout << "1.  Edit Title" << endl;
                cout << "2.  Edit Description" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if (choice == 2) {
                    cout << "Previous Description: " << Books[index][6] << endl;
                    cout << "Enter new Description: ";
                    getline(cin, Books[index][6]);
                    cout << "Description Successfully Changed!" << endl;
                } else if (choice == 1) {
                    cout << "Previous Title: " << Books[index][1] << endl;
                    cout << "Enter new Title: ";
                    getline(cin, Books[index][1]);
                    cout << "Title Successfully Changed!" << endl;
                } else {
                    cout << "Invalid Choice" << endl;
                }
                
                int sub_choice;
                do {
                    cout << "1.  Return to Main Menu" << endl;
                    cout << "2.  Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> sub_choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    if (sub_choice > 2 || sub_choice < 1) {
                        cout << "Invalid Choice (1 - 2)" << endl;
                    } else if (sub_choice == 2) {
                        return 0;
                    }
                } while (sub_choice > 2 || sub_choice < 1);
                
                clearScreen();
                break;
            }
            
            // View all Books
            case 7: {
                clearScreen();
                // char lengths: ID 11, Title 42, Author 28, Availability 100
                cout << " ID        | Title                                  | Author                     | Availability " << endl;
                cout << "------------------------------------------------------------------------------------------------" << endl;
                
                // Print each Book 
                for (int i = 0; i < book_number; i++) {
                    // if Book is deleted (hidden) from library then exit method
                    if (Books[i][7] == "hide") {
                        continue;
                    }
                    
                    // Print ID and fill the remaining blank with whitespace
                    cout << " " << Books[i][0];
                    for (size_t j = 0; j < (10 - Books[i][0].length()); j++) {
                        cout << " ";
                    }
                    cout << "|";
                    
                    // Print Title and fill the remaining blank with whitespace
                    cout << " " << Books[i][1];
                    for (size_t j = 0; j < (39 - Books[i][1].length()); j++) {
                        cout << " ";
                    }
                    cout << "|";
                    
                    // Print Author and fill the blank with whitespace
                    cout << " " << Books[i][2];
                    for (size_t j = 0; j < (27 - Books[i][2].length()); j++) {
                        cout << " ";
                    }
                    cout << "|";
                    
                    // Print Additional Info
                    cout << " " << Books[i][5] << endl;
                    cout << "           - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -          " << endl;
                    cout << " Publication Date: " << Books[i][3] << endl;
                    cout << " Publisher: " << Books[i][4] << endl;
                    cout << " Description: " << endl;
                    cout << " ";
                    
                    // Print Description and only move to the next line after 90 characters and the word is finished
                    string description = Books[i][6];
                    for (size_t j = 0; j < description.length(); j++) {
                        cout << description[j];
                        if ((j + 1) % 90 == 0) {
                            for (size_t k = j + 1; k < description.length(); k++) {
                                cout << description[k];
                                if (description[k] == ' ') {
                                    j = k;
                                    break;
                                }
                                j = k;
                            }
                            cout << endl;
                        }
                    }
                    cout << endl;
                    cout << "------------------------------------------------------------------------------------------------" << endl;
                }
                
                int sub_choice;
                do {
                    cout << "1.  Return to Main Menu" << endl;
                    cout << "2.  Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> sub_choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    if (sub_choice > 2 || sub_choice < 1) {
                        cout << "Invalid Choice (1 - 2)" << endl;
                    } else if (sub_choice == 2) {
                        return 0;
                    }
                } while (sub_choice > 2 || sub_choice < 1);
                
                clearScreen();
                break;
            }
            
            // Exit program
            case 8:
                return 0;
            
            // Catch invalid choices
            default:
                clearScreen();
                cout << "Invalid Choice (1 - 8)" << endl;
                break;
        }
    }
    
    return 0;
}
