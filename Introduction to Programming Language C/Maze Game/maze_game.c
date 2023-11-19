//I used a GNU GCC based compiler called MingGW for compiling this code via Visual Studio Code


//including of necessary libraries
#include<time.h>//for using time() function
#include<stdio.h>
#include<conio.h>//for using getch() function
#include<stdlib.h>
#include<math.h> //for using functions like fabs
#include<string.h> //for using str functions like strcmp()
//declaring of macro ints for maze
int WALL=0;
int EXIT=1;
int MOVEABLE_PLACE=2;


//Function for saving monster's location
void savelocation(int *evenxaxis, int *evenyaxis, int *oddxaxis, int *oddyaxis, int movecount, int *monsterxaxis, int *monsteryaxis){
    if (movecount % 2 == 0) //will save the moves with even movecount
    {
        *evenxaxis = *monsterxaxis;
        *evenyaxis = *monsteryaxis;
    }
    else if (movecount % 2 == 1) //will save the moves with odd movecount
    {
        *oddxaxis = *monsterxaxis;
        *oddyaxis = *monsteryaxis;
    }
}


//Function for checking an integer is the smallest value of the array or not
int arraychecker(int i, int unsortingdistance[4]){
    int control = 0;
    for ( int j = 0; j < 4; j++)
    {
        if (unsortingdistance[i] > unsortingdistance[j])
        {
            control ++; 
        }
        
    }
    if (control != 0)
    {
        //returns 0 if the chosen intege is not the smallest one
        return 0;
    }
    else
    {
        //returns 1 if the chosen integer is the smallest one
        return 1;
    }
}


// Distance Calculator
int calculateDistance(int monsterxaxis, int monsteryaxis, int playerxaxis, int playeryaxis)
{
    return (fabs(playerxaxis - monsterxaxis) + fabs(playeryaxis - monsteryaxis )); //calculates the distance between the monster and the player
}


//Monster Movement Function for Hard Mode
void hardmonster(int *monsterxaxis, int *monsteryaxis, int *playerxaxis, int *playeryaxis, int MAZE[16][16])
{
    int evenxaxis = *monsterxaxis; //will take on the monster's x axis if movecount is even
    int evenyaxis = *monsteryaxis; //will take on the monster's y axis if movecount is even
    int oddxaxis,oddyaxis;  //these will take on the monster's x and y axis if movecount is odd
    int movecount = 0; //it will count the moves that were made by monster
    int checker = 0; //it is used for seperating the calculations when there is an equality between distances and there isn't one. 
    int temp = 1;  //it will be used for storing temporary values when sorting distances
    int random;     //it will be used for randomizing the movement of the monster when there is an equality among distances
    int equality1 = 5; //it will keep the index of one of the equal distances
    int equality2 = 5;  //it will keep the index of the other one of the equal distances 
    int control [4]; // will be used for checking if there is a wall in the place which monster wants to move
    int sortedDistance [4] ; //sorted version of distances
    int unsortedDistance [4];  // Up->0 / Right ->1 / Down -> 2 / Left -> 3 /

    if (*monsteryaxis - 1 >= 0)
    {
        //checks if the upper side of the monster is suitable for moving or not and calculates the distance if it is suitable
        control[0] = *monsteryaxis - 1;
        if (MAZE[control[0]][*monsterxaxis] == 0)
        {
            //will set the distance to max if there is a wall in that way
            sortedDistance[0] = 1000;
            unsortedDistance[0] = 1000;
        }
        else if (movecount %2 == 0 && evenxaxis == *monsterxaxis && evenyaxis == control[0])
        {
            //will set the distance to max if the monster has been there before
            sortedDistance[0] = 1000;
            unsortedDistance[0] = 1000;
        }
        else if (movecount %2 == 1 && oddxaxis == *monsterxaxis && oddyaxis == control[0])
        {
            //will set the distance to max if the monster has been there before
            sortedDistance[0] = 1000;
            unsortedDistance[0] = 1000;
        }
        else
        {
            //calculates the real distance if moving that way is suitable for the monster
            sortedDistance[0] = calculateDistance(*monsterxaxis,control[0],*playerxaxis,*playeryaxis);
            unsortedDistance[0] = calculateDistance(*monsterxaxis,control[0],*playerxaxis,*playeryaxis);
        }
        
    }

    else
    {
        //will set the distance to max if the monster is near an edge of the maze and can't go that way
        sortedDistance[0] = 1000;
        unsortedDistance[0] = 1000;
    }

    if (*monsterxaxis + 1 <= 15)
    {
        //checks if the right side of the monster is suitable for moving or not and calculates the distance if it is suitable
        control[1] = *monsterxaxis + 1;
        if (MAZE[*monsteryaxis][control[1]] == 0)
        {
            //will set the distance to max if there is a wall in that way
            sortedDistance[1] = 1000;
            unsortedDistance[1] = 1000;
        }
        else if (movecount % 2 == 0 && evenxaxis == control[1] && evenyaxis == *monsteryaxis)
        {
             //will set the distance to max if the monster has been there before
            sortedDistance[1] = 1000;
            unsortedDistance[1] = 1000;
        }
        else if (movecount % 2 == 1 && oddxaxis == control[1] && oddyaxis == *monsteryaxis)
        {
             //will set the distance to max if the monster has been there before
            sortedDistance[1] = 1000;
            unsortedDistance[1] = 1000;
        }
        else
        {
            //calculates the real distance if moving that way is suitable for the monster
            sortedDistance[1] = calculateDistance(control[1],*monsteryaxis,*playerxaxis,*playeryaxis);
            unsortedDistance[1] =calculateDistance(control[1],*monsteryaxis,*playerxaxis,*playeryaxis);
        }
        
    }

    else
    {
        //will set the distance to max if the monster is near an edge of the maze and can't go that way
        sortedDistance[1] = 1000;
        unsortedDistance[1] = 1000;
    }

    if (*monsteryaxis + 1 <= 15)
    {
        //checks if the down side of the monster is suitable for moving or not and calculates the distance if it is suitable
        control[2] = *monsteryaxis + 1;
        if (MAZE[control[2]][*monsterxaxis] == 0)
        {
            //will set the distance to max if there is a wall in that way
            sortedDistance[2] = 1000;
            unsortedDistance[2] = 1000;
        }
        else if (movecount %2 == 0 && evenxaxis == *monsterxaxis && evenyaxis == control[2])
        {
            //will set the distance to max if the monster has been there before
            sortedDistance[2] = 1000;
            unsortedDistance[2] = 1000;
        }
        else if (movecount %2 == 1 && oddxaxis == *monsterxaxis && oddyaxis == control[2])
        {
            //will set the distance to max if the monster has been there before
            sortedDistance[2] = 1000;
            unsortedDistance[2] = 1000;
        }
        else
        {
            //calculates the real distance if moving that way is suitable for the monster
            sortedDistance[2] = calculateDistance(*monsterxaxis,control[2],*playerxaxis,*playeryaxis);
            unsortedDistance[2] = calculateDistance(*monsterxaxis,control[2],*playerxaxis,*playeryaxis);
        }
        
    }

    else
    {
        //will set the distance to max if the monster is near an edge of the maze and can't go that way
        sortedDistance[2] = 1000;
        unsortedDistance[2] = 1000;
    }

    if (*monsterxaxis - 1 >= 0)
    {
        //checks if the left side of the monster is suitable for moving or not and calculates the distance if it is suitable
        control[3] = *monsterxaxis - 1;
        if (MAZE[*monsteryaxis][control[3]] == 0)
        {
            //will set the distance to max if there is a wall in that way
            sortedDistance[3] = 1000;
            unsortedDistance[3] = 1000;
        }
        else if (movecount % 2 == 0 && evenxaxis == control[3] && evenyaxis == *monsteryaxis)
        {
             //will set the distance to max if the monster has been there before
            sortedDistance[3] = 1000;
            unsortedDistance[3] = 1000;
        }
        else if (movecount % 2 == 1 && oddxaxis == control[3] && oddyaxis == *monsteryaxis)
        {
             //will set the distance to max if the monster has been there before
            sortedDistance[3] = 1000;
            unsortedDistance[3] = 1000;
        }
        else
        {
            //calculates the real distance if moving that way is suitable for the monster
            sortedDistance[3] = calculateDistance(control[3],*monsteryaxis,*playerxaxis,*playeryaxis);
            unsortedDistance[3] = calculateDistance(control[3],*monsteryaxis,*playerxaxis,*playeryaxis);
        }
        
    }

    else
    {
         //will set the distance to max if the monster is near an edge of the maze and can't go that way
        sortedDistance[3] = 1000;
        unsortedDistance[3] = 1000;
    }

    for (int i = 0; i < 4; i++)
    {
        //sorts the distances from smallest to highest
        for (int j = 0; j < 4; j++)
        {
            if (sortedDistance[i] < sortedDistance[j])
            {
                temp = sortedDistance[i];
                sortedDistance[i] = sortedDistance[j];
                sortedDistance[j] = temp;
            }
            if (sortedDistance[i] == sortedDistance[j] && i != j)
            {
                checker = 1;
            }  
        }
    }
    
    if (checker == 0)
    {
        //finds out the best way for monster to move if there isn't any equality among the distances and executes it
        if (sortedDistance[0] == unsortedDistance[0])
        {
            //will move up if it is the shorters and suitable
            *monsteryaxis -= 1;
            movecount++;
            savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
        }
        else if (sortedDistance[0] == unsortedDistance[1])
        {
            //will move right if it is the shorters and suitable
            *monsterxaxis += 1;
            movecount++;
            savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
        }
        else if (sortedDistance[0] == unsortedDistance[2])
        {
            //will move down if it is the shorters and suitable
            *monsteryaxis += 1;
            movecount++;
            savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
        }
        else if (sortedDistance[0] == unsortedDistance[3])
        {
            //will move left if it is the shorters and suitable
            *monsterxaxis -= 1;
            movecount++;
            savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
        }   
    }

    else if (checker == 1)
    {
        //finds out the best way for monster to move if there are equalities among distances and executes it
         for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (unsortedDistance[i] == unsortedDistance[j] && i != j)
                {
                    if (arraychecker(i,unsortedDistance))
                    {
                        equality1 = i;
                        equality2 = j;
                    }
                } 
            }    
        }
        
        if (sortedDistance[0] != sortedDistance[1])
        {
            //will work if there isn't any equality between any of the distances and the smallest one
            if (sortedDistance[0] == unsortedDistance[0])
            {
                //will move up if it is the shorters and suitable
                *monsteryaxis -= 1;
                movecount++;
                savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
            }
            else if (sortedDistance[0] == unsortedDistance[1])
            {
                //will move right if it is the shorters and suitable
                *monsterxaxis += 1;
                movecount++;
                savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
            }
            else if (sortedDistance[0] == unsortedDistance[2])
            {
                //will move down if it is the shorters and suitable
                *monsteryaxis += 1;
                movecount++;
                savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
            }
            else if (sortedDistance[0] == unsortedDistance[3])
            {
                //will move left if it is the shorters and suitable
                *monsterxaxis -= 1;
                movecount++;
                savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
            }          
        }
        else if (sortedDistance[0] == sortedDistance[1])
        {
           random = rand()%2;
            if (random == 1) //finds out which move is the shortest one in equality1 and executes it
            {
                if ( equality1 == 0)
                {
                    //will move up if it is the shorters and suitable
                    *monsteryaxis -= 1;
                    movecount++;
                    savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
                }
                else  if ( equality1 == 1)
                {
                    //will move right if it is the shorters and suitable
                    *monsterxaxis += 1;
                    movecount++;
                    savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
                }
                else if ( equality1 == 2)
                {
                    //will move down if it is the shorters and suitable
                    *monsteryaxis += 1;
                    movecount++;
                    savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
                }
                else if ( equality1 == 3)
                {
                    //will move left if it is the shorters and suitable
                    *monsterxaxis -= 1;
                    movecount++;
                    savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
                }
                    
            }
            else if (random == 0) //finds out which move is the shortest one in equality2 and executes it
            {
                if ( equality2 == 0)
                {
                    //will move up if it is the shorters and suitable
                    *monsteryaxis -= 1;
                    movecount++;
                    savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
                }
                else  if ( equality2 == 1)
                {
                    //will move right if it is the shorters and suitable
                    *monsterxaxis += 1;
                    movecount++;
                    savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
                }
                else if ( equality2 == 2)
                {
                    //will move down if it is the shorters and suitable
                    *monsteryaxis += 1;
                    movecount++;
                    savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
                }
                else if ( equality2 == 3)
                {
                    //will move left if it is the shorters and suitable
                    *monsterxaxis -= 1;
                    movecount++;
                    savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
                }                 
            }  
        }      
    }   
}


//Function for controlling if the game ended or not
int endgame(int monsterxaxis, int monsteryaxis, int playerxaxis, int playeryaxis)
{
    if (monsterxaxis == playerxaxis && monsteryaxis == playeryaxis)
    {
        //returns 0 if monster has caught the player
        return 0;
    }
    else if (playerxaxis == 0 && playeryaxis == 7)
    {
        //returns 1 if player has reached to the exit
        return 1;
    }
    else
    {
        //returns 2 if the game is still going on
        return 2;
    }
}


//Function for printing the playground to screen
void printPlayGround(int MAZE[16][16],int *monsterxaxis, int *monsteryaxis, int *playerxaxis, int *playeryaxis)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (i == *monsteryaxis && j == *monsterxaxis)
            {
                printf("|M|"); //prints M for monster
            }
            else if (i == *playeryaxis && j == *playerxaxis)
            {
                printf("|P|"); // prints P for player
            }
            else if (MAZE[i][j]==0)
            {
                printf("|O|"); //prints 0 for walls
            }
            else if (MAZE[i][j]==1)
            {
                printf("|E|"); //prints E for exit
            }
            else{
                printf("|_|"); //prints _ for moveable places
            }
        }
        printf("\n");
    }  
}


//Distance checker function
void generalChecker(int *monsterxaxis, int *monsteryaxis, int *playerxaxis, int *playeryaxis,int MAZE[16][16])
{
    //randomizes locations until they all obey the manhattan distance rule
    while (fabs(*playerxaxis - *monsterxaxis) + fabs(*playeryaxis - *monsteryaxis) < 16 || fabs(*playeryaxis - 7) + fabs(*playerxaxis - 0) < 16 || MAZE[*monsteryaxis][*monsterxaxis] == 0 || MAZE[*playeryaxis][*playerxaxis] == 0 )
    {
        *monsterxaxis = rand()%16;
        *monsteryaxis = rand()%16;
        *playerxaxis = rand()%16;
        *playeryaxis = rand()%16;
    }   
}


//Easy Mode Monster Movement Function
void easymonster(int *monsterxaxis, int *monsteryaxis,int MAZE[16][16])
{
    int evenxaxis = *monsterxaxis; //will take on the monster's x axis if movecount is even
    int evenyaxis = *monsteryaxis; //will take on the monster's y axis if movecount is even
    int oddxaxis,oddyaxis; //these will take on the monster's x and y axis if movecount is odd
    int movecount = 0; //it will count the moves that were made by monster
    int control=0; // will be used for checking if there is a wall in the place which monster wants to move
    int movement = rand()%4; //will be used for randomizing the movement of the monster
    if (movement == 0)
    {
        //monster goes left if suitable
        if (*monsterxaxis - 1 >= 0)
        {
            control = *monsterxaxis - 1;
            if (MAZE[*monsteryaxis][control] == 0)
            {
                //calls the function again if there is a wall in that way
                easymonster(monsterxaxis,monsteryaxis,MAZE);
            }
            else if (movecount % 2 == 0 && control == evenxaxis && *monsteryaxis == evenyaxis )
            {
                //calls the function again if monster has been there before
                easymonster(monsterxaxis,monsteryaxis,MAZE);
            }
            else if (movecount % 2 == 1 && control == oddxaxis && *monsteryaxis == oddyaxis)
            {
                //calls the function again if monster has been there before
                easymonster(monsterxaxis,monsteryaxis,MAZE);
            }
            else
            {
                //monster moves left
                *monsterxaxis -= 1;
                movecount++;
                savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
            }
        }
        else
        {
            //calls the function again if the monster is near an edge of the maze and can't go that way
            easymonster(monsterxaxis,monsteryaxis,MAZE);
        }
    }
    else if (movement == 1)
    {
        //monster goes right if suitable
        if (*monsterxaxis + 1 <= 15)
        {
            control = *monsterxaxis + 1;
            if (MAZE[*monsteryaxis][control]==0)
            {
                //calls the function again if there is a wall in that way
                easymonster(monsterxaxis,monsteryaxis,MAZE);
            }
            else if (movecount % 2 == 0 && control == evenxaxis && *monsteryaxis == evenyaxis )
            {
                //calls the function again if monster has been there before
                easymonster(monsterxaxis,monsteryaxis,MAZE);
            }
            else if (movecount % 2 == 1 && control == oddxaxis && *monsteryaxis == oddyaxis)
            {
                //calls the function again if monster has been there before
                easymonster(monsterxaxis,monsteryaxis,MAZE);
            }
            else
            {
                //monster moves right
                *monsterxaxis += 1;
                movecount++;
                savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
            }
        
        }
        else
        {
            //calls the function again if the monster is near an edge of the maze and can't go that way
            easymonster(monsterxaxis,monsteryaxis,MAZE);
        }
    }
    else if (movement == 2)
    {
        // monster goes up if suitable
        if (*monsteryaxis - 1 >= 0)
        {
            control = *monsteryaxis - 1;
            if (MAZE[control][*monsterxaxis]==0)
            {
                //calls the function again if there is a wall in that way
                easymonster(monsterxaxis,monsteryaxis,MAZE);
            }
            else if (movecount % 2 == 0 && control == evenyaxis && *monsterxaxis == evenxaxis)
            {
                //calls the function again if monster has been there before
                easymonster(monsterxaxis,monsteryaxis,MAZE);
            }
            else if (movecount % 2 == 1 && control == oddyaxis && *monsterxaxis == oddxaxis)
            {
                //calls the function again if monster has been there before
                easymonster(monsterxaxis,monsteryaxis,MAZE);
            }
            else
            {
                //monster moves up
                *monsteryaxis -= 1;
                movecount++;
                savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
            }
        
        }
        else
        {
            //calls the function again if the monster is near an edge of the maze and can't go that way
            easymonster(monsterxaxis,monsteryaxis,MAZE);
        }
    }
    else if (movement == 3)
    {
        //monster goes down if suitable
        if (*monsteryaxis + 1 <= 15)
        {
            control = *monsteryaxis + 1;
            if (MAZE[control][*monsterxaxis]==0)
            {
                //calls the function again if there is a wall in that way
                easymonster(monsterxaxis,monsteryaxis,MAZE);
            }
            else if (movecount % 2 == 0 && control == evenyaxis && *monsterxaxis == evenxaxis)
            {
                //calls the function again if monster has been there before
                easymonster(monsterxaxis,monsteryaxis,MAZE);
            }
            else if (movecount % 2 == 1 && control == oddyaxis && *monsterxaxis == oddxaxis)
            {
                //calls the function again if monster has been there before
                easymonster(monsterxaxis,monsteryaxis,MAZE);
            }
            else
            {
                //monster moves down
                *monsteryaxis += 1;
                movecount++;
                savelocation(&evenxaxis,&evenyaxis,&oddxaxis,&oddyaxis,movecount,monsterxaxis,monsteryaxis);
            }
        }
        else
        {
            //calls the function again if the monster is near an edge of the maze and can't go that way
            easymonster(monsterxaxis,monsteryaxis,MAZE);
        }
    }
}


//Player Movement Function
void playermovement(int *playerxaxis, int *playeryaxis, int MAZE[16][16])
{
    int playercontrol =0; // will be used for checking if there is a wall in the place which player wants to move
    char movement [2] ; //will take the way that player wants to move
    printf("W->Up\nD->Right\nS->Down\nA->Left\n");
    scanf("%s",&movement);
    strcpy(movement,strlwr(movement));
    if (strcmp(movement,"w")==0)
    {
        //checkes the move that is chosen by player; executes if it is suitable and says player to choose again if not.
        if (*playeryaxis - 1 >= 0)
        {
            playercontrol= *playeryaxis - 1;
            if (MAZE[playercontrol][*playerxaxis]==0)
            {
                //calls the function again if there is a wall in the direction in the way that player wants to go and says it to player
                printf("You can't go through that direction because there is a wall over there.");
                playermovement(playerxaxis, playeryaxis, MAZE);
            }
            else
            {
                //player moves up
                *playeryaxis -= 1;
            }
            
        }
        else
        {
            //calls the function again if there is a cliff in the direction in the way that player wants to go and says it to player
            printf("You can't go through that direction because there is a cliff over there.");
            playermovement(playerxaxis,playeryaxis,MAZE);
        }
          
    }
    else if (strcmp(movement,"d")==0)
    {
        //checkes the move that is chosen by player; executes if it is suitable and says player to choose again if not.
        if (*playerxaxis + 1 <=15)
        {
            playercontrol = *playerxaxis + 1;
            if (MAZE[*playeryaxis][playercontrol]==0)
            {
                //calls the function again if there is a wall in te direction in the way that player wants to go and says it to player
                printf("You can't go through that direction because there is a wall over there.");
                playermovement(playerxaxis,playeryaxis,MAZE);
            }
            else
            {
                //player moves right
                *playerxaxis += 1;
            }
            
        }
        else
        {
            //calls the function again if there is a cliff in the direction in the way that player wants to go and says it to player
            printf("You can't go through that direction because there is a cliff over there.");
            playermovement(playerxaxis,playeryaxis,MAZE);
        }
        
    }
    else if (strcmp(movement,"s")==0)
    {
        //checkes the move that is chosen by player; executes if it is suitable and says player to choose again if not.
        if (*playeryaxis + 1 <=15)
        {
             playercontrol = *playeryaxis + 1;
            if (MAZE[playercontrol][*playerxaxis]==0)
            {
                //calls the function again if there is a wall in the direction in the way that player wants to go and says it to player
                printf("You can't go through that direction because there is a wall over there.");
                playermovement(playerxaxis,playeryaxis,MAZE);
            }
            else
            {
                //player moves down
                *playeryaxis += 1;
            }
        }
        else
        {
            //calls the function again if there is a cliff in the direction in the way that player wants to go and says it to player
            printf("You can't go through that direction because there is a cliff over there.");
            playermovement(playerxaxis,playeryaxis,MAZE);
        }
    }
    else if (strcmp(movement,"a")==0)
    {
        //checkes the move that is chosen by player; executes if it is suitable and says player to choose again if not.
        if ( *playerxaxis - 1 >= 0)
        {
             playercontrol = *playerxaxis - 1;
            if (MAZE[*playeryaxis][playercontrol]==0)
            {
                //calls the function again if there is a wall in the direction in the way that player wants to go and says it to player
                printf("You can't go through that direction because there is a wall over there.");
                playermovement(playerxaxis,playeryaxis,MAZE);
            }
            else
            {
                //player moves left
                *playerxaxis -= 1;
            }
        }
        else
        {
            //calls the function again if there is a cliff in the direction in the way that player wants to go and says it to player
            printf("You can't go through that direction because there is a cliff over there.");
            playermovement(playerxaxis,playeryaxis,MAZE);
        }
        
    }
    else
    {
        //calls the function again and says to player that he/she has entered a wrong type of input if the input is wrong
        printf("Please select an appropriate way of moving.");
        playermovement(playerxaxis,playeryaxis,MAZE);
    }

}

//game executing function
int main()
{
    int game = 1;
    srand(time(NULL));
    int monsterxaxis,monsteryaxis,playerxaxis,playeryaxis; //integers for keeping the monster's and the player's location
    int MAZE [16][16]; //array for maze
    int difficulty;//chosen difficulty 
    
    //Declaration of moveable places
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                    MAZE[i][j]=2;
            }
            
        }
    //Declaration of walls and exit
       {MAZE[0][8] = 0;
        MAZE[1][8] = 0;
        MAZE[2][8] = 0;
        MAZE[2][7] = 0;
        MAZE[2][9] = 0;
        MAZE[2][2] = 0;
        MAZE[3][2] = 0;
        MAZE[2][13] = 0;
        MAZE[3][13] = 0;
        MAZE[5][6] = 0;
        MAZE[5][7] = 0;
        MAZE[5][8] = 0;
        MAZE[6][6] = 0;
        MAZE[9][3] = 0;
        MAZE[9][4] = 0;
        MAZE[9][5] = 0;
        MAZE[10][5] = 0;
        MAZE[8][10] = 0;
        MAZE[9][10] = 0;
        MAZE[10][10] = 0;
        MAZE[11][10] = 0;
        MAZE[11][11] = 0;
        MAZE[12][2] = 0;
        MAZE[13][2] = 0;
        MAZE[14][2] = 0;
        MAZE[14][3] = 0;
        MAZE[14][4] = 0;
        MAZE[7][0] = 1;}         
        while (game == 1)
        {
                printf("Welcome to the playground!\n");
                printf("Walls->0\nYou->P\nMonster->M\nExit->E\n");
                printf("You have to get to the exit before the monster gets to you!\n");
                printf("You can move up, down, left or right but no diagnotial moves are allowed. You must move around them.");
                printf("Please choose the difficulty level of the game!\n1->Easy\n2->Hard\n");
                scanf("%d",&difficulty);
            if (difficulty == 1)
            {
                //starts the game in easy mode
                monsterxaxis = rand()%16;//row of monster
                monsteryaxis = rand()%16;//column of monster 
                playerxaxis = rand()%16;//row of player
                playeryaxis = rand()%16;//column of player
                generalChecker(&monsterxaxis,&monsteryaxis,&playerxaxis,&playeryaxis,MAZE); //checkes the distances and corrects them
           
                while (endgame(monsterxaxis,monsteryaxis,playerxaxis,playeryaxis) == 2)
                {
                    printPlayGround(MAZE,&monsterxaxis,&monsteryaxis,&playerxaxis,&playeryaxis);
                    playermovement(&playerxaxis,&playeryaxis,MAZE);
                    easymonster(&monsterxaxis,&monsteryaxis,MAZE);
                    system("cls");
                }
            
                if (endgame(monsterxaxis,monsteryaxis,playerxaxis,playeryaxis) == 1)
                {
                    //if player has won the game
                    printf("Congratulations! You won!\n");
                    endgamequestion1:
                    printf("Would you like to play again?\n1->Yes\n2->No\n");
                    scanf("%d",&game);
                        if (game == 1)
                        {
                            system("cls");
                        }
                       
                        else if (game == 2)
                        {
                            system("PAUSE");
                        }
                        
                        else
                        {
                            printf("Please enter a valid value.\n");
                            goto endgamequestion1;
                        }
                }

                else if (endgame(monsterxaxis,monsteryaxis,playerxaxis,playeryaxis) == 0)
                {
                    //if player has lost the game
                    printf("The monster has caught you! You lost!");
                    endgamequestion2:
                    printf("Would you like to play again?\n1->Yes\n2->No\n");
                    scanf("%d",&game);
                        if (game == 1)
                        {
                            system("cls");
                        }
                        else if (game == 2)
                        {
                            system("PAUSE");
                        }
                        else
                        {
                            printf("Please enter a valid value.\n");
                            goto endgamequestion2;
                        }
                
                }
            }
            if (difficulty == 2)
            {
                //starts the game in hard mode
                monsterxaxis = rand()%16;//row of monster
                monsteryaxis = rand()%16;//column of monster 
                playerxaxis = rand()%16;//row of player
                playeryaxis = rand()%16;//column of player
                generalChecker(&monsterxaxis,&monsteryaxis,&playerxaxis,&playeryaxis,MAZE);
           
                while (endgame(monsterxaxis,monsteryaxis,playerxaxis,playeryaxis) == 2)
                {
                    printPlayGround(MAZE,&monsterxaxis,&monsteryaxis,&playerxaxis,&playeryaxis);
                    playermovement(&playerxaxis,&playeryaxis,MAZE);
                    hardmonster(&monsterxaxis,&monsteryaxis,&playerxaxis,&playeryaxis,MAZE);
                    system("cls");
                }
            
                if (endgame(monsterxaxis,monsteryaxis,playerxaxis,playeryaxis) == 1)
                {
                    //if player has won the game
                    printf("Congratulations! You won!\n");
                    endgamequestion3:
                    printf("Would you like to play again?\n1->Yes\n2->No\n");
                    scanf("%d",&game);
                        if (game == 1)
                        {
                            //game continues
                            system("cls");
                        }
                       
                        else if (game == 2)
                        {
                            //exits from game
                            system("PAUSE");
                        }
                        
                        else
                        {
                            //if taken value is invalid
                            printf("Please enter a valid value.\n");
                            goto endgamequestion3;
                        }
                    }

                else if (endgame(monsterxaxis,monsteryaxis,playerxaxis,playeryaxis) == 0)
                {
                    //if player has lost the game
                    printf("The monster has caught you! You lost!");
                    endgamequestion4:
                    printf("Would you like to play again?\n1->Yes\n2->No\n");
                    scanf("%d",&game);
                        if (game == 1)
                        {
                            //game continues
                            system("cls");
                        }
                        else if (game == 2)
                        {
                            //exits from game
                            system("PAUSE");
                        }
                        else
                        {
                            //if taken value is invalid
                            printf("Please enter a valid value.\n");
                            goto endgamequestion4;
                        } 
                }
            }   
        }   
    getch();
    return 0;
}