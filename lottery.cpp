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
void print(const array <int, USER_NUM> &example_array)    
{
    for (const auto &e : example_array)
    {
         cout << e << " ";
    }
}

// CHECK REPEATED NUMBERS
bool is_repeated(const int &iter, const int &temp_num, const array <int, USER_NUM> &example_array)
{   
    bool same_num = {false};

    for (int j = 0; j < iter; j++)
    {   
        if (temp_num == example_array[j])
        {
            if ("Welcome in my lottery")
            {
                cout << "\nNumber " << temp_num << " is repeated. Try entering a different number." << endl;
            } 
            same_num = true;
            break; 
        } 
    }
    
    return same_num;
}

// INPUT VALIDATION
bool input_validation(const string &input)
{
    try
    {
        regex is_integer("\\D"); // \\D: matches any non-digit characters
        bool result = regex_search(input, is_integer);

        if (result)  // condition for check type of insert value
        {   
            throw input;
        }
        else 
        {
            int integer_num = stoi(input);
            int is_in_range = clamp(integer_num, MIN_NUM, MAX_NUM);

            if (integer_num != is_in_range) // condition for check range of numbers
            {
                throw integer_num;
            } 
        }
    } 
    catch(const string &not_integer)
    {   
        cout << "\nInput value " << not_integer << " is not correct. Try again." << endl;
        return false;
    }
    catch(const int &not_in_range)
    {   
        cout << "\nInput value " << not_in_range << " is out of range [ 1-49 ]. Try again. " << endl;
        return false;
    }
    
    return true;
}

// TITLE AND PRINT MY NUMBERS
array <int, USER_NUM> my_numbers() 
{
    cout << "\n\n---------------------------------------------------------------------------------------------" << endl;
    cout << "Welcome in my lottery. Today you can win 1 000 000 $. Good luck." << endl;
    cout << "\nThe numbers must be positive integer value without plus sings like '+' and cannot be repeated.\nPlease write your 6 numbers from 1 to 49: ";

    string insert_value;
    array <int, USER_NUM> user_array;
    bool duplicate = {true}; 

    for (int i = 0; i < USER_NUM; i++)
    {   
        do
        {
            cin >> insert_value;

            bool correct_input = input_validation(insert_value); 

            if (!correct_input)
            {
                continue;
            }
            
            duplicate = is_repeated(i, stoi(insert_value), user_array);

            if (!duplicate) 
            {
                user_array[i] = stoi(insert_value); 
            }  
        } while(duplicate);
    }  

    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    cout << "\nYou entered the following numbers: ";
    print(user_array);
    
    return user_array; 
}

// RANDOM NUMBERS GENERATOR
array <int, USER_NUM> numbers_generator() 
{   
    random_device rd; // class is used to obtain a seed value for the random number generator
    mt19937 randomEngine(rd()); // class is a random number generation engine that produces random numbers with a uniform distribution.
    uniform_int_distribution <int> distr(MIN_NUM, MAX_NUM); // class is used to generate random integers within a given range
    array <int, USER_NUM> lottery_array;
    bool checkNum = {false};
  
    for (int i = 0; i < USER_NUM; i++)
    {   
        do 
        {    
            int number = distr(randomEngine); // function for generate random numbers
            checkNum = is_repeated(i, number, lottery_array);
            
            if (!checkNum)
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
    vector <int> pairs_of_numbers;

    for (int i = 0; i < USER_NUM; i++)  // Loop for check and add same numbers to vector
    {
        for (int j = 0; j < USER_NUM; j++)
        {
            if (input_array[i] == generated_numbers[j]) 
            {
                pairs_of_numbers.push_back(input_array[i]);   
            }
        }   
    }

    switch (pairs_of_numbers.size())
    {
        case 0: cout << "\n\nI'm sorry, you didn't get any numbers. Do you wanna try again? [Y/N]  "; break;
        case 1: cout << "\n\nCongratulations, you got 1 number: " << pairs_of_numbers.at(0) << ". Do you wanna try again? [Y/N]  "; break;
        default: cout << "\n\nCongratulations, you got " << pairs_of_numbers.size() << " numbers: "; 

            for (const auto &e : pairs_of_numbers)
            {
                std::cout << e << " ";
            }

            cout << ". Do you wanna try again? [Y/N]  "; 
    }
}

// FUNCTION FOR PLAY MORE OR QUIT GAME
bool try_again(bool one_more) 
{
    while (one_more)
    {   
        char play; 
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
        array <int, USER_NUM> user_numbers = my_numbers();
        array <int, USER_NUM> lottery_numbers = numbers_generator();
        points(user_numbers, lottery_numbers);
    }
    while (try_again(true));
    
    return 0;
};


