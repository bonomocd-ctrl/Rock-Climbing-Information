#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h> // Windows console colors

using namespace std;

// CONSTANTS
const int ADVANCED_HOURS = 160;
const int INTERMEDIATE_HOURS = 21;
const int FREQUENT_CLIMBER_DAYS = 80;
const int NEW_CLIMBER_DAYS = 10;
const double DEDICATED_SESSION_HOURS = 2.0;

// ENUM
enum ClimbDifficulty { EASY = 1, MODERATE, HARD, EXTREME };

// STRUCT
struct ClimbSession {
    string date;
    double hours;
    ClimbDifficulty difficulty;  // Enum PART OF STRUCT 
};

// FUNCTION DECLARATIONS
void setColor(int);
void displayBanner();
string getStringInput(string prompt);
int getIntInput(string prompt);
double getDoubleInput(string prompt);

void displayMenu();
void saveReport(string, string, string, int, double, double,
    int[], int, double, int, int);
void showReport(string, string, string, int, double, double,
    int[], int, double, int, int);
void recommendLevel(int, double, double, string);
void describeDifficulty(ClimbDifficulty difficulty) {
    setColor(10);
    cout << "\nDifficulty Rating: ";

    switch (difficulty) {
    case EASY:
        cout << "This is a beginner-friendly route. Great for warming up.\n";
        break;
    case MODERATE:
        cout << "A reasonable challenge. Good technique is helpful.\n";
        break;
    case HARD:
        cout << "A tough climb! Expect strenuous moves and commitment.\n";
        break;
    case EXTREME:
        cout << "Top-tier difficulty. Only experienced climbers attempt this.\n";
        break;
    default:
        cout << "Unknown difficulty.\n";
    }

    setColor(15);
}
// enum functions
ClimbDifficulty getDifficultyFromUser();
void describeDifficulty(ClimbDifficulty);
string difficultyToString(ClimbDifficulty);  

// struct/session functions
ClimbSession createClimbSession();
void printClimbSession(const ClimbSession& s);
void saveSessionToFile(const ClimbSession& s);

// array of struct functions
void addSession(ClimbSession sessions[], int& count, int max);
void showAllSessions(const ClimbSession sessions[], int count);

// array functions
int fillMonthlyGrades(int grades[], int maxSize);
void analyzeGrades(int grades[], int count, double& avg, int& high, int& low);


// COLOR FUNCTION
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// BANNER
void displayBanner() {
    setColor(11);
    cout << "=============================================\n";
    cout << "      Welcome to the Rock Climbing Tracker!  \n";
    cout << "  Track your progress and discover your level.\n";
    cout << "=============================================\n\n";
    setColor(15);
}

// INPUT VALIDATION
string getStringInput(string prompt) {
    string input;
    setColor(5);
    cout << prompt;
    getline(cin, input);

    while (input == "") {
        setColor(12);
        cout << "Invalid input. Please try again.\n";
        setColor(5);
        cout << prompt;
        getline(cin, input);
    }
    return input;
}

int getIntInput(string prompt) {
    int value;
    setColor(5);
    cout << prompt;
    cin >> value;
    while (cin.fail() || value <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(12);
        cout << "Invalid. Enter a positive number: ";
        cin >> value;
    }
    cin.ignore();
    return value;
}

double getDoubleInput(string prompt) {
    double value;
    setColor(5);
    cout << prompt;
    cin >> value;
    while (cin.fail() || value <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(12);
        cout << "Invalid. Enter a positive number: ";
        cin >> value;
    }
    cin.ignore();
    return value;
}

// MENU
void displayMenu() {
    setColor(14);
    cout << "\n=============================================\n";
    cout << "  1 = View Climbing Report\n";
    cout << "  2 = Recommend Climbing Level\n";
    cout << "  3 = Log Single Climbing Session\n";
    cout << "  4 = Rate Difficulty Only\n";
    cout << "  5 = Enter Monthly Difficulty Grades\n";
    cout << "  6 = Exit Program\n";
    cout << "  7 = Add Session to Weekly Log\n";
    cout << "  8 = View Weekly Log\n";
    cout << "=============================================\n";
    setColor(5);
}

// ENUM CONVERSION FUNCTION (NEW!)
string difficultyToString(ClimbDifficulty d) {
    switch (d) {
    case EASY: return "Easy";
    case MODERATE: return "Moderate";
    case HARD: return "Hard";
    case EXTREME: return "Extreme";
    }
    return "Unknown";
}

// REPORT
void showReport(string name, string type, string location, int days,
    double hoursPerSession, double totalTime,
    int grades[], int gradeCount, double avgDifficulty, int highest, int lowest)
{
    setColor(10);
    cout << fixed << setprecision(2);

    cout << "\n=============================================\n";
    cout << "         Rock Climbing Summary Report        \n";
    cout << "=============================================\n";
    cout << left << setw(25) << "Climber Name:" << right << setw(20) << name << endl;
    cout << left << setw(25) << "Climbing Style:" << right << setw(20) << type << endl;
    cout << left << setw(25) << "Location:" << right << setw(20) << location << endl;
    cout << left << setw(25) << "Days per Year:" << right << setw(20) << days << endl;
    cout << left << setw(25) << "Hours per Session:" << right << setw(20) << hoursPerSession << endl;
    cout << left << setw(25) << "Average Annual Hours:" << right << setw(20) << totalTime << endl;

    if (gradeCount > 0) {
        cout << "\n---- Monthly Difficulty Ratings ----\n";
        for (int i = 0; i < gradeCount; i++)
            cout << "Month " << (i + 1) << ": " << grades[i] << endl;

        cout << "Avg Difficulty: " << avgDifficulty
            << " | High: " << highest
            << " | Low: " << lowest << endl;
    }

    cout << "=============================================\n";
    setColor(15);
}

void saveReport(string name, string type, string location, int days,
    double hoursPerSession, double totalTime,
    int grades[], int gradeCount, double avgDifficulty, int highest, int lowest)
{
    ofstream out("report.txt");
    out << fixed << setprecision(2);

    out << "Rock Climbing Report\n";
    out << "-----------------------\n";
    out << "Climber: " << name << endl;
    out << "Style: " << type << endl;
    out << "Location: " << location << endl;
    out << "Days/year: " << days << endl;
    out << "Hrs/session: " << hoursPerSession << endl;
    out << "Total Hours: " << totalTime << endl;

    if (gradeCount > 0) {
        out << "\nMonthly Difficulty Ratings:\n";
        for (int i = 0; i < gradeCount; i++)
            out << "Month " << (i + 1) << ": " << grades[i] << endl;

        out << "Average: " << avgDifficulty
            << " | High: " << highest
            << " | Low: " << lowest << endl;
    }

    out.close();
}

// LEVEL RECOMMENDATION
void recommendLevel(int days, double hrs, double totalTime, string name)
{
    setColor(11);

    if (days >= FREQUENT_CLIMBER_DAYS && hrs >= DEDICATED_SESSION_HOURS)
        cout << "\nWow, " << name << "! You're extremely dedicated!\n";
    else if (days >= FREQUENT_CLIMBER_DAYS)
        cout << "\nYou climb frequently — great job!\n";
    else if (days < NEW_CLIMBER_DAYS && hrs <= DEDICATED_SESSION_HOURS)
        cout << "\nYou're just starting out — keep going!\n";
    else if (days < NEW_CLIMBER_DAYS)
        cout << "\nNew climber but very dedicated — awesome!\n";
    else
        cout << "\nYou have a healthy, balanced climbing schedule.\n";

    if (totalTime >= ADVANCED_HOURS)
        cout << "You are an ADVANCED climber!\n";
    else if (totalTime >= INTERMEDIATE_HOURS)
        cout << "You are an INTERMEDIATE climber.\n";
    else
        cout << "You are a BEGINNER climber.\n";

    setColor(15);
}

// DIFFICULTY INPUT
ClimbDifficulty getDifficultyFromUser() {
    int choice;
    cout << "\nHow difficult was the climb?\n";
    cout << " 1 = Easy\n 2 = Moderate\n 3 = Hard\n 4 = Extreme\n";
    cout << "Enter choice: ";
    cin >> choice;

    while (choice < 1 || choice > 4) {
        cout << "Invalid (1–4): ";
        cin >> choice;
    }
    cin.ignore();
    return static_cast<ClimbDifficulty>(choice);
}

// STRUCT FUNCTIONS
ClimbSession createClimbSession() {
    ClimbSession s;
    s.date = getStringInput("\nEnter session date (mm/dd/yyyy): ");
    s.hours = getDoubleInput("Enter hours climbed: ");
    s.difficulty = getDifficultyFromUser();   // Enum stored 
    return s;
}

void printClimbSession(const ClimbSession& s) {
    setColor(11);
    cout << "\n===== Climbing Session =====\n";
    cout << "Date: " << s.date << endl;
    cout << "Hours: " << s.hours << endl;
    cout << "Difficulty: " << difficultyToString(s.difficulty) << endl;
    cout << "============================\n";
    setColor(15);
}

void saveSessionToFile(const ClimbSession& s) {
    ofstream out("session.txt");
    out << "Climbing Session\n";
    out << "Date: " << s.date << endl;
    out << "Hours: " << s.hours << endl;
    out << "Difficulty: " << difficultyToString(s.difficulty) << endl;
    out.close();
}

// ARRAY OF STRUCTS FUNCTIONS
void addSession(ClimbSession sessions[], int& count, int max) {
    if (count >= max) {
        cout << "\nERROR: Session log is full.\n";
        return;
    }
    sessions[count] = createClimbSession();
    count++;
    cout << "\nSession added to weekly log!\n";
}

void showAllSessions(const ClimbSession sessions[], int count) {
    if (count == 0) {
        cout << "\nNo sessions logged yet.\n";
        return;
    }

    cout << "\n========== Weekly Climbing Sessions ==========\n";
    for (int i = 0; i < count; i++) {
        cout << "Session " << (i + 1) << ":\n";
        cout << "  Date: " << sessions[i].date << endl;
        cout << "  Hours: " << sessions[i].hours << endl;
        cout << "  Difficulty: " << difficultyToString(sessions[i].difficulty) << endl;
        cout << "-------------------------------------------\n";
    }
}

// ARRAY GRADES FUNCTIONS
int fillMonthlyGrades(int grades[], int max) {
    int count;
    cout << "\nHow many months (1–" << max << ")? ";
    cin >> count;

    while (count < 1 || count > max) {
        cout << "Invalid (1–" << max << "): ";
        cin >> count;
    }

    for (int i = 0; i < count; i++) {
        int value;
        cout << "Difficulty for month " << (i + 1) << " (1–10): ";
        cin >> value;
        while (value < 1 || value > 10) {
            cout << "Must be 1–10: ";
            cin >> value;
        }
        grades[i] = value;
    }
    cin.ignore();
    return count;
}

void analyzeGrades(int grades[], int count, double& avg, int& high, int& low) {
    int sum = 0;
    high = grades[0];
    low = grades[0];

    for (int i = 0; i < count; i++) {
        sum += grades[i];
        if (grades[i] > high) high = grades[i];
        if (grades[i] < low) low = grades[i];
    }
    avg = static_cast<double>(sum) / count;
}

// MAIN PROGRAM
int main() {
    displayBanner();

    string name = getStringInput("What is your full name? ");
    string type = getStringInput("\nFavorite style of climbing? ");
    string location = getStringInput("\nDo you climb indoors or outdoors? ");
    int days = getIntInput("\nHow many days do you climb per year? ");
    double hrsPerSession = getDoubleInput("\nAverage hours per session? ");

    double totalTime = days * hrsPerSession;

    // Monthly difficulty arrays
    int monthlyGrades[12];
    int gradeCount = 0;
    double avgDifficulty = 0;
    int highest = 0, lowest = 0;

    // Array of structs for weekly log
    ClimbSession sessions[50];
    int sessionCount = 0;

    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            if (gradeCount == 0)
                cout << "\nEnter monthly grades first (option 5).\n";
            else {
                showReport(name, type, location, days, hrsPerSession, totalTime,
                    monthlyGrades, gradeCount, avgDifficulty, highest, lowest);
                saveReport(name, type, location, days, hrsPerSession, totalTime,
                    monthlyGrades, gradeCount, avgDifficulty, highest, lowest);
            }
            break;

        case 2:
            recommendLevel(days, hrsPerSession, totalTime, name);
            break;

        case 3: {
            ClimbSession s = createClimbSession();
            printClimbSession(s);
            saveSessionToFile(s);
            break;
        }

        case 4:
            describeDifficulty(getDifficultyFromUser());
            break;

        case 5:
            gradeCount = fillMonthlyGrades(monthlyGrades, 12);
            analyzeGrades(monthlyGrades, gradeCount, avgDifficulty, highest, lowest);
            cout << "\nGrades recorded.\n";
            break;

        case 6:
            cout << "\nThank you for using the Climbing Tracker!\n";
            break;

        case 7:
            addSession(sessions, sessionCount, 50);
            break;

        case 8:
            showAllSessions(sessions, sessionCount);
            break;

        default:
            cout << "Invalid option.\n";
        }

    } while (choice != 6);

    return 0;
}
