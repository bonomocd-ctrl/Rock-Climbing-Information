
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
    else {
        cout << "\n What style of rock climbing do you enjoy most? ";
        getline(cin, climbingType);
        if (climbingType == "") {
            cout << "\n Invalid input: climbing style cannot be blank. Program terminated.\n";
            return 0;
        }
        else {
            cout << "\n Do you usually climb indoors or outdoors? ";
            getline(cin, climbingLocation);
            
            
            if (climbingLocation == "") 
                { cout << "\n Invalid input: location cannot be blank. Program terminated.\n"; 
                return 0; }
            else {
                cout << "\n How many days do you climb in a year? "; cin >> climbDays;
            
                if (climbDays <= 0) {
                    cout << "\n Invalid input: climbing days must be greater than 0. Program terminated.\n";
                    return 0;
                }
                
                else {
                    cout << "\nOn average, how many hours do you spend per climbing session? ";
                    cin >> climbTime;
                    if (climbTime <= 0) {
                        cout << "\n Invalid input: climbing session time must be greater than 0. Program terminated.\n";
                        return 0;
                    }
                    else {
                        //Calculate average time spent climbing in a year.
                        totalTime = climbTime * climbDays;
                        //Summary of information given displayed to the user. in a properly formatted output.
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

                        // Save report to file named report.txt
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

                        cout << "\n Your climbing report has been saved to 'report.txt'.\n";
                    }
                }
            }
        }
    }

    return 0;
}