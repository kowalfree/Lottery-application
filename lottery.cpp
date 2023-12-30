#include <iostream>
#include <random>
#include <vector>

using namespace std;

int num [6];
int *randomArray = new int[49]; //array reservation
char play = {'Y'}; // variable for "Yes or Not?"

// WRITE MY OWN NUMBERS

void myNumbers () 
{
    cout<<"\nWrite your 6 numbers from 1 to 49. The numbers cannot be repeated."<< endl;
    int i;

    for (i = 0; i<6; i++) 
    {
        cin >> num[i]; 
        // Condition for check range
        if (num[i] < 1 || num[i] > 49) 
        { 
            cout<<"Number " << num[i] << " is not in the range 1 to 49. Try entering a different number."<< endl;
            cin >> num[i]; 
        } 
        // Loop for check repeated numbers
        for (int j = 0; j<6; j++) 
        {
            if (j != i) 
            {
                if (num[j] == num[i]) 
                {
                    cout<<"Number " << num[j] << " is repeated. Try entering a different number."<< endl;
                    cin >> num[j]; 
                }     
            }              
        }      
    }

    // void repeat () 
// {
//     for (int i=0; i < 49; i++) 
//     {   
//         for (int j=0; j < 49; j++) 
//         {  
//             if (randomArray[i] == randomArray[j] && i!=j) 
//             {
//                 cout<<"repeat numbers: "<<randomArray[i]<<" ";
//             }
//         }
// 	}
// }

    cout<<"\nYou entered the following numbers: ";
     // Loop for print our numbers
    for (int k = 0; k < 6; k++) {
            
        cout<< num[k] <<" ";
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
   
    // loop for randomizing numbers
    for (int i=1; i<=6; i++) 
    { 
        do {
            int number = distr(randomEngine); // function for generate random numbers
            checkNum = {true};

            // loop to check for number repetitions
            for (int j=1; j<=howMany; j++) 
            { 
                // condition checking number repetitions
                if (number == randomArray[j-1]) 
                { 
                    checkNum = false;
                } 
            }
            // a loop for entering the correct numbers into the array
            if (checkNum == true) 
            { 
                randomArray[howMany] = number;
                howMany++; 
            }
        } while (checkNum != true);
    }
    cout<<"\nLottery numbers: ";
    
    // loop to print the entire array
    for (int i=0; i < howMany; i++) 
    {
		cout<<randomArray[i]<<" ";
	}
}

// FUNCTION FOR CALCULATE POINTS
void points () 
{   int i;
    int j;
    vector <int> sameNumbers; // VECTOR WITH SAME NUMBERS

    // Loop for check and add same numbers to vector
    for (i = 0; i<6; i++)
    {
         for (j = 0; j<6; j++)
        {
            if (num[i] == randomArray[j]) 
            {
                sameNumbers.push_back(num[i]);   
            }
        }   
    }

    // Condition for check amount of same numbers in vector
    if (sameNumbers.empty() == true) // 
    {
        cout<<"\n\nI'm sorry, you didn't get any numbers. Do you wanna try again? [Y/N]  ";
    } 
    else if (sameNumbers.size() == 1)
    {
        cout<<"\n\nCongratulations, you got "<< sameNumbers.size() <<" number: "<< sameNumbers.at(0)<< ". Do you wanna try again? [Y/N]  ";
    }
    else 
    {
        cout<<"\n\nCongratulations, you got "<< sameNumbers.size() <<" numbers: "; 

        for (size_t k = 0; k<sameNumbers.size(); k++)
        {
            cout << sameNumbers.at(k)<<" ";
        };

        cout<< ". Do you wanna try again? [Y/N]  ";
    }
}

// FUNCTION FOR PLAY MORE OR QUIT GAME
int tryAgain () 
{
    cin>> play;

    if (play == 'Y' || play == 'y') 
    {
        myNumbers ();
        numbersGenerator ();
        points ();
        tryAgain ();
    }
    else if (play == 'N' || play == 'n') 
    {   
       return 0;
    }
    else 
    {
        cout<<"\nWrong answer. Do you wanna try again? [Y/N] "; 
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


