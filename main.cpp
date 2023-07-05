#include<iostream>
#include<fstream>

#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

#include<time.h>
using namespace std;

int generateRandom()
{
    // generating random number between 10 and 99
    srand(time(NULL));

    int randomNumber = rand() % 100;

    while(randomNumber < 10) // number should be between 10 and 99
    {
        randomNumber = rand() % 100;

        if(randomNumber >= 10)
        {
            break;
        }
    }

    // Roll No: 0531, therefore multiplication not needed

    int division = (531 / randomNumber) % 25;

    if(division < 10)
    {
        division += 15;
    }

    return division;
}

int** createAndPopulateMatrix(int n)
{
    // creating 

    int** matrix = new int* [n];

    for(int i = 0; i < n ; i++)
    {
        matrix[i] = new int[n];
    }

    srand(time(0));

    // populating

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[i][j] = rand() % 100;
        }
    }

    return matrix;
}

void displayMatrix(int**& matrix, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int n = generateRandom();
    int** matrix = createAndPopulateMatrix(n); // create n x n matrix and populate it

    int** matrix1 = createAndPopulateMatrix(3);
    int matrix2[n][n];

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            matrix2[i][j] = 0;
        }
    }

    displayMatrix(matrix, n);

    ofstream fout("matrix.txt");

    cout << endl << endl;

    for(int i = 0; i < n; i++)
    {
        if(fork() == 0)
        {
            for(int j = 0; j < n; j++)
            {
                for(int k = 0; k < n; k++)
                {
                    matrix2[i][j] += matrix[i][k] * matrix[k][j];
                }                
                fout << matrix2[i][j] << " ";
            }
            fout << endl;
            exit(0);
        }
        else
        {
            cout << "";
        }
    }

    for(int i = 0; i < n; i++)
    {
        wait(NULL);
    }

    // read the file and display the multiplication result

    cout << "---- Result of multiplication ----" << endl << endl;

    ifstream fin("matrix.txt");
    char temp;

    fin.get(temp);

    if(fin)
    {
        while(fin.eof() == false)
        {
            cout << temp;
            fin.get(temp);
        }
    }
    else
    {
        cout << "Error opening file" << endl;
    }
    
}