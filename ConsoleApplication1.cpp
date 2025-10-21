
#include <iostream>
#include <string>
int main()
{
    // Declare Variables to store responses.
    std::string climbingType, climbingLocation;
    int climbTime, climbDays, totalTime;
    //Ask questions about rock climbing to the user.
    std::cout << "What style of rock clibing do you enjoy the most? \n";
    std::cin >> climbingType;
    std::cout << "\nDo you usually climb indoors or outdoors? ";
    std::cin >> climbingLocation;
    std::cout << "\nHow many days do you rock climb in a year? ";
    std::cin >> climbDays;
    std::cout << "\nWhat is the average amount of time in hours you spend in a rock climbing session?  ";
    std::cin >> climbTime;
    //Calculate average time spent climbing in a year.
    totalTime = climbTime * climbDays;
    //Summary of information given displayed to the user.
    std::cout << "\n Thank you for sharing! Here's a summary of your rock climbing preferences:\n";
    std::cout << "You enjoy the " << climbingType << " rock climbing style, ";
    std::cout << "and you prefer to climb " << climbingLocation << ". ";
    std::cout << "You climb for " << climbDays << " days in a year.\n";
    std::cout << "That's an average of " << totalTime << " hours of climbing in a year! \n";
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
