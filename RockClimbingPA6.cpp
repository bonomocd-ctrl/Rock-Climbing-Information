#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h> // for console colors

using namespace std;

//Constants
const int ADVANCED_HOURS = 160;
const int INTERMEDIATE_HOURS = 21;
const int FREQUENT_CLIMBER_DAYS = 80;
const int NEW_CLIMBER_DAYS = 10;
const double DEDICATED_SESSION_HOURS = 2.0;

// ENUM
enum ClimbDifficulty { EASY = 1, MODERATE, HARD, EXTREME };

//Function declaration
void setColor(int);
void displayBanner();
string getStringInput(string prompt);
int getIntInput(string prompt);
double getDoubleInput(string prompt);
void displayMenu();
void showReport(string, string, string, int, double, double,
    int grades[], int gradeCount, double avgDifficulty, int highest, int lowest);
void saveReport(string, string, string, int, double, double,
    int grades[], int gradeCount, double avgDifficulty, int highest, int lowest);
void recommendLevel(int, double, double, string);
void logSessions();

// Enum used as a parameter for a void function
ClimbDifficulty getDifficultyFromUser();
void describeDifficulty(ClimbDifficulty);

// Array function
int fillMonthlyGrades(int grades[], int maxSize);
void analyzeGrades(int grades[], int count, double& avg, int& highest, int& lowest);

//Color function
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void displayBanner() {
    setColor(11);
    cout << "=============================================\n";
    cout << "      Welcome to the Rock Climbing Tracker!  \n";
    cout << "  Track your progress and discover your level.\n";
    cout << "=============================================\n\n";
    setColor(15);
}

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

    while (value <= 0) {
        setColor(12);
        cout << "Invalid input. Enter a number greater than 0: ";
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

    while (value <= 0) {
        setColor(12);
        cout << "Invalid input. Enter a number greater than 0: ";
        cin >> value;
    }
    cin.ignore();
    return value;
}

void displayMenu() {
    setColor(14);
    cout << "\n=============================================\n";
    cout << "  Choose an option below:\n";
    cout << "  1 = View Climbing Report\n";
    cout << "  2 = Recommend Climbing Level\n";
    cout << "  3 = Log Session\n";
    cout << "  4 = Rate Difficulty of Last Climb\n";
    cout << "  5 = Enter Monthly Difficulty Grades\n";
    cout << "  6 = Exit Program\n";
    cout << "=============================================\n";
    setColor(5);
}

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
        cout << "\n------- Monthly Difficulty Ratings -------\n";
        for (int i = 0; i < gradeCount; i++) {
            cout << "Month " << (i + 1) << ": " << grades[i] << endl;
        }
        cout << "Average Difficulty: " << avgDifficulty
            << " | Highest: " << highest
            << " | Lowest: " << lowest << endl;
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

    out << "=============================================\n";
    out << "         Rock Climbing Summary Report        \n";
    out << "=============================================\n";
    out << left << setw(25) << "Climber Name:" << right << setw(20) << name << endl;
    out << left << setw(25) << "Climbing Style:" << right << setw(20) << type << endl;
    out << left << setw(25) << "Location:" << right << setw(20) << location << endl;
    out << left << setw(25) << "Days per Year:" << right << setw(20) << days << endl;
    out << left << setw(25) << "Hours per Session:" << right << setw(20) << hoursPerSession << endl;
    out << left << setw(25) << "Average Annual Hours:" << right << setw(20) << totalTime << endl;

    if (gradeCount > 0) {
        out << "\n------- Monthly Difficulty Ratings -------\n";
        for (int i = 0; i < gradeCount; i++) {
            out << "Month " << (i + 1) << ": " << grades[i] << "\n";
        }
        out << "\nAverage Difficulty: " << avgDifficulty
            << " | Highest: " << highest
            << " | Lowest: " << lowest << endl;
    }

    out << "=============================================\n";
    out.close();

    setColor(10);
    cout << "\nYour climbing report with difficulty array has been saved to 'report.txt'.\n";
    setColor(15);
}

void recommendLevel(int days, double hoursPerSession, double totalTime, string name)
{
    setColor(11);

    if (days >= FREQUENT_CLIMBER_DAYS && hoursPerSession >= DEDICATED_SESSION_HOURS)
        cout << "\nWow, " << name << "! You are a very dedicated and experienced climber!\n";
    else if (days >= FREQUENT_CLIMBER_DAYS)
        cout << "\nWow, " << name << "! You climb very often!\n";
    else if (days < NEW_CLIMBER_DAYS && hoursPerSession <= DEDICATED_SESSION_HOURS)
        cout << "\nLooks like you are just getting started, " << name << ". Keep climbing!\n";
    else if (days < NEW_CLIMBER_DAYS)
        cout << "\nYou're very dedicated for a new climber, " << name << "! Keep pushing!\n";
    else
        cout << "\nYou have a balanced climbing schedule, " << name << "!\n";

    if (totalTime >= ADVANCED_HOURS)
        cout << "Based on your total hours, you are an ADVANCED climber!\n";
    else if (totalTime >= INTERMEDIATE_HOURS)
        cout << "You are an INTERMEDIATE climber!\n";
    else
        cout << "You are a BEGINNER climber.\n";

    setColor(15);
}

void logSessions() {
    int numSessions = getIntInput("\nHow many climbing sessions would you like to log? ");
    double totalHours = 0;
    double sessionHours;

    for (int i = 1; i <= numSessions; i++) {
        cout << "Enter hours climbed for session " << i << ": ";
        cin >> sessionHours;

        while (sessionHours <= 0) {
            setColor(12);
            cout << "Invalid input. Enter hours greater than 0: ";
            cin >> sessionHours;
        }

        totalHours += sessionHours;
    }
    cin.ignore();

    double avg = totalHours / numSessions;

    setColor(10);
    cout << fixed << setprecision(2);
    cout << "\n=============================================\n";
    cout << "       Climbing Session Summary\n";
    cout << "=============================================\n";
    cout << left << setw(25) << "Sessions Logged:" << right << setw(15) << numSessions << endl;
    cout << left << setw(25) << "Total Hours Climbed:" << right << setw(15) << totalHours << endl;
    cout << left << setw(25) << "Average per Session:" << right << setw(15) << avg << endl;
    cout << "=============================================\n";

    ofstream out("sessiondata.txt");
    out << fixed << setprecision(2);
    out << "Sessions Logged: " << numSessions << endl;
    out << "Total Hours Climbed: " << totalHours << endl;
    out << "Average per Session: " << avg << endl;
    out.close();

    cout << "\nSession data added to 'sessiondata.txt'.\n";
    setColor(15);
}

// --------------------------------------------
// ENUM INPUT
ClimbDifficulty getDifficultyFromUser() {
    int choice;
    setColor(14);
    cout << "\nHow difficult was your most recent climbing session?\n";
    cout << "  1 = Easy\n";
    cout << "  2 = Moderate\n";
    cout << "  3 = Hard\n";
    cout << "  4 = Extreme\n";
    setColor(5);
    cout << "Enter option: ";
    cin >> choice;

    while (choice < 1 || choice > 4) {
        setColor(12);
        cout << "Invalid choice. Enter a number 1–4: ";
        cin >> choice;
    }
    cin.ignore();

    return static_cast<ClimbDifficulty>(choice);
}

void describeDifficulty(ClimbDifficulty level) {
    setColor(11);
    switch (level) {
    case EASY:
        cout << "\nEasy session! Great for warm-ups and technique practice.\n";
        break;
    case MODERATE:
        cout << "\nSolid climb! Moderate sessions help build consistency.\n";
        break;
    case HARD:
        cout << "\nNice work! A hard session means you're pushing your limits.\n";
        break;
    case EXTREME:
        cout << "\nWOW! Extreme difficulty! You're climbing at a high level!\n";
        break;
    }
    setColor(15);
}


// Array with input and analysis
int fillMonthlyGrades(int grades[], int maxSize) {
    int count;

    setColor(14);
    cout << "\nHow many months of difficulty ratings will you enter? (1–" << maxSize << "): ";
    cin >> count;

    while (count < 1 || count > maxSize) {
        setColor(12);
        cout << "Invalid. Enter between 1 and " << maxSize << ": ";
        cin >> count;
    }

    for (int i = 0; i < count; i++) {
        int value;
        setColor(5);
        cout << "Enter your difficulty rating for month " << (i + 1) << " (1–10): ";
        cin >> value;

        while (value < 1 || value > 10) {
            setColor(12);
            cout << "Invalid. Difficulty must be between 1 and 10: ";
            cin >> value;
        }
        grades[i] = value;
    }

    cin.ignore();
    return count;
}

void analyzeGrades(int grades[], int count, double& avg, int& highest, int& lowest) {
    int sum = 0;
    highest = grades[0];
    lowest = grades[0];

    for (int i = 0; i < count; i++) {
        sum += grades[i];
        if (grades[i] > highest) highest = grades[i];
        if (grades[i] < lowest) lowest = grades[i];
    }

    avg = static_cast<double>(sum) / count;
}

// MAIN
int main() {
    displayBanner();

    string name = getStringInput("What is your full name? ");
    string type = getStringInput("\nWhat style of rock climbing do you enjoy most? ");
    string location = getStringInput("\nDo you usually climb indoors or outdoors? ");
    int days = getIntInput("\nHow many days do you climb per year? ");
    double hrsPerSession = getDoubleInput("\nAverage hours per session? ");

    double totalTime = days * hrsPerSession;

    // Array variables
    int monthlyGrades[12];
    int gradeCount = 0;
    double avgDifficulty = 0;
    int highest = 0, lowest = 0;

    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            if (gradeCount == 0) {
                setColor(12);
                cout << "\nERROR: No monthly difficulty data entered yet.\n";
                cout << "Please choose option 5 to enter difficulty ratings first.\n";
                setColor(15);
            }
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

        case 3:
            logSessions();
            break;

        case 4: {
            ClimbDifficulty diff = getDifficultyFromUser();
            describeDifficulty(diff);
            break;
        }

        case 5:
            gradeCount = fillMonthlyGrades(monthlyGrades, 12);
            analyzeGrades(monthlyGrades, gradeCount, avgDifficulty, highest, lowest);

            setColor(10);
            cout << "\nMonthly difficulty ratings recorded!\n";
            cout << "Average: " << avgDifficulty
                << " | Highest: " << highest
                << " | Lowest: " << lowest << "\n";
            setColor(15);
            break;

        case 6:
            setColor(14);
            cout << "\nThank you for using the Rock Climbing Tracker. Goodbye!\n";
            setColor(15);
            break;

        default:
            setColor(12);
            cout << "Invalid option. Try again.\n";
            setColor(15);
        }

    } while (choice != 6);

    return 0;
}
