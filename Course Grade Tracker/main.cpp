/*
  Course-Grade.cpp
  Created by Austin Flores on 2/21/14.
  Copyright (c) 2014 dracospitfire. All rights reserved.
*/

#include <iostream>        //required for display output
#include <string>          //required for string class
#include <cmath>           //required for pow and sqrt
#include <iomanip>         //required for setw or setprecision


using namespace std;       //requred to access entities with namespace std

struct ClassRoom
{
    int id;
    string name;           //student names
    float *test;           //dynamically allocated array
    float aveScore;        //test average
    char grade;            //course grade
};

//function prototypes
void GenerateData(int, int);
void CalulateAverageScore(ClassRoom[], int, int);

int main()
{
    cout << "\t\tClass Room Course Grades\n\n";
    cout << "This program will help you keep track of individual students's scores."
    << "\n\tEnter to get started:\n";
    cin.ignore(100,'\n');

    int size;
    int amount;
    int k;
    do{
        k = 0;
        cout << "How many students are there?\n> ";
        cin >> size;
        //verifying input no negative values
        if(size <= 0)
        {
            cout << "\tNumber of students should be greater than ZERO.\n";
            k = 1;
        }
        else
        {
            k = 0;
        }
    } while (k);
    
    do{
        k = 0;
        cout << "\nHow many test scores will each student take?\n> ";
        cin >> amount;
        //verifying input no negative values
        if(amount <= 0)
        {
            cout << "\tNumber of exams should be greater than ZERO.\n";
            k = 1;
        }
        else
        {
            k = 0;
        }
    } while (k);
    
    GenerateData(size, amount);
    
    cout << "\n\n\t";
    return 0;
}

void GenerateData(int size, int amount)
{
    int k;
    cout << "\nNow, you will provide each Student's ID number and all their test scores.\n\n";
    
    //dynamically allocate structure large enough to hold the number of students
    ClassRoom *freshman = new ClassRoom[size];
    int student;
    //dynamically allocate array large enough to hold the number of test scores
    for (student = 0; student < size; student++)
        freshman[student].test = new float[amount];

    //collect data
    for (student = 0; student < size; student++)
    {
        cout << (student + 1);
        cin.ignore(100,'\n');
        do{
            k = 0;
            cout << " Student's\n\t\t\tName: ";
            getline(cin, freshman[student].name);
            //verifying input only letters and spaces for name
            if (freshman[student].name.length() == 0)
            {
                cout << "Please Enter,";
                k = 1;
            }
            for (long n = 0; n < freshman[student].name.length(); n++)
            {
                if (!isalpha(freshman[student].name.c_str()[n]))
                {
                    if (isspace(freshman[student].name.c_str()[n]))
                        k = 0;
                    else
                    {
                        k = 1;
                        n = freshman[student].name.length();
                    }
                }
                else
                    k = 0;
            }
        } while (k);
        do{
            k = 0;
            cout << " Student's\n\t\t\tID: ";
            cin >> freshman[student].id;
            //verifying jersey number is not negative.
            if(freshman[student].id > 0)
            {
                //verifying jersey number is not repeated
                for (int pastStudent = 0; pastStudent < student; pastStudent++)
                    if(freshman[student].id == freshman[pastStudent].id)
                    {
                        cout << "\tStudent ID number already used.\n\tPlease verify that it is correct.\n";
                        k = 1;
                    }
            }
            else
            {
                cout << "\tID number can not be negative.\n";
                k = 1;
            }
        } while (k);
        for (int score = 0; score < amount; score++ )
        {
            cout << (score + 1);
            k = 0;
            do{
                cout << " Test Score:\n\t\t\t> ";
                cin >> freshman[student].test[score];
                //verifying input no negative values
                if(freshman[student].test[score] < 0)
                {
                    cout << "\tScore can not be negative.\n";
                    k = 1;
                }
                else
                {
                    k = 0;
                }
            } while (k);
        }
        cout << "\n";
    }
    
    CalulateAverageScore(freshman, size, amount);
    
    //generate table
    for (student = 0; student < size; student++)
    {
        cout << left;
        cout << "\n ";
        cout << (student + 1);
        cout << " Student's\n"     << setw(20);
        cout << "Name:"            << setw(8)
             << "ID:"              << setw(11)
             << "Score:"           << setw(11)
             << "Grade:";
        cout << "\n";
        cout << "------------------------------------------------------";
        cout << "\n";
        cout << left                       << setw(23);
        cout << freshman[student].name     << setw(11);
        cout << freshman[student].id       << setw(11);
        cout << freshman[student].aveScore;
        cout << freshman[student].grade;
        cout << "\n";
        cout << "------------------------------------------------------";
    }
    //free the dynamically allocated memory
    for (student = 0; student < size; student++)
        delete [] freshman[student].test;
    for (student = 0; student < size; student++)
        freshman[student].test = 0;
    delete [] freshman;
    freshman = 0;
}

void CalulateAverageScore(ClassRoom freshman[], int size, int amount)
{
    for (int student = 0; student < size; student++)
    {
        int sum = 0;
        for (int score = 0; score < amount; score++ )
        {
            sum += freshman[student].test[score];
        }
        
        freshman[student].aveScore = sum * pow(amount,-1);
        if (freshman[student].aveScore >= 91)
            freshman[student].grade = 'A';
        if (freshman[student].aveScore >= 81 && freshman[student].aveScore <= 90)
            freshman[student].grade = 'B';
        if (freshman[student].aveScore >= 71 && freshman[student].aveScore <= 80)
            freshman[student].grade = 'C';
        if (freshman[student].aveScore >= 61 && freshman[student].aveScore <= 70)
            freshman[student].grade = 'D';
        if (freshman[student].aveScore <= 60)
            freshman[student].grade = 'F';
        
    }

}
