#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <regex>
#include <conio.h>

using namespace std;

int num [6];
int *randomArray = new int[49]; //dynamic array reservation
int i; //variable for functions checkInteger () and myNumbers ()


// CHECK IF A STRING IS INTEGER
void checkInteger ()
{
    string stringsArray [6];
 
    while (true)
    {
        cin >> stringsArray[i];
        regex isInteger("\\D"); // \\D: matches any non-digit characters
        bool result = regex_search(stringsArray[i], isInteger);
    
        if(result)
        {   
            cout << "Input value " << stringsArray[i] << " is not correct. Try again." << endl;
        }
        else
        {   
            num[i] = stoi(stringsArray[i]); 

            if (num[i] < 1 ||  num[i] > 49) // condition for check range od numbers
            {
                cout << "Input value " << stringsArray[i] << " is not correct. Try again." << endl;
            } 
            else 
            {
                break; 
            }    
        }
    } 
}

// CHECK REPEATED NUMBERS
void repeatedNum () 
{
    checkInteger ();
    
    for (int j = 0; j<i; j++) // check repeated numbers
    {
        while (num[j] == num[i]) 
        {
            cout << "Number " << num[i] << " is repeated. Try entering a different number." << endl;
            repeatedNum ();
        }              
    }            
}

// TITLE AND PRINT MY NUMBERS
void myNumbers () 
{   
    cout << "\n\n---------------------------------------------------------------------------------------------" << endl;
    cout << "Welcome in my lottery. Today you can win 1 000 000 $. Good luck." << endl;
    cout << "\nThe numbers must be positive integer value without plus sings like '+' and cannot be repeated.\nPlease write your 6 numbers from 1 to 49: ";

    for (i = 0; i<6; i++) 
    { 
        repeatedNum ();
    }

    cout << "\nYou entered the following numbers: ";
    
    for (int k = 0; k < 6; k++)  // Loop for print our numbers
    {
        cout << num[k] << " ";
    }
}

// RANDOM NUMBERS GENERATOR
void numbersGenerator () 
{
    random_device rd; // class is used to obtain a seed value for the random number generator
    mt19937 randomEngine(rd()); // class is a random number generation engine that produces random numbers with a uniform distribution.
    uniform_int_distribution <int> distr(1, 49); // class is used to generate random integers within a given range
    bool checkNum; // variable for help
    int howMany = {0}; // how many draws were made
   
    for (int i=1; i<=6; i++) // loop for randomizing numbers
    { 
        do 
        {
            int number = distr(randomEngine); // function for generate random numbers
            checkNum = {true};

            for (int j=1; j<=howMany; j++) // loop to check for number repetitions
            { 
                if (number == randomArray[j-1]) 
                { 
                    checkNum = false;
                } 
            }
            
            if (checkNum == true) // condition for entering the correct numbers into the array
            { 
                randomArray[howMany] = number;
                howMany++; 
            }
        } 
        while (checkNum != true);
    }

    cout << "\nLottery numbers: ";
    
    for (int i=0; i < howMany; i++)  // loop to print the entire array
    {
		cout << randomArray[i] << " ";
	}
}

// FUNCTION FOR CALCULATE POINTS
void points () 
{   int i;
    int j;
    vector <int> sameNumbers; // vector with same numbers

    for (i = 0; i<6; i++)  // Loop for check and add same numbers to vector
    {
         for (j = 0; j<6; j++)
        {
            if (num[i] == randomArray[j]) 
            {
                sameNumbers.push_back(num[i]);   
            }
        }   
    }

    if (sameNumbers.empty() == true) // Condition for check amount of same numbers in vector 
    {
        cout << "\n\nI'm sorry, you didn't get any numbers. Do you wanna try again? [Y/N]  ";
    } 
    else if (sameNumbers.size() == 1)
    {
        cout << "\n\nCongratulations, you got " << sameNumbers.size() << " number: " << sameNumbers.at(0) << ". Do you wanna try again? [Y/N]  ";
    }
    else 
    {
        cout << "\n\nCongratulations, you got " << sameNumbers.size() << " numbers: "; 

        for (size_t k = 0; k<sameNumbers.size(); k++)
        {
            cout << sameNumbers.at(k) << " ";
        };

        cout << ". Do you wanna try again? [Y/N]  " << endl; 
    }
}

// FUNCTION FOR PLAY MORE OR QUIT GAME
int tryAgain () 
{
    char play = getch(); // variable for "Yes or Not?"
   
    if (play == 'Y' || play == 'y') 
    {
        myNumbers ();
        numbersGenerator ();
        points ();
        tryAgain ();
    }
    else if (play == 'N' || play == 'n') 
    {  
        cout << "\nExiting the lottery."; 
        return 0;
    }
    else 
    {
        cout << "\nWrong answer. Do you wanna try again? [Y/N] "; 
        tryAgain ();
    }

    return 0;         
}

//MAIN FUNCTION
int main () 
{  
    myNumbers ();
    numbersGenerator ();
    points ();
    tryAgain ();
    delete [] randomArray;
    
    return 0;
};


