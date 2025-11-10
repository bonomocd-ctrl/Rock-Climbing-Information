#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
const int ADVANCED_HOURS = 160;         
const int INTERMEDIATE_HOURS = 21;   
const int FREQUENT_CLIMBER_DAYS = 80;   
const int NEW_CLIMBER_DAYS = 10;       
const double DEDICATED_SESSION_HOURS = 2.0;
int main()
{
    // Introduction banner
    cout << "=============================================\n";
    cout << "      Welcome to the Rock Climbing Tracker!  \n";
    cout << "  Track your progress and discover your level.\n";
    cout << "=============================================\n\n";

    // Declare variables
    string climberName, climbingType, climbingLocation;
    int climbDays, numSessions;
    double climbTime, totalTime,sessionHours, totalSessionHours = 0;
    // Input section (with validation using while loops)
    cout << "What is your full name? ";
    getline(cin, climberName);
    while (climberName == "") {
        cout << "Invalid input: name cannot be blank.\n";
        cout << "Please enter your full name: ";
        getline(cin, climberName);
    }

    cout << "\nWhat style of rock climbing do you enjoy most? ";
    getline(cin, climbingType);
    while (climbingType == "") {
        cout << "Invalid input: climbing style cannot be blank.\n";
        cout << "Please enter your preferred climbing style: ";
        getline(cin, climbingType);
    }

    cout << "\nDo you usually climb indoors or outdoors? ";
    getline(cin, climbingLocation);
    while (climbingLocation == "") {
        cout << "Invalid input: location cannot be blank.\n";
        cout << "Please enter whether you climb indoors or outdoors: ";
        getline(cin, climbingLocation);
    }

    // Input validation using a while loop (must be positive)
    cout << "\nHow many days do you climb in a year? ";
    cin >> climbDays;
    while (climbDays <= 0) {
        cout << "Invalid input. Please enter a value greater than 0: ";
        cin >> climbDays;
    }

    cout << "\nOn average, how many hours do you spend per climbing session? ";
    cin >> climbTime;
    while (climbTime <= 0) {
        cout << "Invalid input. Please enter a value greater than 0: ";
        cin >> climbTime;
    }

    // Compute total time
    totalTime = climbTime * climbDays;

    int choice;
    do {
        cout << "\n=============================================\n";
        cout << "  Choose an option below:\n";
        cout << "  1 = View Climbing Report\n";
        cout << "  2 = Recommend Climbing Level\n";
        cout << "  3 = Log session\n";
        cout << "  4 = Exit Program\n";
        cout << "=============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << fixed << setprecision(2);
            cout << "\n=============================================\n";
            cout << "         Rock Climbing Summary Report        \n";
            cout << "=============================================\n";
            cout << left << setw(25) << "Climber Name:" << right << setw(20) << climberName << endl;
            cout << left << setw(25) << "Climbing Style:" << right << setw(20) << climbingType << endl;
            cout << left << setw(25) << "Location:" << right << setw(20) << climbingLocation << endl;
            cout << left << setw(25) << "Days per Year:" << right << setw(20) << climbDays << endl;
            cout << left << setw(25) << "Hours per Session:" << right << setw(20) << climbTime << endl;
            cout << left << setw(25) << "Average Annual Hours:" << right << setw(20) << totalTime << endl;
            cout << "=============================================\n";

            // Save to file
            ofstream outData("report.txt");
            outData << fixed << setprecision(2);
            outData << "=============================================\n";
            outData << "         Rock Climbing Summary Report        \n";
            outData << "=============================================\n";
            outData << left << setw(25) << "Climber Name:" << right << setw(20) << climberName << endl;
            outData << left << setw(25) << "Climbing Style:" << right << setw(20) << climbingType << endl;
            outData << left << setw(25) << "Location:" << right << setw(20) << climbingLocation << endl;
            outData << left << setw(25) << "Days per Year:" << right << setw(20) << climbDays << endl;
            outData << left << setw(25) << "Hours per Session:" << right << setw(20) << climbTime << endl;
            outData << left << setw(25) << "Average Annual Hours:" << right << setw(20) << totalTime << endl;
            outData << "=============================================\n";
            outData.close();
            cout << "\nYour climbing report has been saved to 'report.txt'.\n";
            break;
        }

        case 2:
            // Recommend Climbing Level
            if (climbDays >= FREQUENT_CLIMBER_DAYS && climbTime >= DEDICATED_SESSION_HOURS) {
                cout << "\nWow, " << climberName << "! You are a very dedicated and experienced climber!\n";
            }
            else if (climbDays >= FREQUENT_CLIMBER_DAYS && climbTime < DEDICATED_SESSION_HOURS) {
                cout << "\nWow, " << climberName << "! You climb very often!\n";
            }
            else if (climbDays < NEW_CLIMBER_DAYS && climbTime <= DEDICATED_SESSION_HOURS) {
                cout << "\nLooks like you are just getting started, " << climberName << ". Keep climbing!\n";
            }
            else if (climbDays < NEW_CLIMBER_DAYS && climbTime >= DEDICATED_SESSION_HOURS) {
                cout << "\nYou're very dedicated for a new climber, " << climberName << "! Keep pushing!\n";
            }
            else {
                cout << "\nYou have a balanced climbing schedule, " << climberName << "!\n";
            }

            if (totalTime >= ADVANCED_HOURS) {
                cout << "Based on your total hours, you are an ADVANCED climber!\n";
            }
            else if (totalTime >= INTERMEDIATE_HOURS && totalTime < ADVANCED_HOURS) {
                cout << "You are an INTERMEDIATE climber. Keep learning and growing stronger!\n";
            }
            else {
                cout << "You are a BEGINNER climber. Have fun learning the ropes!\n";
            }
            break;

        case 3:
        {
            cout << "\nHow many climbing sessions would you like to log? ";
            cin >> numSessions;

            // Validate input
            while (numSessions <= 0) {
                cout << "Invalid input. Please enter a number greater than 0: ";
                cin >> numSessions;
            }

            // Use a for loop to collect climbing data for each session
            for (int i = 1; i <= numSessions; i++) {
                cout << "Enter hours climbed for session " << i << ": ";
                cin >> sessionHours;

                while (sessionHours <= 0) {
                    cout << "Invalid input. Enter hours greater than 0: ";
                    cin >> sessionHours;
                }

                totalSessionHours += sessionHours;
            }

            double averageSessionHours = totalSessionHours / numSessions;

            cout << fixed << setprecision(2);
            cout << "\n=============================================\n";
            cout << "       Climbing Session Summary\n";
            cout << "=============================================\n";
            cout << left << setw(25) << "Sessions Logged:" << right << setw(15) << numSessions << endl;
            cout << left << setw(25) << "Total Hours Climbed:" << right << setw(15) << totalSessionHours << endl;
            cout << left << setw(25) << "Average per Session:" << right << setw(15) << averageSessionHours << endl;
            cout << "=============================================\n";

            // write to sessiondata.txt
            ofstream outData("sessiondata.txt");
            outData << fixed << setprecision(2);
            outData << "\n=============================================\n";
            outData << "       Climbing Session Summary\n";
            outData << "=============================================\n";
            outData << left << setw(25) << "Sessions Logged:" << right << setw(15) << numSessions << endl;
            outData << left << setw(25) << "Total Hours Climbed:" << right << setw(15) << totalSessionHours << endl;
            outData << left << setw(25) << "Average per Session:" << right << setw(15) << averageSessionHours << endl;
            outData << "=============================================\n";
            outData.close();
            cout << "\nSession data added to 'sessiondata.txt'.\n";
            break;
        }
        case 4:
            cout << "\nThank you for using the Rock Climbing Tracker. Goodbye!\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 4);  // do-while loop ensures menu repeats until exit

    return 0;
}