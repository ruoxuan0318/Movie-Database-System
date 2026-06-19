#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// =========================================================================
// STRUCT DEFINITIONS (Requirement: 2 Struct Data Types)
// =========================================================================

// Holds the detailed information of a cinema movie record
struct MovieData {
    int movieID;
    string title;
    double price;
    double rating;
};

// Holds the transactional information of a customer ticket booking
struct BookingData {
    int bookingID;
    string customerUsername;
    int movieID;
    int quantity;
    double totalAmount;
};

// =========================================================================
// DOUBLE LINKED LIST (Requirement: 1 Dynamic Non-Primitive Data Structure)
// =========================================================================

class MovieNode {
public:
    MovieData data;
    MovieNode* next;
    MovieNode* prev;

    MovieNode(int id, string t, double p, double r) {
        data.movieID = id;
        data.title = t;
        data.price = p;
        data.rating = r;
        next = NULL;
        prev = NULL;
    }
};

class MovieLinkedList {
private:
    MovieNode* head;
    MovieNode* tail;
public:
    MovieLinkedList() {
        head = NULL;
        tail = NULL;
    }

    // Manual memory clearance to prevent leaks (Requirement: Dynamic Memory Operation)
    ~MovieLinkedList() {
        MovieNode* current = head;
        while (current != NULL) {
            MovieNode* nextNode = current->next;
            delete current; 
            current = nextNode;
        }
    }

    // Inserts a record at the tail of the list
    void insertMovie(int id, string t, double p, double r) {
        MovieNode* newNode = new MovieNode(id, t, p, r);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Linearly finds movie by primary key ID
    MovieNode* findMovie(int id) {
        MovieNode* current = head;
        while (current != NULL) {
            if (current->data.movieID == id) return current;
            current = current->next;
        }
        return NULL;
    }

    // Manually updates links and destroys unneeded nodes (Requirement: Dynamic Memory Operation)
    bool deleteMovie(int id) {
        MovieNode* target = findMovie(id);
        if (target == NULL) return false;

        if (target == head) {
            head = target->next;
            if (head != NULL) head->prev = NULL;
            else tail = NULL; 
        }
        else if (target == tail) {
            tail = target->prev;
            if (tail != NULL) tail->next = NULL;
        }
        else {
            target->prev->next = target->next;
            target->next->prev = target->prev;
        }

        delete target; 
        return true;
    }

    // Formats and renders plain text tracking sheets
    void printAllMovies() {
        if (head == NULL) {
            cout << "[SYSTEM] There are no movie records registered inside the data system.\n";
            return;
        }
        MovieNode* current = head;
        cout << "===========================================================================\n";
        cout << left << setw(12) << "MovieID" << setw(40) << "Movie Title" << setw(12) << "Price ($)" << setw(10) << "Rating" << endl;
        cout << "===========================================================================\n";
        while (current != NULL) {
            cout << left << setw(12) << current->data.movieID 
                 << setw(40) << current->data.title 
                 << setw(12) << fixed << setprecision(2) << current->data.price 
                 << setw(10) << current->data.rating << endl;
            current = current->next;
        }
        cout << "===========================================================================\n";
    }

    MovieNode* getHead() { return head; }
};

// =========================================================================
// BASE CLASSES (Requirement: 2 Base Classes)
// =========================================================================

// Base Class 1: General User profile architecture
class User {
protected:
    string username;
    string password;
public:
    User(string un, string pw) : username(un), password(pw) {}
    virtual ~User() {} 
    
    // Pure virtual function enforcing polymorphic override across systems
    virtual void showMenu() = 0; 
    
    string getUsername() { return username; }
    string getPassword() { return password; }
};

// Base Class 2: System structural auditing tracker
class SystemLogger {
public:
    void printLog(string user, string action) {
        cout << "[AUDIT LOG] Active Account [" << user << "] invoked operation: " << action << endl;
    }
};

// =========================================================================
// REQUIREMENT CHECK: ALGORITHMS (MANUAL IMPLEMENTATION - NO STL)
// =========================================================================

class CinemaAlgorithms {
private:
    // Manual swap function for MovieData structure elements
    static void swapMovieRecords(MovieData& recordA, MovieData& recordB) {
        MovieData tempHolder = recordA;
        recordA = recordB;
        recordB = tempHolder;
    }

    // Partition logic for Quick Sort (Requirement: Quick Sort Implementation)
    static MovieNode* partitionList(MovieNode* lowNode, MovieNode* highNode, int sortCriterion) {
        MovieData pivotValue = highNode->data;
        MovieNode* indexI = lowNode->prev;

        for (MovieNode* indexJ = lowNode; indexJ != highNode; indexJ = indexJ->next) {
            bool conditionMet = false;
            
            // Criterion 1: Sort by Price (Ascending - Low to High)
            if (sortCriterion == 1) {
                if (indexJ->data.price <= pivotValue.price) {
                    conditionMet = true;
                }
            } 
            // Criterion 2: Sort by Rating (Descending - High to Low)
            else if (sortCriterion == 2) {
                if (indexJ->data.rating >= pivotValue.rating) {
                    conditionMet = true;
                }
            }

            if (conditionMet) {
                if (indexI == NULL) {
                    indexI = lowNode;
                } else {
                    indexI = indexI->next;
                }
                swapMovieRecords(indexI->data, indexJ->data);
            }
        }
        
        if (indexI == NULL) {
            indexI = lowNode;
        } else {
            indexI = indexI->next;
        }
        swapMovieRecords(indexI->data, highNode->data);
        return indexI;
    }

    // Recursive implementation of Quick Sort on Doubly Linked List
    static void executeQuickSort(MovieNode* lowNode, MovieNode* highNode, int sortCriterion) {
        if (highNode != NULL && lowNode != highNode && lowNode != highNode->next) {
            MovieNode* pivotNode = partitionList(lowNode, highNode, sortCriterion);
            executeQuickSort(lowNode, pivotNode->prev, sortCriterion);
            executeQuickSort(pivotNode->next, highNode, sortCriterion);
        }
    }

public:
    // Entry function to trigger sorting from outside the class
    static void sortMovieCatalogue(MovieLinkedList& movieStorageList, int sortCriterion) {
        MovieNode* startingNode = movieStorageList.getHead();
        if (startingNode == NULL) return;

        MovieNode* endingNode = startingNode;
        while (endingNode->next != NULL) {
            endingNode = endingNode->next;
        }
        executeQuickSort(startingNode, endingNode, sortCriterion);
    }

    // Helper node retriever by simulated integer index positions
    static MovieNode* locateNodeByIndex(MovieNode* startingNode, int structuralIndex) {
        MovieNode* searchCursor = startingNode;
        int currentCounter = 0;
        while (searchCursor != NULL) {
            if (currentCounter == structuralIndex) {
                return searchCursor;
            }
            searchCursor = searchCursor;
            searchCursor = searchCursor->next;
            currentCounter++;
        }
        return NULL;
    }

    // Manual implementation of Binary Search (Requirement: Binary Search Implementation)
    static MovieNode* binarySearchMovieByID(MovieLinkedList& movieStorageList, int targetID) {
        MovieNode* headNode = movieStorageList.getHead();
        if (headNode == NULL) return NULL;

        // Calculate total length manually since STL size() is banned
        int totalElementsCount = 0;
        MovieNode* sizingCursor = headNode;
        while (sizingCursor != NULL) {
            totalElementsCount++;
            sizingCursor = sizingCursor->next;
        }

        int lowerBound = 0;
        int upperBound = totalElementsCount - 1;

        while (lowerBound <= upperBound) {
            int middleIndex = lowerBound + (upperBound - lowerBound) / 2;
            MovieNode* middleNode = locateNodeByIndex(headNode, middleIndex);

            if (middleNode == NULL) return NULL;

            if (middleNode->data.movieID == targetID) {
                return middleNode; 
            }
            else if (middleNode->data.movieID < targetID) {
                lowerBound = middleIndex + 1; 
            }
            else {
                upperBound = middleIndex - 1; 
            }
        }
        return NULL; 
    }
};

// =========================================================================
// REQUIREMENT CHECK: OVERLOADED FUNCTIONS (4 Overloaded / Overridden Functions)
// =========================================================================

// Function Overload 1: Basic string validation for empty input
bool validateUserInput(string dataInput) {
    if (dataInput.empty() || dataInput == " " || dataInput == "") {
        return false;
    }
    return true;
}

// Function Overload 2: Overloaded validation checking boundary limits for IDs
bool validateUserInput(int numericID) {
    if (numericID < 1000 || numericID > 9999) {
        return false;
    }
    return true;
}

// Function Overload 3: Overloaded validation checking bounds for financial metrics
bool validateUserInput(double financialValue) {
    if (financialValue <= 0.0 || financialValue > 500.0) {
        return false;
    }
    return true;
}

// Function Overload 4: Overloaded validation checking logic parameters
bool validateUserInput(int userSelectionOption, int minimumLimit, int maximumLimit) {
    if (userSelectionOption < minimumLimit || userSelectionOption > maximumLimit) {
        return false;
    }
    return true;
}
