/**
 *   @file: car-dealer.cc
 * @author: Brody Reynolds
 *   @date: 11/1/2021
 *  @brief: A program where the user is able to buy a single car
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

///function prototypes

/**
 * chosenModel - finds and returns the letter, in upper case, entered from user
 * @param  none - none
 * @return model - returns the model letter from user input
 */
char chosenModel();

/**
 * selections - returns the currently selected model, total price, and chosen option
 * @param model, total, and options - returns the model type, total price, and the chosen options for car
 * @return none - void
 */
void selections(char model, double total, vector<string> options);

/**
 * equalValue - checks to see if the value is equal than it will return true
 * @param s1, s2 - checks strings to see they are equal
 * @return bool - true or false
 */
bool equalValue(string s1, string s2);

/**
 * character - turns characters into upper case than compares
 * @param ch1, ch2 - the values given to see if they return true or false if they are equal or there not
 * @return bool - true or false
 */
bool character(char ch1, char ch2);

/**
 * availableOptions - takes files data and returns the available car options and prices
 * @param options and optionPrices - vectors data which contains the car options and prices from file data
 * @return none - void
 */
void availableOptions(vector<string> options, vector<int> optionPrices);

int main()
{

    int choice = 0;

    ifstream in("options.txt"); // Opens file
    if (in.fail())              // If fails to open
    {
        cout << "Error: no file located" << endl;
        exit(0);
    }

    char model = ' '; // Default value for selected car model

    vector<int> optionPrice;       // Options prices from file
    vector<string> options;        // Option from file
    vector<string> currentOption; // Currently selected information from user

    double total = 0.0; // Default total of currently selected value

    while (!in.eof())
    {

        string accessories;
        int price;
        in >> price; // Grabs prices

        getline(in, accessories); // Grabs options

        if (accessories[0] == ' ')
        {
            accessories = accessories.substr(1, accessories.length() - 1); // skips white space
        }

        optionPrice.push_back(price);   // Fills vector "optionPrice" with the prices
        options.push_back(accessories); // Fills vector "options" with the accessories for car
    }

    double ePrice = 10000.0;
    double lPrice = 12000.0;
    double xPrice = 18000.0;

    do
    {
        cout << endl;
        selections(model, total, currentOption); // Displays current selection
        cout << endl;
        // Menu
        cout << "1. Select a model (E, L, X)" << endl;
        cout << "2. Display available options and prices" << endl;
        cout << "3. Add an option" << endl;
        cout << "4. Remove option" << endl;
        cout << "5. Cancel order" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice <= 0 || choice > 6) // If choice is not 1-6
        {
            cout << "Error: select a choice between 1 and 6" << endl;
        }

        else if (choice == 1)
        {
            if (model != ' ')
            {
                cout << "Model already chosen! Cancel order if you want a new model." << endl;
            }
            else // If current model is not chosen
            {
                model = chosenModel();

                if (model == 'E')
                {
                    total = ePrice; // Adds to total price
                }
                else if (model == 'X')
                {
                    total = xPrice;
                }
                else if (model == 'L')
                {
                    total = lPrice;
                }
            }
        }

        else if (choice == 2)
        {
            cout << "Prices for model (E, L, & X): $10000.00, $12000.00, $18000.00" << endl;
            cout << "Available Options: " << endl;
            cout << endl;

            availableOptions(options, optionPrice); // Displays available option
        }

        else if (choice == 3)
        {
            if (model != ' ')
            {
                string oName; // Inserted info from user

                cout << "Enter option: ";
                cin.ignore(); // Ignores newline
                getline(cin, oName);

                for (size_t i = 0; i < options.size(); i++) //Checks to see if the option is the same as inputted info
                {
                    if (equalValue(options[i], oName)) // Checks to see if values are equal. If the user already selected the value
                    {
                        bool currentlySelected = false;
                        for (size_t u = 0; u < currentOption.size(); u++)
                        {
                            if (equalValue(options[i], currentOption[u]))
                            {
                                currentlySelected = true; // 
                            }
                        }

                        if (!currentlySelected) // Adds the option to currently selected 
                        {
                            currentOption.push_back(options[i]);

                            total += optionPrice[i]; // Adds to the total
                        }
                    }
                }
            }
        }

        else if (choice == 4)
        {
            if (model != ' ')
            {
                string oName;

                cout << "Enter option: ";
                cin.ignore();
                getline(cin, oName);

                for (size_t i = 0; i < currentOption.size(); i++)
                {
                    if (equalValue(currentOption[i], oName))
                    {
                        // Removes the price of the selected option
                        for (size_t u = 0; u < options.size(); u++)
                        {
                            if (equalValue(currentOption[i], options[u]))
                            {
                                total -= optionPrice[u]; // Removes from the total
                            }
                        }
                        // Removes option from currently selected
                        currentOption.erase(currentOption.begin() + i);
                    }
                }
                cout << endl;
            }
        }

        else if (choice == 5) // Resets everything to default
        {
            currentOption.clear();
            model = ' ';
            total = 0;
            
            cout << endl;
        }

    } while (choice != 6);

    in.close(); // Closes file

    return 0;
}

void selections(char model, double total, vector<string> options)
{

    if (model == ' ')
    {
        cout << "NO MODEL SELECTED" << endl; // If no current selections
    }
    else
    {
        cout << "Model: " << model << ", $" << fixed << setprecision(2) << total << ",  ";
        cout << "Options: ";

        if (options.size() > 0)
        {

            for (size_t i = 0; i < options.size(); i++) 
            {

                if (i % 5 == 0) // Prints 5 options per line
                {
                    cout << endl;
                }

                cout << options.at(i); // Outputs option

                if (i < options.size() - 1) // Adds commas
                {
                    cout << ", ";
                }
            }
        }
        else
        {
            cout << "None";
        }
        cout << endl;
    }
}

bool character(char ch1, char ch2)
{
    ch1 = toupper(ch1); // Changes character to upper case
    ch2 = toupper(ch2);

    if (ch1 == ch2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char chosenModel()
{
    char model;

    cout << "Enter the model (E, L, X): ";
    cin >> model;
    cout << endl;

    if (model == ' ')
    {
        cout << "Enter the model (E, L, X): ";
        cin >> model;
        cout << endl;
    }
    else
    {

        while (model != ' ') 
        {
            char ch = toupper(model); // Takes model and upper cases

            if (ch == 'E' || ch == 'L' || ch == 'X')
            {
                return toupper(model);
            }
        }
    }
}

bool equalValue(string s1, string s2) // Checks if equal
{
    return (equal(s1.begin(), s1.end(), s2.begin(), &character) && s1.size() == s2.size());
}

void availableOptions(vector<string> options, vector<int> optionPrices)
{
    for (size_t i = 1; i < options.size(); i++)
    {
        cout << options[i - 1] << " ($" << optionPrices[i - 1] << ")     ";

        if (i % 3 == 0) // Prints out 3 available options per line
        {
            cout << endl;
        }
    }
}