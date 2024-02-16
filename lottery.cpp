#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

constexpr int USER_NUM = {6};
constexpr int MAX_NUM = {49};
constexpr int MIN_NUM = {1};

// PRINT ELEMENTS OF ARRAY
void print(const array <int, USER_NUM> &arr)
{
    for (const auto &e : arr)
    {
         cout << e << " ";
    }
}

// CHECK REPEATED NUMBERS
bool is_repeated(const int &iter, const int &temp_num, const array <int, USER_NUM> &example_array)
{   
    bool same_num = {false};

    for (int j = 0; j < iter; j++) // check repeated numbers
    {   
        if (temp_num == example_array[j])
        {
            cout << "\nNumber " << temp_num << " is repeated. Try entering a different number." << endl; 
            same_num = true;
            break; 
        } 
    }

    return same_num;
}

// INPUT VALIDATION
bool input_validation(const string &input, const int &output)
{
    try
    {
        regex isInteger("\\D"); // \\D: matches any non-digit characters
        bool result = regex_search(input, isInteger);

        if (result)  // condition for check type of insert value
        {   
            throw input;
        }

        int is_in_range = clamp(output, MIN_NUM, MAX_NUM);

        if (output != is_in_range) // condition for check range of numbers
        {
            throw output;
        } 
    } 
    catch(string not_integer)
    {   
        cout << "\nInput value " << not_integer << " is not correct. Try again." << endl;
        return false;
    }
    catch(int not_in_range)
    {   
        cout << "\nInput value " << not_in_range << " is out of range [ 1-49 ]. Try again: " << endl;
        return false;
    }

    return true;
}

// TITLE AND PRINT MY NUMBERS
array <int, USER_NUM> myNumbers() 
{
    cout << "\n\n---------------------------------------------------------------------------------------------" << endl;
    cout << "Welcome in my lottery. Today you can win 1 000 000 $. Good luck." << endl;
    cout << "\nThe numbers must be positive integer value without plus sings like '+' and cannot be repeated.\nPlease write your 6 numbers from 1 to 49: ";

    string insert_value;
    array <int, USER_NUM> user_array;

    for (int i = 0; i < USER_NUM; i++)
    {   
        while (true)
        {
            cin >> insert_value;

            if (i == (USER_NUM - 1)) // condition for clear input after insert all values
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }   

            int integer_num;
            integer_num = stoi(insert_value);

            bool correct_input = input_validation(insert_value, integer_num); // check if input value is integer and in range
            bool duplicate = is_repeated(i, integer_num, user_array); // check repeated numbers

            if (!correct_input || duplicate)
            {
                continue;
            }
            else 
            {
                user_array[i] = integer_num;
                break;  
            }  
        }
    }  
    
    cout << "\nYou entered the following numbers: ";
    print(user_array);
    
    return user_array; 
}

// RANDOM NUMBERS GENERATOR
array <int, USER_NUM> numbersGenerator() 
{   
    random_device rd; // class is used to obtain a seed value for the random number generator
    mt19937 randomEngine(rd()); // class is a random number generation engine that produces random numbers with a uniform distribution.
    uniform_int_distribution <int> distr(MIN_NUM, MAX_NUM); // class is used to generate random integers within a given range
    array <int, USER_NUM> lottery_array;
    bool checkNum = false;

    for (int i = 0; i < USER_NUM; i++) // loop for randomizing numbers
    {
         do 
        {   
            int number = distr(randomEngine); // function for generate random numbers

            for (int j = 0; j <= i; j++) // loop to check for number repetitions
            { 
                if (number == lottery_array[j]) 
                { 
                    checkNum = true;
                    break;
                } 
            }
            
            if (!checkNum) // condition for entering the correct numbers into the array
            { 
                lottery_array[i] = number;
            }
        } 
        while (checkNum);
    }

    cout << "\nLottery numbers: ";
    
    print(lottery_array); // loop to print the entire array

    return lottery_array;
}

// FUNCTION FOR CALCULATE POINTS
void points(const array <int, USER_NUM> &input_array, const array <int, USER_NUM> &generated_numbers) 
{   
    vector <int> sameNumbers; // vector with same numbers

    for (int i = 0; i < USER_NUM; i++)  // Loop for check and add same numbers to vector
    {
         for (int j = 0; j < USER_NUM; j++)
        {
            if (input_array[i] == generated_numbers[j]) 
            {
                sameNumbers.push_back(input_array[i]);   
            }
        }   
    }

    if (sameNumbers.empty()) // Condition for check amount of same numbers in vector 
    {
        cout << "\n\nI'm sorry, you didn't get any numbers. Do you wanna try again? [Y/N]  ";
    } 
    else if (sameNumbers.size() == 1)
    {
        cout << "\n\nCongratulations, you got 1 number: " << sameNumbers.at(0) << ". Do you wanna try again? [Y/N]  ";
    }
    else 
    {
        cout << "\n\nCongratulations, you got " << sameNumbers.size() << " numbers: "; 

        for (const auto &e : sameNumbers)
        {
            std::cout << e << " ";
        }

        cout << ". Do you wanna try again? [Y/N]  " << endl; 
    }
}

// FUNCTION FOR PLAY MORE OR QUIT GAME
bool tryAgain(bool one_more) 
{
    while (one_more)
    {   
        char play; // variable for "Yes or Not?"
        cin >> play; 
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
        if (play == 'Y' || play == 'y') 
        {
            break;
        }
        else if (play == 'N' || play == 'n') 
        {  
            cout << "\nExiting the lottery."; 
            one_more = false;
            break;
        }
        else 
        {
            cout << "\nWrong answer. Do you wanna try again? [Y/N] "; 
        }  
    }
    return one_more; 
}

//MAIN FUNCTION
int main() 
{  
    do
    {
        array <int, USER_NUM> user_numbers = myNumbers();
        array <int, USER_NUM> lottery_numbers = numbersGenerator();
        points(user_numbers, lottery_numbers);
    }
    while (tryAgain(true));
    
    return 0;
};


