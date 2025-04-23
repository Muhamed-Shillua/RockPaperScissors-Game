#include <iostream>
#include <string>
#include <cstdlib> // For rand() and srand()
#include <ctime>  // For time()
#include <windows.h> //For system-level functions such as changing console color and clearing the screen
using namespace std;

// Structure to store the game score for Player, Computer, and Draws
struct strScore
{
    short Player = 0, Computer = 0, Draws = 0;
};

// Enum to represent the choices in the game: Stone, Paper, Scissor
enum enChoices
{
    Stone = 1,
    Paper = 2,
    Scissor = 3
};

// Change the console text color based on the input color code
void SetColor(string ColorCode)
{
    string command = "color " + ColorCode;
    system(command.c_str());
}

void ClearScreen()
{
    system("cls");
}

void CenterText(string Text)
{
    int width = 80; // Console width
    int pad = (width - Text.length()) / 2; // Calculate padding to center the text
    cout << string(pad, ' ') << Text << endl;
}

int ReadNumber(string Message)
{
    int Number;
    do {
        cout << Message;
        cin >> Number; // Get the user input
    } while (Number <= 0); // Ensure the number is positive
    return Number;
}

int GenerateRandomNumber(int From, int To)
{
    return (rand() % (To - From + 1)) + From; // Generate a random number in the range
}

// Get the player's choice (Stone, Paper, or Scissor)
enChoices GetPlayerChoice()
{
    int PlayerChoice = ReadNumber("Your Choice [1]: Stone, [2]: Paper, [3]: Scissor? ");
    while (PlayerChoice < 1 || PlayerChoice > 3) { // Validate the input
        PlayerChoice = ReadNumber("Invalid! Choose [1]: Stone, [2]: Paper, [3]: Scissor: ");
    }
    return static_cast<enChoices>(PlayerChoice); // Convert the input to an enum
}

// Generate the computer's random choice (Stone, Paper, or Scissor)
enChoices GetComputerChoice()
{
    return static_cast<enChoices>(GenerateRandomNumber(1, 3)); // Randomly select one of the three options
}

void PrintChoices(enChoices PlayerChoice, enChoices ComputerChoice)
{
    cout << "You chose: ";
    switch (PlayerChoice) { // Display player's choice
    case Stone: cout << "Stone"; break;
    case Paper: cout << "Paper"; break;
    case Scissor: cout << "Scissor"; break;
    }
    cout << "\nComputer chose: ";
    switch (ComputerChoice) { // Display computer's choice
    case Stone: cout << "Stone"; break;
    case Paper: cout << "Paper"; break;
    case Scissor: cout << "Scissor"; break;
    }
    cout << endl;
}

void WinnerPerRound(enChoices PlayerChoice, enChoices ComputerChoice, strScore& Score)
{
    if (PlayerChoice == ComputerChoice) {
        Score.Draws++; // It's a draw
    }
    else if ((PlayerChoice == Stone && ComputerChoice == Scissor) ||
        (PlayerChoice == Paper && ComputerChoice == Stone) ||
        (PlayerChoice == Scissor && ComputerChoice == Paper)) {
        Score.Player++; // Player wins
    }
    else {
        Score.Computer++; // Computer wins
    }
}

void PrintCurrentScore(strScore Score)
{
    // Show current round winner
    if (Score.Player > Score.Computer)
        CenterText("Round Winner: Player");
    else if (Score.Computer > Score.Player)
        CenterText("Round Winner: Computer");
    else
        CenterText("Round Result: Draw");

    // Display current score
    CenterText("---------- Current Score ----------");
    CenterText("Player Wins   : " + to_string(Score.Player));
    CenterText("Computer Wins : " + to_string(Score.Computer));
    CenterText("Draws         : " + to_string(Score.Draws));
    CenterText("----------------------------------");
}

void PrintFinalScore(strScore Score)
{
    if (Score.Player > Score.Computer)
        SetColor("2F"); // Green background for player win
    else if (Score.Computer > Score.Player)
        SetColor("4F"); // Red background for computer win
    else
        SetColor("6F"); // Yellow background for draw

    // Display final score
    CenterText("========== Final Score ==========");
    CenterText("Player Wins   : " + to_string(Score.Player));
    CenterText("Computer Wins : " + to_string(Score.Computer));
    CenterText("Draws         : " + to_string(Score.Draws));
    CenterText("=================================");

    // Announce the winner
    if (Score.Player > Score.Computer)
        CenterText("Congratulations! You Won the Game!");
    else if (Score.Computer > Score.Player)
        CenterText("Computer Won the Game! Better luck next time.");
    else
        CenterText("It's a Draw! Well Played!");

    CenterText("========== Game Over ==========");
}

bool AskToPlayAgain()
{
    char Answer;
    cout << "\nDo you want to play again? [Y/N]: ";
    cin >> Answer;
    return (toupper(Answer) == 'Y'); // Return true if player chooses to play again
}

// Start a new game with multiple rounds
void NewGame()
{
    strScore Score;
    int Rounds = ReadNumber("How Many Rounds (1 to 10)? "); // Get the number of rounds to play

    for (int i = 1; i <= Rounds; i++) { // Loop through each round
        cout << "\nRound [" << i << "] begins:\n";
        enChoices PlayerChoice = GetPlayerChoice(); // Get the player's choice
        enChoices ComputerChoice = GetComputerChoice(); // Get the computer's choice
        PrintChoices(PlayerChoice, ComputerChoice); // Display choices
        WinnerPerRound(PlayerChoice, ComputerChoice, Score); // Determine the winner of the round
        PrintCurrentScore(Score); // Display the current score

        // Set background color based on round result
        if (PlayerChoice == ComputerChoice)
            SetColor("6E"); // Yellow background for draw
        else if ((PlayerChoice == Stone && ComputerChoice == Scissor) ||
            (PlayerChoice == Paper && ComputerChoice == Stone) ||
            (PlayerChoice == Scissor && ComputerChoice == Paper))
            SetColor("2E"); // Green background for player win
        else
            SetColor("4E"); // Red background for computer win
    }

    PrintFinalScore(Score); // Display final score after all rounds
}

// Start the game and handle multiple sessions
void StartTheGame()
{
    do
    {
        ClearScreen(); // Clear the screen before starting a new game
        SetColor("1F"); // Set initial color
        CenterText("==============================");
        CenterText("         Let's Play!         ");
        CenterText("==============================\n");
        NewGame(); // Start a new game
    } while (AskToPlayAgain()); // Repeat if the player chooses to play again
}

int main() {
    srand((unsigned)time(NULL)); // Initialize random seed based on current time

    StartTheGame(); // Start the game

    return 0; 
}
