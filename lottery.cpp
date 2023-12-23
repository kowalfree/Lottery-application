#include <iostream>
#include <random>


using namespace std;

int num1, num2, num3, num4, num5, num6;

// WRITE MY OWN NUMBERS

void myNumbers () {

cout<<"Write your 6 numbers from 1 to 49. The numbers cannot be repeated."<< endl;
cin >> num1 >> num2 >> num3 >> num4 >> num5 >> num6; 

if (num1 < 1 || num1 > 49) {cout<<"Number " << num1 << " is not in the range 1 to 49"<< endl;
} else if (num2 < 1 || num2 > 49) {cout<<"Number " << num2 << " is not in the range 1 to 49"<< endl;
} else if (num3 < 1 || num3 > 49) {cout<<"Number " << num3 << " is not in the range 1 to 49"<< endl;
} else if (num4 < 1 || num4 > 49) {cout<<"Number " << num4 << " is not in the range 1 to 49"<< endl;
} else if (num5 < 1 || num5 > 49) {cout<<"Number " << num5 << " is not in the range 1 to 49"<< endl;
} else if (num6 < 1 || num6 > 49) {cout<<"Number " << num6 << " is not in the range 1 to 49"<< endl;
} else {cout<<"You provided the following numbers: "<< num1 <<" "<< num2 <<" "<< num3 <<" "<< num4 <<" "<< num5 <<" "<< num6 << endl;}

}

// RANDOM NUMBERS GENERATOR

void numbersGenerator () {

    random_device rd; // class is used to obtain a seed value for the random number generator
    mt19937_64 randomEngine(rd()); // class is a random number generation engine that produces random numbers with a uniform distribution.
    uniform_int_distribution <int> distr(1, 49); // class is used to generate random integers within a given range
    bool checkNum; // variable for help
    int *randomArray = new int[6]; //array reservation
    int howMany = {0}; // how many draws were made

    // loop for randomizing numbers
    for (int i=1; i<=6; i++) { 
            int number = distr(randomEngine); // function for generate random numbers
            checkNum = true; 

        do {
            // loop to check for number repetitions
            for (int j=1; j<=howMany; j++) { 

                // condition checking number repetitions
                if (number == randomArray[j]) { 
                    checkNum = false;
                } 
            }
            
            // a loop for entering the correct numbers into the array
            if (checkNum == true) { 
                howMany++; 
                randomArray[howMany-1] = number;
            }

        } while (checkNum != true);
    }
    cout<<"Lottery numbers: ";
    
    // loop to print the entire array
    for (int i=0; i < howMany; i++) 
    {
		cout<<randomArray[i]<<" ";
	}
}

//MAIN FUNCTION

int main () {

myNumbers ();
numbersGenerator ();

    return 0;
};