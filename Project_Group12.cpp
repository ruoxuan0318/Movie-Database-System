#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. STRUCT DEFINITIONS (Project Requirement)
// ==========================================
struct MovieData {
    int movieID;
    string title;
    double price;
    double rating;
};

struct BookingData {
    int bookingID;
    string customerUsername;
    int movieID;
    int quantity;
    double totalAmount;
};

// ==========================================
// 2. DYNAMIC NON-PRIMITIVE DATA STRUCTURE (DNP)
// ==========================================
class MovieNode {
public:
    MovieData data;
    MovieNode* next;
    MovieNode* prev;
};

class MovieLinkedList {
private:
    MovieNode* head;
    MovieNode* tail;
};

// ==========================================
// 3. OBJECT-ORIENTED PROGRAMMING DESIGN (OOP)
// ==========================================
class User {
protected:
    string username;
    string password;
};

class SystemLogger {
};

int main() {
    cout << "Initializing CineManage System Database..." << endl;
    return 0;
}
