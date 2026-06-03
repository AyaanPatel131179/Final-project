//Ayaan Patel, Final Project: Personal Finance Calculator, 6/2/2026, Extra - Reading/Writing Files

//libraries
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;


//this function tries to open the input file and read all the saved values
//returns true if it worked, false if the file doesnt exist
bool loadData(string filename,
              double &salary,
              double &taxRate,
              double &rent,
              double &car,
              double &food,
              double &subscriptions,
              double &entertainment,
              double &other)
{
    ifstream inFile(filename);

    //stops and returns false if it doesnt open the file
    if (!inFile)
    
        return false;

    string line;

    //go through each line and split it at the = sign
    while (getline(inFile,line)){

        size_t pos = line.find('=');

        // skip the line if there is no = sign
        if (pos == string::npos)

            continue;

        string key = line.substr(0, pos);


        // wrap stod in a try/catch so bad data doesnt crash everything
        double value;
        try
        {
            value = stod(line.substr(pos + 1));
        }
        catch (...)
        {
            // if the value is messed up just skip that line
            continue;
        }



        //match the key to the right variable
        if (key == "salary")

            salary = value;

        else if (key == "tax")

            taxRate = value;

        else if (key == "rent")

            rent = value;

        else if (key == "car")

            car = value;

        else if (key == "food")

            food = value;

        else if (key == "subscriptions")

            subscriptions = value;

        else if (key == "entertainment")

            entertainment = value;

        else if (key == "other")

            other = value;
    }

    inFile.close();
    return true;
}


//saves whatever the user typed in so we dont have to ask again next time
void saveInput(string filename,
               double salary,
               double taxRate,
               double rent,
               double car,
               double food,
               double subscriptions,
               double entertainment,
               double other)
{
    ofstream outFile(filename);

    outFile << "salary=" << salary << endl;
    outFile << "tax=" << taxRate << endl;
    outFile << "rent=" << rent << endl;
    outFile << "car=" << car << endl;
    outFile << "food=" << food << endl;
    outFile << "subscriptions=" << subscriptions << endl;
    outFile << "entertainment=" << entertainment << endl;
    outFile << "other=" << other << endl;

    outFile.close();
}


//writes the full budget report to a txt file so you can look at it later
void saveReport(double salary,
                double monthlyGross,
                double takeHome,
                double totalExpenses,
                double leftover,
                double needsBudget,
                double wantsBudget,
                double savingsBudget,
                double yearlySavings,
                int score)
{
    ofstream outFile("budget_report.txt");

    outFile << fixed << setprecision(2);

    outFile << "      $PERSONAL FINANCE REPORT$ \n";
 

    //income section
    outFile << "Yearly Salary:          $" << salary << endl;
    outFile << "Monthly Gross Income:   $" << monthlyGross << endl;
    outFile << "Monthly Take Home Pay:  $" << takeHome << endl;
    outFile << "Total Expenses:         $" << totalExpenses << endl;
    outFile << "Money Left Over:        $" << leftover << endl;

    // what the 50/30/20 rule says you should be spending
    outFile << "\n-Recommended Budget-\n";
    outFile << "Needs 50%:            $" << needsBudget << endl;
    outFile << "Wants 30%:            $" << wantsBudget<< endl;
    outFile << "Savings 20%:          $" << savingsBudget << endl;
    outFile << "Yearly Savings Goal:    $" << yearlySavings << endl;

    outFile << "\nBudget Health Score: " <<score<< "/100\n";

    outFile.close();
}


int main(){


    //makes all dollar amounts show 2 decimal places bc money
    cout << fixed << setprecision(2);


    //all the variables start at 0
    double salary =0;
    double taxRate =0;
    double rent =0;
    double car =0;
    double food =0;
    double subscriptions =0;
    double entertainment =0;
    double other =0;

    string inputFile = "budget_input.txt";



    cout << "    PERSONAL FINANCE CALCULATOR\n";

    // try to load saved data first before asking the user anything
    bool loaded = loadData(inputFile, salary, taxRate, rent, car, food, subscriptions, entertainment, other);

    if (loaded)
    {
        cout << "loaded data from " << inputFile << "\n\n";
    }
    else
    {
        //no file found so we ask the user to type everything in
        cout << "no budget_input.txt found.\n";
        cout << "Enter your info below.\n\n";

        cout << "Yearly Salary: $";
        cin >> salary;

        cout << "Estimated Tax Rate %: ";
        cin >> taxRate;

        cout << "\nMonthly Expenses\n";

        cout << "Rent/Mortgage: $";
        cin >> rent;

        cout << "Transport/Car: $";
        cin >> car;

        cout << "Food/Groceries: $";
        cin >> food;

        cout << "Subscriptions: $";
        cin >> subscriptions;

        cout << "Entertainment: $";
        cin >> entertainment;

        cout << "Other Expenses: $";
        cin >> other;

        //saves what they entered so next time it loads automatically
        saveInput(inputFile, salary, taxRate, rent, car, food, subscriptions, entertainment, other);

        cout << "\nInputs saved to budget_input.txt\n";
    }





    //all the math

    double monthlyGross = salary/12.0;

    //subtract the tax percentage to get takehome
    double takeHome = monthlyGross * (1-taxRate/100.0);

    double totalExpenses = rent + car + food + subscriptions + entertainment + other;

    double leftover = takeHome - totalExpenses;

    //50/30/20 rule breakdown

    double needsBudget = takeHome *0.50;
    double wantsBudget = takeHome *0.30;
    double savingsBudget = takeHome *0.20;
    double yearlySavings = savingsBudget *12;




    //score starts at 100 and goes down bc of bad spending habits
    int score = 100;

    if (rent > takeHome *0.30)
        score -= 15;

    if (food > takeHome *  0.15)
        score -= 10;

    if (subscriptions > 50)
        score -= 5;

    if (entertainment > takeHome * 0.10)
        score -= 10;

    // big penalty if you spend more than you make
    if (totalExpenses > takeHome)
        score -= 30;

    // dont let the score go below 0
    if (score < 0)
        score = 0;





    //prints to console
    cout << "          BUDGET SUMMARY\n";


    cout << "\nYearly Salary:          $" << salary;
    cout << "\nMonthly Gross Income:   $" << monthlyGross;
    cout << "\nMonthly Take Home Pay:  $" << takeHome;

    cout << "\n\nTotal Expenses:         $" << totalExpenses;
    cout << "\nMoney Left Over:        $" << leftover;

    cout << "\n\n- 50/30/20 Budget Rule -";
    cout << "\nNeeds (50%):            $" << needsBudget;
    cout << "\nWants (30%):            $" << wantsBudget;
    cout << "\nSavings (20%):          $" << savingsBudget;
    cout << "\nYearly Savings Goal:    $" << yearlySavings;

    cout << "\n\n  Advice  \n";


    if (rent > takeHome * 0.30)
        cout << "rent is higher than it should be.\n";

    if (food > takeHome * 0.15)
        cout << "food spending is a bit high.\n";

    if (subscriptions > 50)
        cout << "you might want to cut some subscriptions.\n";

    if (entertainment > takeHome * 0.10)
        cout << "entertainment spending is pretty high.\n";

    if (totalExpenses > takeHome)
        cout << "WARNING: You are spending more than you make.\n";
    else
        cout << "spending is within your income.\n";

    if (leftover >= savingsBudget)
        cout << "you are hitting your savings goal.\n";
    else
        cout << "try to save a little more each month.\n";

    cout << "\nBudget Health Score: " << score << "/100\n";




    // save everything to the report file
    saveReport(salary, monthlyGross, takeHome, totalExpenses, leftover,
               needsBudget, wantsBudget, savingsBudget, yearlySavings, score);

    cout << "\nReport saved to budget_report.txt\n";



    return 0;
}