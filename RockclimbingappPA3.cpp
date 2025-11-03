#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
int main()
{
    cout << "=============================================\n";
    cout << "  Welcome to the Rock Climbing Tracker!\n";
    cout << "  Let's learn about your climbing adventures.\n";
    cout << "=============================================\n";
    // Declare Variables to store responses.
    string climberName, climbingType, climbingLocation;
    int climbDays;
    double climbTime, totalTime;
    //Ask questions about rock climbing to the user. In an if statement. This will terminate the program if there is an invalid input.
    cout << "What is your full name? ";
    getline(cin, climberName);
    if (climberName == "") {
        cout << "\n Invalid input: name cannot be blank. Program terminated.\n";
        return 0;
    }

    cout << "\nWhat style of rock climbing do you enjoy most? ";
    getline(cin, climbingType);

    if (climbingType == "") {
        cout << "\n Invalid input: climbing style cannot be blank. Program terminated.\n";
        return 0;
    }

    cout << "\nDo you usually climb indoors or outdoors? ";
    getline(cin, climbingLocation);

    if (climbingLocation == "") {
        cout << "\n Invalid input: location cannot be blank. Program terminated.\n";
        return 0;
    }

    cout << "\nHow many days do you climb in a year? ";
    cin >> climbDays;

    if (climbDays <= 0) {
        cout << "\n Invalid input: climbing days must be greater than 0. Program terminated.\n";
        return 0;
    }

    cout << "\nOn average, how many hours do you spend per climbing session? ";
    cin >> climbTime;

    if (climbTime <= 0) {
        cout << "\n Invalid input: climbing session time must be greater than 0. Program terminated.\n";
        return 0;
    }

    //Calculate average time spent climbing in a year.
    totalTime = climbTime * climbDays;
    
    // A simple menu to choose options
    int choice;
    cout << "\n=============================================\n";
    cout << "  Choose an option below:\n";
    cout << "  1 = View Climbing Report\n";
    cout << "  2 = Recommend Climbing Level\n";
    cout << "  3 = Exit Program\n";
    cout << "=============================================\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
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
        {
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
        }
        break;

    case 2:
        // These compound if statements determine what type of climber someone is.
        if (climbDays >= 80 && climbTime >= 2.0) {
            cout << "\nWow, " << climberName << " you are a very dedicated and experienced climber!\n";
        }
        else if (climbDays >= 80 && climbTime < 2.0) {
            cout << "\nWow, " << climberName << " you climb very often!\n";
        }
        else if (climbDays < 10 && climbTime <= 2.0) {
            cout << "\nLooks like you are just getting started " << climberName << ". Keep climbing!\n";
        }
        else if (climbDays < 10 && climbTime >= 2.0) {
            cout << "\nLooks like you are very dedicated to climbing " << climberName << ", keep getting stronger!\n";
        }
        else {
            cout << "\nYou have a balanced climbing schedule " << climberName << "!\n";
        }
        // This if statement determines a persons climbing level
        if (totalTime >= 160) {
            cout << "\nBased on your activity, you are an ADVANCED climber!\n";
        }
        else if (totalTime >= 21 && totalTime <160 ) {
            cout << "\nYou are an INTERMEDIATE climber. Keep learning and growing stronger!\n";
        }
        else {
            cout << "\nYou are a BEGINNER climber. Have fun learning the ropes!\n";
        }
        break;
    // This exits the program
    case 3:
        cout << "\nThank you for using the Rock Climbing Tracker. Goodbye!\n";
        break;

    default:
        cout << "\nInvalid choice. Program terminated.\n";
        break;
    }

    return 0;
}