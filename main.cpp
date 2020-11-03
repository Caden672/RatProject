/* COPYRIGHT (C) 2020 Caden Dees (cjd117) All Rights Reserved.
Rats Project
Author. Caden Dees
        cjd117@zips.uakron.edu
Version. 1.02 11.02.2020
Purpose: To simulate the population of rats aboard a ship over a three week period.  Variables in the simulation include the initial rat population,
the weather, and the sanitation level on the ship.  Population growth and decay values were given in the prompt.  Also outputs the tables to a text file.
*/

#include <iostream>  //Library for in out functions
#include <iomanip> //Library for manipulating inputs and ouputs.
#include <limits>  //Includes mathematical functions
#include <cmath>  //Includes mathematical functions
#include <fstream> //Includes file input output operations

using std::cin;  //Lines 14 - 24 define the functions used in this program
using std::cout; //using the standard namespace.
using std::endl;
using std::string;
using std::setw;
using std::right;
using std::left;
using std::ofstream;
using std::ios;

void choiceValidationInteger(int &, int , int , string &, bool &); //Function prototypes line 26-50
void choiceValidationSanitation(double &, int , int , string &);
void choiceValidationWeather (int &, int , int , string &);
void sanitationFunction (double &);
void initialRatPopulationInput (int &);
void deathOverpopulationFunction (int &, int &);
void initialDeathFunction (int &, int &, int &, int &);
void overpopulationFunction (int &, int &, int &);
void weatherMenu ();
void populationChange (int &, int &, int &, int &, int &, double &, int &, string &);
void weatherChoice (int &, string &);
void birthrate (double &, int &, double &);
void deathrate (double &, int &, double &);
void populationUpdate (int &, int &, int &, int &);
void tableFunction (int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &);
void dashLoop();
void line1();
void weatherTypeStrings(string &, int &);
void line(int , string &, int &, int &, int &, int &);
void finalLine(int &, int &);
void fileClear();
void lineFile(int , string &, int &, int &, int &, int &, ofstream &);
void tableFunctionFile (int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, ofstream &); //good
void dashLoopFile(ofstream &);
void line1File(ofstream &);

int main() //Begin the program
{
    fileClear();
    int f = 0; //index variable
    while (f < 10) //allows simulation to be run 10 times
    {
    int initialRatPopulation = 0;
    initialRatPopulationInput(initialRatPopulation);
    int ratPopulation = initialRatPopulation;
    double sanitation = 0;
    sanitationFunction(sanitation);
    int capacity = static_cast<int>(10 * sanitation);
    int deathsweek1 (0), deathsweek2(0), deathsweek3(0);
    int birthsweek1 (0), birthsweek2(0), birthsweek3(0);
    int overpopulation (0);
    overpopulationFunction (overpopulation, initialRatPopulation, capacity);
    initialDeathFunction(overpopulation, deathsweek1, deathsweek2, deathsweek3);
    weatherMenu();
    int weatherWeek1 (0), weatherWeek2 (0), weatherWeek3 (0);
    string weatherString1 = "week 1: ", weatherString2 = "week 2: ", weatherString3 = "week 3: ";
    int finalPopulationWeek1 (0), finalPopulationWeek2 (0), finalPopulationWeek3 (0);
    populationChange (deathsweek1, ratPopulation, capacity, overpopulation, birthsweek1, sanitation, weatherWeek1, weatherString1);
    populationUpdate (ratPopulation, finalPopulationWeek1, birthsweek1, deathsweek1);
    populationChange (deathsweek2, finalPopulationWeek1, capacity, overpopulation, birthsweek2, sanitation, weatherWeek2, weatherString2);
    populationUpdate (finalPopulationWeek1, finalPopulationWeek2, birthsweek2, deathsweek2);
    populationChange (deathsweek3, finalPopulationWeek2, capacity, overpopulation, birthsweek3, sanitation, weatherWeek3, weatherString3);
    populationUpdate (finalPopulationWeek2, finalPopulationWeek3, birthsweek3, deathsweek3);
    tableFunction (initialRatPopulation, finalPopulationWeek1, finalPopulationWeek2, finalPopulationWeek3, birthsweek1, birthsweek2, birthsweek3,
                   deathsweek1, deathsweek2, deathsweek3, weatherWeek1, weatherWeek2, weatherWeek3);
    finalLine(initialRatPopulation, finalPopulationWeek3);
    f++;//add 1 index
    ofstream outfile;
    outfile.open("LastSim.txt", ios::app); //opens the file LastSim.txt, if it is not already there, the file will be created.
    tableFunctionFile (initialRatPopulation, finalPopulationWeek1, finalPopulationWeek2, finalPopulationWeek3, birthsweek1, birthsweek2, birthsweek3,
                   deathsweek1, deathsweek2, deathsweek3, weatherWeek1, weatherWeek2, weatherWeek3, outfile); //outputs the table to the file.
    outfile.close(); //closes the output file.
    }
}

//Precondition: Must have ofstream file open.
//Postcondition: Writes the dashed line of each table to the output file.
void dashLoopFile(ofstream &outfile)
{
    int i = 0;
    while (i < 38)
    {
        outfile <<"-";
        i++;
    }
    outfile << endl;
}

//Precondition: Must have ofstream file open. All variables must also be defined
//Postcondition: Writes the lines of the table to the output file.
void lineFile (int week, string &weatherType, int &initialPopulation, int &birthsweek, int &deathsweek, int &finalPopulation, ofstream &outfile)
{
    outfile << setw(4) << right <<week;
    outfile << setw(8) << left << weatherType;
    outfile << setw(6) << right << initialPopulation;
    outfile << setw(7) << right << birthsweek;
    outfile << setw(7) << right << deathsweek;
    outfile << setw(6) << right << finalPopulation <<endl;
}

//Precondition: Must have ofstream file open.
//Postcondition: Writes the heading line of each table to the output file.
void line1File(ofstream &outfile)
{
    outfile << setw(4) << right <<"Week";
    outfile << setw(8) << right << "Weather";
    outfile << setw(6) << right << "Begin";
    outfile << setw(7) << right << "Births";
    outfile << setw(7) << right << "Deaths";
    outfile << setw(6) << right << "Final" <<endl;
}


//Preconditions: Must have initialRatPopulation, the weather for each week entered by the user, and the final population, births, and deaths of all three weeks
//calculated as integers. Must have an ofstream file open.
//Postcondition:  Outputs a well formated table to a the text file showing all of the variables mentioned in the precondition.
void tableFunctionFile (int &initialRatPopulation, int &finalPopulationWeek1, int &finalPopulationWeek2, int &finalPopulationWeek3, int &birthsweek1,
                     int &birthsweek2, int &birthsweek3, int &deathsweek1, int &deathsweek2, int &deathsweek3, int &weatherWeek1, int &weatherWeek2, int &weatherWeek3, ofstream& outfile)
{
    string weatherType1(""), weatherType2(""), weatherType3("");
    weatherTypeStrings(weatherType1, weatherWeek1);
    weatherTypeStrings(weatherType2, weatherWeek2);
    weatherTypeStrings(weatherType3, weatherWeek3);
    line1File(outfile);
    dashLoopFile (outfile);
    lineFile(1, weatherType1, initialRatPopulation, birthsweek1, deathsweek1, finalPopulationWeek1, outfile);
    lineFile(2, weatherType2, finalPopulationWeek1, birthsweek2, deathsweek2, finalPopulationWeek2, outfile);
    lineFile(3, weatherType3, finalPopulationWeek2, birthsweek3, deathsweek3, finalPopulationWeek3, outfile);
    outfile << endl;
}

//Precondition: the outfile stream must be declared
//Postcondition: Clears the file.
void fileClear()
{
    ofstream outfile;
    outfile.open("LastSim.txt", ios::trunc);
    outfile << "";
    outfile.close();
}

//Precondition: No precondition
//Postcondition: Twenty blank lines are output to the screen
void printManyLines()
{
    int i = 0;
    while (i < 20)
    {
        cout <<endl;
        i++;
    }
}

//Precondition: Initial population must be found and the finalPopulation must be calculated.
//Postcondition: Outputs a message telling people to either stay calm or abandon ship based on the final population
//compared to the initial population
void finalLine(int &initialPopulation, int &finalPopulation)
{
    int thresholdPopulation = static_cast<int>(initialPopulation * 1.15);
    if (finalPopulation > thresholdPopulation)
    {
        cout << "You should abandon ship." <<endl;
    }
    else
    {
        cout << "Everyone should stay calm." << endl;
    }
    cout << "Press Enter to continue" << endl;
    cin.get();
    printManyLines();
}

//Precondition: Must have input for weather type, initial population, births for that week, deaths for that week, and final population of that week.
//Postcondition:  The values entered in the precondition are output in the correct table format in a row.
void line (int week, string &weatherType, int &initialPopulation, int &birthsweek, int &deathsweek, int &finalPopulation)
{
    cout << setw(4) << right <<week;
    cout << setw(8) << left << weatherType;
    cout << setw(6) << right << initialPopulation;
    cout << setw(7) << right << birthsweek;
    cout << setw(7) << right << deathsweek;
    cout << setw(6) << right << finalPopulation <<endl;
}

//Precondition: None
//Postcondition: Output's table header
void line1()
{
    cout << setw(4) << right <<"Week";
    cout << setw(8) << right << "Weather";
    cout << setw(6) << right << "Begin";
    cout << setw(7) << right << "Births";
    cout << setw(7) << right << "Deaths";
    cout << setw(6) << right << "Final" <<endl;
}

//Precondition: None
//Postcondition: Outputs the correct number of dashed lines for the table.
void dashLoop()
{
    int i = 0;
    while (i < 38)
    {
        cout <<"-";
        i++;
    }
    cout << endl;
}

//Precondition: Must have a string variable for weather type, and the weather for the week [1-3] for calm, hot, or stormy.
//Postcondition: Sets the weatherType string to "Calm", "Hot", or "Stormy" based on the weather input for the week.
void weatherTypeStrings(string &weatherType, int &weatherweek)
{
    switch(weatherweek)
    {
        case 1:
            weatherType = " Calm";
            break;
        case 2:
            weatherType = " Hot";
            break;
        case 3:
            weatherType = " Stormy";
            break;
    }
}

//Preconditions: Must have initialRatPopulation, the weather for each week entered by the user, and the final population, births, and deaths of all three weeks
//calculated as integers.
//Postcondition:  Outputs a well formated table showing all of the variables mentioned in the precondition.
void tableFunction (int &initialRatPopulation, int &finalPopulationWeek1, int &finalPopulationWeek2, int &finalPopulationWeek3, int &birthsweek1,
                     int &birthsweek2, int &birthsweek3, int &deathsweek1, int &deathsweek2, int &deathsweek3, int &weatherWeek1, int &weatherWeek2, int &weatherWeek3)
{
    string weatherType1(""), weatherType2(""), weatherType3("");
    weatherTypeStrings(weatherType1, weatherWeek1);
    weatherTypeStrings(weatherType2, weatherWeek2);
    weatherTypeStrings(weatherType3, weatherWeek3);
    line1();
    dashLoop ();
    line(1, weatherType1, initialRatPopulation, birthsweek1, deathsweek1, finalPopulationWeek1);
    line(2, weatherType2, finalPopulationWeek1, birthsweek2, deathsweek2, finalPopulationWeek2);
    line(3, weatherType3, finalPopulationWeek2, birthsweek3, deathsweek3, finalPopulationWeek3);
}


//Precondition: Must have calculated the currentPopulation, finalPopulation, the births and the deaths for that week.
//Postcondition: Sets the finalPopulation to population after taking into account births and deaths for the week.
void populationUpdate(int &currentPopulation, int &finalPopulation, int &birthsweek, int &deathsweek)
{
    finalPopulation = (currentPopulation + birthsweek) - deathsweek;
    finalPopulation = (finalPopulation > 0) ? finalPopulation : 0;
}

//Precondition: deathRate must be be a double variable, must have values for weatherWeek, and sanitation.
//Postcondition:  deathRate becomes a double value based on weatherWeek and sanitation.
void deathrateFunction(double &deathrate, int &weatherWeek, double &sanitation)
{
    if (sanitation < 4)
    {
        switch (weatherWeek)
        {
            case 1:
                deathrate = .07;
                break;
            case 2:
                deathrate = .36;
                break;
            case 3:
                deathrate = .55;
                break;
        }
    }
    else if (sanitation >= 4 && sanitation < 7)
    {
        switch (weatherWeek)
        {
            case 1:
                deathrate = .06;
                break;
            case 2:
                deathrate = .32;
                break;
            case 3:
                deathrate = .50;
                break;
        }
    }
    else if (sanitation >= 7)
    {
        switch (weatherWeek)
        {
            case 1:
                deathrate = .05;
                break;
            case 2:
                deathrate = .28;
                break;
            case 3:
                deathrate = .45;
                break;
        }
    }
}

//Precondition: birthRate must be be a double variable, must have values for weatherWeek, and sanitation.
//Postcondition:  birthRate becomes a double value based on weatherWeek and sanitation.
void birthrateFunction(double &birthrate, int &weatherWeek, double &sanitation)
{
    if (sanitation < 4)
    {
        switch (weatherWeek)
        {
            case 1:
                birthrate = .14;
                break;
            case 2:
                birthrate = .05;
                break;
            case 3:
                birthrate = .01;
                break;
        }
    }
    else if (sanitation >= 4 && sanitation < 7)
    {
        switch (weatherWeek)
        {
            case 1:
                birthrate = .16;
                break;
            case 2:
                birthrate = .06;
                break;
            case 3:
                birthrate = .02;
                break;
        }
    }
    else if (sanitation >= 7)
    {
        switch (weatherWeek)
        {
            case 1:
                birthrate = .18;
                break;
            case 2:
                birthrate = .07;
                break;
            case 3:
                birthrate = .03;
                break;
        }
    }
}

//Precondition: Must have integer variable weatherWeek defined, and string weatherString defined.
//Postcondition:  weatherWeek variable is updated from user input, and is validated.
void weatherChoice(int &weatherWeek, string &weatherString)
{
    string msg = "The weather has been set to 1. Calm Weather.";
    cout << "Enter the weather conditions for " << weatherString;
    cin >> weatherWeek;
    choiceValidationWeather(weatherWeek, 1, 3, msg);
}

//Precondition: Must have int deathWeek, population, capacity, overpopulation, birthsweek, and weather week defined, as well as
//double sanitation, and string weatherString defined.
//Postcondition: the births for the week will updated, the deaths for the week will update, all based on the effective
//rat population, sanitation level, and weather.
void populationChange (int &deathsWeek, int &population, int &capacity, int &overpopulation, int &birthsWeek, double &sanitation, int &weatherWeek, string &weatherString)
{
    weatherChoice(weatherWeek, weatherString);
    double birthrate = 0;
    birthrateFunction(birthrate, weatherWeek, sanitation);
    int useRatPopulation = (overpopulation > 0) ? capacity : population;
    birthsWeek = birthrate * useRatPopulation;
    double deathrate = 0;
    deathrateFunction(deathrate, weatherWeek, sanitation);
    int newdeathsweek = 0;
    newdeathsweek = static_cast<int>(deathrate * useRatPopulation);
    deathsWeek = newdeathsweek + deathsWeek;
}

//Precondition: None
//Postcondition: Displays a menu for the weather.
void weatherMenu()
{
    cout << "Weather options: " << endl
         << "1 = Calm Weather" << endl
         << "2 = Hot Weather" << endl
         << "3 = Stormy Weather" << endl;
}

//Precondition: Population must have a value and capacity must be calculated, overpopulation must be a defined variable.
//Postcondition: Overpopulation will have an integer value.
void overpopulationFunction(int &overpopulation, int &population, int &capacity)
{
    overpopulation = (population - capacity);
    overpopulation = (overpopulation > 0) ? overpopulation : 0;
}

//Precondition: Must have overpopulation calculated, and defined variables for deathsWeek1, deathsWeek2, and deathsWeek3/
//Postcondition: sets the initial value for deaths for the week for weeks 1-3.
void initialDeathFunction(int &overpopulation, int &deathsweek1, int &deathsweek2, int &deathsweek3)
{
    if (overpopulation > 0)
    {
        deathOverpopulationFunction(overpopulation, deathsweek1);
        deathOverpopulationFunction(overpopulation, deathsweek2);
        deathOverpopulationFunction(overpopulation, deathsweek3);
        deathsweek3 = deathsweek3 + (overpopulation % 3);
    }
}


//Precondition: Must have overpopulation value, and integer variable for deathweek.
//Postcondition: Sets deathWeek to 1/3 overpopulation.
void deathOverpopulationFunction(int &overpopulation, int &deathweek)
{
    deathweek = overpopulation / 3;
}

//Precondition: Must have a defined integer for intitialRatPopulation.
//Postcondition: initialRatPopulation becomes a value input by the user, and is validated.
void initialRatPopulationInput(int &initialRatPopulation)
{
    string msg = "The starting population is invalid.";
    bool loopFlag = 0;
    do //validation loop for room choice
    {
	cout << "Enter the starting rat population: ";
	cin >> initialRatPopulation;
	choiceValidationInteger(initialRatPopulation, 0, 99999 , msg, loopFlag);
    } while (loopFlag == 0);
}

//Precondition: Must have a defined double for sanitation.
//Postcondition: sanitation becomes a value input by the user, and is validated.
void sanitationFunction(double &sanitation)
{
    string msg = "The sanitation level has been set to 10.";
    cout << "Enter the sanitation level (0-10): ";
    cin >> sanitation;
    choiceValidationSanitation(sanitation, 0, 10, msg);
}

//Preconditions: Must have a selection integer variable, and a defined integer upper and lower range. A string message must also
//be defined.
//Postcondition: validates that the user input for the selection is an integer within the range and if it is not, a message will display
//and the selection will be set to 1.
void choiceValidationWeather(int &selection, int lowerRange, int upperRange, string &msg)
{
    if((cin.fail())||((selection > upperRange) ||(selection < lowerRange))) //if the input is invalid or not in range, will repeat choice selection.
        {
            cout << msg << endl;
            selection = 1;
        }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

//Preconditions: Must have a selection double variable, and a defined integer upper and lower range. A string message must also
//be defined.
//Postcondition: validates that the user input for the selection is a double within the range and if it is not, a message will display
//and the selection will be set to 10 if the input is higher than 10, and end the program if the input is less than 0.
void choiceValidationSanitation(double &selection, int lowerRange, int upperRange, string &msg)
{
    if((cin.fail())||(selection > upperRange)) //if the input is invalid or not in range, will repeat choice selection.
        {
            cout << msg << endl;
            selection = 10;
        }
    else if (selection < 0)
    {
        cout << "The ship is too clean for rats to survive.  Simulation ending.";
        exit(0);
    }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

//Preconditions: Must have a selection double variable, and a defined double upper and lower range. A string message must also
//be defined.  A boolean variable must also be defined.
//Postcondition: Validates that the user input for the selection is an integer within the range and if it is not, a message will appear and the boolean variable will be set to 0.
void choiceValidationInteger(int &selection, int lowerRange, int upperRange, string &msg, bool &validChoice)
{
    validChoice = 1;
    if((cin.fail())||((selection > upperRange) ||(selection < lowerRange))) //if the input is invalid or not in range, will repeat choice selection.
        {
            cout << msg << endl;
            validChoice = 0;
        }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}
