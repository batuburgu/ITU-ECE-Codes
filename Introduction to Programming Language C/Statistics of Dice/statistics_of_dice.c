#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

// function for printing the results to screen
void showResults (int howManyTimesIn6[6], int sumsOfNumbers[11]){

    int starCount; // will be used for keeping the number of starts in a single column
    int firstThrow[6][20]; // array for printing first roll
    int secondThrow[11][20]; // array for printing second roll
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            firstThrow[i][j] = 0; // setting all points in array like there will be no stars
            if (j == 19)
            {
                firstThrow[i][j] = i+1; // setting the numbers of the face of the dice
            }
        } 
    }
    
    for (int i = 0; i < 6; i++)
    {
        starCount = howManyTimesIn6[i] / 100; // keeps the star count in i'st column
        
        for (int j = 18; j > 18-starCount; j--)
        {
            firstThrow[i][j] = 100; //setting the points which will have starts
        }
    }
    
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 6; i++)
        {
            //print stars
            if (firstThrow[i][j] == 100)
            {
                printf("*\t");
            }
            //print empty spaces
            else if (firstThrow[i][j] == 0)
            {
                printf(" \t");
            }
            //print numbers of the faces
            else if (j == 19)
            {
                printf("%d\t",firstThrow[i][j]);
            }
        }
        
        printf("\n");   
    }
    
    printf("\n\n\n"); //adjusting the space between results
    
    //part for two dices
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            secondThrow[i][j] = 0; // setting all points in array like there will be no stars
            if (j == 19)
            {
                secondThrow[i][j] = i+2; // setting the sums of two faces of the dices
            }  
        }
    }
    
    for (int i = 0; i < 11; i++)
    {
        starCount = sumsOfNumbers[i] / 100; // keeps the star count in i'st column
        for (int j = 19; j > 19 - starCount; j--)
        {
            if (j != 19 )
            {
                secondThrow[i][j] = 100; //setting the points which will have starts
            }    
        }
    }

    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 11; i++)
        {
            //print stars
            if (secondThrow[i][j] == 100)
            {
                printf("*\t");
            }
            //prints empty spaces
            else if (secondThrow[i][j] == 0)
            {
                printf(" \t");
            }
            //prints sums of the two faces
            else if (j == 19)
            {
                printf("%d\t",secondThrow[i][j]);
            }   
        }
        printf("\n");
        
    }
}


// function for rolling the dices
void rollTheDice (int howManyTimesIn6[6], int sumsOfNumbers[11]){
    int dice = 0; // the number which came in first dice roll
    int doubleDice1 = 0; // the first number which came in second dice roll
    int doubleDice2 = 0; // the second number which came in second dice roll
    int sumofDoubleDice = 0; //sum of first and second number which came in second dice roll

    for (int i = 0; i < 10000; i++)
    {
        dice = 1 + rand()%6; //rolling the dice
        
        //first dice roll
        switch (dice)
        {
        case 1:
            howManyTimesIn6[0]++; //if it came 1
            break;
        case 2:
            howManyTimesIn6[1]++; //if it came 2
            break;
        case 3:
            howManyTimesIn6[2]++; //if it came 3
            break;
        case 4:
            howManyTimesIn6[3]++; //if it came 4
            break;
        case 5:
            howManyTimesIn6[4]++; //if it came 5
            break;
        case 6:
            howManyTimesIn6[5]++; //if it came 6
            break;
        default:
            break;
        }
    }

    for (int i = 0; i < 10000; i++)
    {
        doubleDice1 = 1 + rand() % 6; //rolling first dice
        doubleDice2 = 1 + rand() % 6; //rolling second dice
        sumofDoubleDice = doubleDice1 + doubleDice2; //sum of the numbers on top of dices
        
        //second dice roll
        switch (sumofDoubleDice)
        {
        case 2:
            sumsOfNumbers[0]++; //if sum is 2
            break;
        case 3:
            sumsOfNumbers[1]++; //if sum is 3
            break;
        case 4:
            sumsOfNumbers[2]++; //if sum is 4
            break;
        case 5:
            sumsOfNumbers[3]++; //if sum is 5
            break;
        case 6:
            sumsOfNumbers[4]++; //if sum is 6
            break;
        case 7:
            sumsOfNumbers[5]++; //if sum is 7
            break;
        case 8:
            sumsOfNumbers[6]++; //if sum is 8
            break;
        case 9:
            sumsOfNumbers[7]++; //if sum is 9
            break;
        case 10:
            sumsOfNumbers[8]++; //if sum is 10
            break;
        case 11:
            sumsOfNumbers[9]++; //if sum is 11
            break;
        case 12:
            sumsOfNumbers[10]++; //if sum is 12
            break;
        default:
            break;
        }
    }
}

//program execution
int main(){

    printf("* -> 100 times\n");
    srand(time(NULL));
    int howManyTimesIn6[6] = {0}; //this array will be used to count frequency of the values
    int sumsOfNumbers[11] = {0}; // this array will be used to count frequency of the sums of the values
    rollTheDice(howManyTimesIn6,sumsOfNumbers); //rolling the dices
    showResults(howManyTimesIn6,sumsOfNumbers); //printing the results
    getch();
    return 0;
}