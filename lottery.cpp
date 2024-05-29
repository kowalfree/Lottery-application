#include <iostream>
#include <string>
#include <set>
#include <random>
#include <regex>
#include <algorithm>

using namespace std;

constexpr int USER_NUM = {6};
constexpr int MAX_NUM = {49};
constexpr int MIN_NUM = {1};

void print(const set <int> &example_set)    
{
    for (const auto &e : example_set)
    {
          cout << " " << e ;;
    }
}

bool input_validation(const string &input)
{
    try
    {
        regex is_integer("\\D"); // \\D: matches any non-digit characters
        bool result = regex_search(input, is_integer);

        if (result)  
        {   
            throw input;
        }
        else 
        {
            int integer_num = stoi(input);
            int is_in_range = clamp(integer_num, MIN_NUM, MAX_NUM);

            if (integer_num != is_in_range) 
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

set <int> my_numbers() 
{
    string insert_value;
    set <int> user_set;
      
    do
    {
        cin >> insert_value;

        if (!input_validation(insert_value))
        {
            continue;
        }

        int temp_num = stoi(insert_value);

        if (user_set.count(temp_num))
        {
            cout << "\nNumber " << temp_num << " is repeated. Try entering a different number." << endl;
            continue;
        } 

        user_set.insert(temp_num);

    } while(user_set.size() < USER_NUM);
    
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return user_set; 
}

set <int> random_numbers()
{
    random_device rd; // class is used to obtain a seed value for the random number generator
    mt19937 randomEngine(rd()); // class is a random number generation engine that produces random numbers with a uniform distribution.
    uniform_int_distribution <int> distr(MIN_NUM, MAX_NUM); // class is used to generate random integers within a given range
    set <int> lottery_set;
    
    while (lottery_set.size() < USER_NUM)
    {
        int number = distr(randomEngine); 
        lottery_set.insert(number); 
    }

    return lottery_set;
};

set <int> points(const set <int> &input_set, const set <int> &generated_numbers) 
{   
    set <int> result;

    set_intersection(input_set.begin(), input_set.end(), generated_numbers.begin(), generated_numbers.end(), inserter(result, result.begin())); 

    (result.size() != 0)? cout << "\n\nCongratulations, you got " << result.size() << " number/s:" : cout << "\n\nI'm sorry, you didn't get any numbers";

    return result;
}

bool try_again() 
{
    char play; 
    do
    {   
        cin >> play; 
        auto one_more = toupper(play);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (one_more != 'Y' && one_more != 'N')
        {
            cout << "\nWrong answer. Do you wanna try again? [Y/N] ";
        }
        else if (one_more == 'N')
        {
            cout << "\nExiting the lottery."; return false;
        }

    } while (toupper(play) != 'Y' && toupper(play) != 'N');

    return true; 
}

int main() 
{  
    do
    {
        cout << "\n\n---------------------------------------------------------------------------------------------" << endl;
        cout << "Welcome in my lottery. Today you can win 1 000 000 $. Good luck." << endl;
        cout << "\nThe numbers must be positive integer value without plus sings like '+' and cannot be repeated.\nPlease write your 6 numbers from 1 to 49: ";
        
        auto user_numbers = my_numbers();
        cout << "\nYour numbers:";
        print(user_numbers);

        auto lottery_numbers = random_numbers();
        cout << "\nLottery numbers:";
        print(lottery_numbers);

        auto same_numbers = points(user_numbers, lottery_numbers); 
        print(same_numbers);

        cout << ". Do you wanna try again? [Y/N]  "; 

    }
    while (try_again());
    
    return 0;
};


