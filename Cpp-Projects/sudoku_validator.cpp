#include <iostream>
using namespace std;

bool check_row(int a[][9], int which_row)
{
    bool all_found = true;
    bool number_found;
    for (int number = 1; number <= 9; number++)
    {
        number_found = false;
        for (int col = 0; col < 9; col++)
        {
            if (a[which_row][col] == number)
            {
                number_found = true;
            }
        }

        if (false == number_found)
        {
            cout << "The missing number in this row = " << number;
            all_found = false;
        }

    } // do this for all the numbers from 1 to 9

    return all_found;
}

bool check_col(int* a, int which_col)
{
    bool all_found = true;
    bool number_found;
    for (int number = 1; number <= 9; number++)
    {
        number_found = false;
        for (int row = 0; row < 9; row++)
        {
            if (*(a + row * 9 + which_col) == number)
            {
                number_found = true;
            }
        }

        if (false == number_found)
        {
            cout << "The missing number in this col  = " << number;
        }

        // if all the numbers are found in the col
        // all_found will be true, otherwise it will
        // be set to false

        all_found = all_found && number_found;

    }

    return all_found;
}

bool check_region(int a[][9], int which_row, int which_col)
{
    bool all_found = true;
    bool number_found;
    for (int number = 1; number <= 9; number++)
    {
        number_found = false;
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (number == a[row + which_row][col + which_col])
                {
                    number_found = true;
                    break; // we found the number, so stop searching for it
                }
            } // col loop

            if (number_found)
            {
                break; //  stop searching from the row as well
            }
        }   // row loop

     // if all the numbers are found in the region
     // all_found will be true, otherwise it will set to false

        all_found = all_found && number_found;

        if (false == number_found)
        {
            cout << " The missing number in this region  = " << number;
        }

    } // do this for all the numbers from 1 to 9

    return all_found;
}

int main()
{

    int suduko[9][9] = { 2, 7, 1,    9, 5, 4,    6, 8, 3,
                         5, 9, 3,    6, 2, 8,    1, 4, 7,
                         4, 6, 8,    1, 3, 7,    2, 5, 9,

                         7, 3, 6,    4, 1, 5,    8, 9, 2,
                         1, 5, 9,    8, 6, 2,    3, 7, 4,
                         8, 4, 2,    3, 7, 9,    5, 6, 1,

                         9, 8, 5,    2, 4, 1,     7, 3, 6,
                         6, 1, 7,    5, 9, 3,     4, 2, 8,
                         3, 2, 4,    7, 8, 6,     9, 1, 5 };


    cout << "Checking all the rows for Sudukoness:" << endl << endl;

    for (int row = 0; row < 9; row++)
    {
        cout << "Checking row " << row << " of the array : ";
        if (check_row(suduko, row))
        {
            cout << " TRUE " << endl;
        }
        else
        {
            cout << " FALSE " << endl;
        }
    }

    cout << endl;
    cout << "Checking all the columns for Sudukoness:" << endl << endl;

    for (int col = 0; col < 9; col++)
    {
        cout << "Checking col " << col << " of the array : ";
        if (check_col(&suduko[0][0], col))
        {
            cout << " TRUE " << endl;
        }
        else
        {
            cout << " FALSE " << endl;
        }
    }

    cout << endl;
    cout << "Checking all the  regions for Sudukoness:" << endl << endl;

    for (int row = 0; row < 9; row = row + 3)
    {
        for (int col = 0; col < 9; col = col + 3)
        {
            cout << "Checking region defined by row = " << row << " and column = " << col;
            if (check_region(suduko, row, col))
            {
                cout << " TRUE " << endl;
            }
            else
            {
                cout << " FALSE " << endl;
            }
        } // col
    } // row




    return 0;
}
