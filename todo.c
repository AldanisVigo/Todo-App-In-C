/*  
 *  TODO Application in C
 *  C is da best foo...bar
 *  Created on Sun Nov 20 2022
 *  Copyright (c) 2022 Aldanis Vigo
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct todo_t todo;

//Structure to store a todo
struct todo_t {
    char name[100];
    bool done;
    todo* next;
}head;

/*
    Function takes in a char pointer and checks if it points to a white space.
    If it does, it begins to increment the pointer by one and checking again
    until we find a character that is not a whitespace.
*/
char* ltrim(char* s){
    //While the value at s is a space
    while(isspace(*s)){
        s++; //Increment the s pointer to the next character
    }

    //Return s when we stop seeing whitespaces
    return s;
}

/*
    Function takes in a char pointer and moves it to the end of the char array
    by adding the results of strlen on the char array. It then checks if the last
    space on the array is a space, if it is it decrements the pointer by 1 and checks
    again. This process continues until we find a character that is not a space
*/
char* rtrim(char* s){
    //Move the pointer to the end of the string
    char* last = s + strlen(s);

    //Iterate through from right to left until we find a non space character.
    while(isspace(*--last));

    //Add the string terminator character \0 at the space right after the non space character
    *(last + 1) = '\0';

    //Return s back to the caller
    return s;
}

/*
    Method makes use of ltrim and rtrim to trim spaces from both ends of a character array
*/
char* trim(char* s){ 
    return rtrim(ltrim(s));
}

/*
    Method to make a string lowercase and return it
*/
char* toLower(char* s) {
    //Iterate through the entire array
    for(char *p=s; *p; p++) *p=tolower(*p); //and change the characters to lowercase
  return s;
}

/*
    Method to make a string uppercase and return it
*/
char* toUpper(char* s) {
    //Iterate through the entire array
    for(char *p=s; *p; p++) *p=toupper(*p); //and change the characters to uppercase
    return s;//return the array
}


/*
    Returns true if the char* contains the following in any case
    "t","true","yes","y"

    Returns false if the char* contains the following in any case
    "f","false","no","n"
*/
bool checkInputTrue(char* input){
    //Check the yes conditions
    bool isYes = strcmp("yes",toLower(input)) == 0; //Check for "yes" and "YES"
    bool isY = strcmp("y",toLower(input)) == 0; // Check for "y" and "Y"
    bool isTrue = strcmp("true",toLower(input)) == 0; //Check for "true" and "TRUE"
    bool isT = strcmp("t",toLower(input)) == 0; //Check for "t" and "T"

    //Check the no conditions
    bool isNo = strcmp("no",toLower(input)) == 0; //Check for "no" and "NO"
    bool isN = strcmp("n",toLower(input)) == 0; //Check for "n" and "N"
    bool isFalse = strcmp("false",toLower(input)) == 0; //Check for "false" and "FALSE"
    bool isF = strcmp("f",toLower(input)) == 0; //Check for "f" and "F"
    
    //If the input is yes or y or true or t
    if(isYes || isY || isTrue || isT){
        return true; 
    }else if(isNo || isN || isFalse || isF){ //Else if the input is no or n or false or f
        return false;
    }else{ //For anything else
        return false; //By default return false
    }

    //Exhaustive conditional, no return required.
}

/*
    Method to list all the todos in the linked list starting at the head
*/
void listAllTodos(){
    printf("=========================================\n");
    printf("============= LIST OF TODOS =============\n");
    printf("=========================================\n");

    //Start at the head
    todo* nextTodo = &head;

    //Do this bit
    do{
        printf("TODO: %-30s%-20s\n",nextTodo->name,nextTodo->done ? "DONE" : "NOT DONE");
        nextTodo = nextTodo->next;
    }while(nextTodo != NULL); //Till the next node in the list is empty
}

/*
    Method to print the application's header with title
*/
void printHeader(){
    //Print the header of the TODO app
    printf("\n");
    printf("========================================================\n");
    printf("======================= TODO APP =======================\n");
    printf("========================================================\n");
    printf("\n");
}


/*
    Method to print the available commands for the application menu
*/
void printMenu(){
    //Print the menu options
    printf("add  - Add an item\n");
    printf("rem  - Remove Item\n");
    printf("up   - Update Item\n");
    printf("ls   - List all items\n");
    printf("exit - Exit the program\n");
}

/*
    Method for prompting the user for input using a specified formatting pattern
*/
char* promptUser(char* pattern,char* prompt){
    printf("%s",prompt);
    static char answer[200];
    scanf(pattern,answer);
    fflush(stdin);
    return answer;
}

/*
    Method for saving a TODO into the linked list
*/
void saveTodo(int numberOfTodos,todo* newTodo,char* todoTrimmed,bool todoCompleted){
    //Save the todo in the linked list
    if(numberOfTodos > 0){ //If there's more than one todo
        //Start at the head
        todo* nextTodo = &head;
        
        //Go to the end of the linked list
        while(nextTodo->next != NULL) nextTodo=nextTodo->next;

        //Save the todo at the end of the linked list
        nextTodo->next = newTodo;
        
    }else{ //Otherwise there's no todos yet, so we can save it at the head
        //Save the name
        strcpy(head.name,todoTrimmed);

        //Save the status
        head.done=todoCompleted;
    }
}

void addTodo(int numberOfTodos){
    //Create a character array to store their input
    char todoTxt[100];

    //Prompt the user to enter in the todo
    strcpy(todoTxt,promptUser("%[^\n]s"," TODO > "));
    
    //Trim their response to remove whitespaces
    char* todoTrimmed = trim(todoTxt);

    // //Create a character array to store their input
    char completed[10];

    //Prompt the user if the todo is completed
    strcpy(completed,promptUser("%s"," Is this todo completed? > "));
    
    //Get a boolean based on their input
    bool todoCompleted = checkInputTrue(completed);

    // //Create a pointer to a new todo
    todo* newTodo = (todo*)malloc(sizeof(todo*));

    // //Copy the trimmed todo to the new todo's name
    strcpy(newTodo->name,todoTrimmed);

    //Set the new todo to the todoCompleted value
    newTodo->done = todoCompleted;

    //Save the todo to the linked list
    saveTodo(numberOfTodos,newTodo,todoTrimmed,todoCompleted);
}

/*
    Main entry point of the TODO application
*/
int main(int argc, char** argv){
    //Integer to keep track of how many todos we have
    int numberOfTodos = 0;

    //Print the header of the program
    printHeader();
    
    //Loop condition flag
    bool keepLooping = true;

    do{ //Start of the loop
        //Print the menu
        printMenu();

        //Character array to store the user input
        char userInput[200];

        //Propmt the user for input and copy it into the user input array
        strcpy(userInput,promptUser("%s"," >>> "));

        //Check the command input from the user
        if(strcmp(trim(userInput),"add") == 0){ //Compare the input with the add command
            //Save a new todo
            addTodo(numberOfTodos);

            //Increment the available todos
            numberOfTodos++;

        } else if(strcmp(trim(userInput),"rem") == 0){ //If they want to remove a todo
            //TODO: Add functionality to remove items from the linked list
            printf("You want to remove an item from the list\n");
        } else if(strcmp(trim(userInput),"up") == 0){ //If they want to update a todo
            //TODO: Add functionality to update an intem in the linked list
            printf("You want to update an item from the list\n");
        } else if(strcmp(trim(userInput),"ls") == 0){ //If they want to list all todos
            //Call the function to list all the todos
            listAllTodos();
        } else if(strcmp(trim(userInput),"exit") == 0){
            keepLooping = false; //Break out of the loop
        }

        //Clear the user input string
        strcpy(userInput,"");

    }while(keepLooping); //While we're still looping

    //Exit the program
    return 0;
}