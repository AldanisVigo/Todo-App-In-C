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
#include <fcntl.h>

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
    printf("===================================================================\n");
    printf("============================= LIST OF TODOS =======================\n");
    printf("===================================================================\n");
    printf("%-15s%-30s%-20s\n","TODO_ID","CONTENT","STATUS");
    //Start at the head
    todo* nextTodo = &head;
    int todoId = 0;
    //Do this bit
    do{
        printf("%-15d%-30s%-20s\n",todoId++,nextTodo->name,nextTodo->done ? "DONE" : "NOT DONE");
        nextTodo = nextTodo->next;
    }while(nextTodo != NULL); //Till the next node in the list is empty
}

/*
    Method to print the application's header with title
*/
void printHeader(){
    //Print the header of the TODO app
    printf("\n");
    printf("===================================================================\n");
    printf("============================== TODO APP ===========================\n");
    printf("===================================================================\n");
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
    Method to retrieve the contents of the todos.vigo file and reconstruct the linked list
*/
int getExistingTodos(){
    //Counter for the number of todos available
    int todoCount = 0;

    //Get a pointer to the todos.vigo file
    FILE* todosFile = fopen("todos.vigo","r");

    if(todosFile != NULL){ //if file exists
        while(!feof(todosFile)){ //Go through it until we hit the end of the file

            //Array to store the next line
            char nextFileLine[200];

            //Get the next line
            fgets(nextFileLine,200,todosFile);
            
            //Create a new todo
            todo* newTodoFromFile; //Create a new todo

            //Allocate some memory for the new todo
            newTodoFromFile = (todo*)malloc(sizeof(todo*));

            //Get the token before the first "," in the line
            char* token = strtok(nextFileLine,",");
            
            int tokenIndex = 0; //Start with the 0th token 
            while(token != NULL){ //While the token is not NULL
                if(tokenIndex == 0){ //If we're on the 0th token
                    strcpy(newTodoFromFile->name,token); //Copy the token to the new todo's name
                }else if(tokenIndex == 1){ //if we're on the 1st token
                    if(strcmp(trim(token),"true") == 0){ //Compare the token with the string "true"
                        newTodoFromFile->done = true; //If it matches set the new todo's done bool to true
                    }else if(strcmp(trim(token),"false") == 0){ //Otherwise if it matches with the string "false"
                        newTodoFromFile->done = false; //Set the new todo's done bool to false
                    }
                }
                tokenIndex++; //Go to the next token index
                token = strtok(NULL,","); //Advance the token to the next comma.
            }
            
            //Save the todo to the linked list
            saveTodo(todoCount,newTodoFromFile,newTodoFromFile->name,newTodoFromFile->done);

            //Increment the number of available todos.
            todoCount++;
        }
    }

    //Close the file
    fclose(todosFile);

    //Return the number of todos we read from the file
    return todoCount;
}

/*
    Method asks the user to enter the id of the todo they would like to remove
    then it confirms that the user want's to remove it and 
    removes it from the linked list
    The first todo is the default todo head, and that one is not deleted, it's just cleared.
*/
void removeTodo(int* numberOfTodos){
    //Variable to store the user's input
    char todoId[100];

    //Prompt the user for a todo id
    strcpy(todoId,promptUser("%s"," Enter the id of the todo you'd like to remove > "));

    //Confirm that the user actually wants to delete the todo
    char confirmRemove[100];

    //Prompt the user for confirmation
    strcpy(confirmRemove,promptUser("%s", "Are you sure you want to remove this todo?"));

    if(checkInputTrue(confirmRemove)){
        //TODO : Add logic to remove the todo at the given id index
        
        //If we only have 1 todo left in the pie, then we can't delete
        if(*numberOfTodos > 1){
            //Otherwise delete as normal
            todo* n = &head;
            int index = atoi(todoId);
            if(index == 0){ //Replace the head node values with the values in the second node.                    
                //Save a reference to the node after the head
                todo* nextNode = n->next;

                //Copy the name from the next node
                strcpy(n->name,nextNode->name); 

                //And the status from the next node
                n->done = nextNode->done;

                //Replace the head node next pointer to the third node.
                n->next = nextNode->next;

                //Free the memory for the nextNode
                free(nextNode);

            }else if(index == *numberOfTodos - 1){ //Delete end of list

                //Iterate till we get to the one before last
                while(n->next->next != NULL) n = n->next;

                //Free it's next pointer's memory
                free(n->next);

                //Clear the last item by setting it's next pointer to NULL
                n->next = NULL; 
            }else{
                //Go to one before the desired node
                for(int i = 0; i < index - 1;i++) n = n->next;
                
                //Save the desired node reference
                todo* selectedNodeReference = n->next;

                //Jump over the node we want to remove
                n->next = selectedNodeReference->next;

                //Free the memory for the node we just jumped
                free(selectedNodeReference);
            }

            //Decrement the number of todos
            *numberOfTodos = *numberOfTodos - 1;

            //Let the user know we deleted the todo
            printf("Deleted todo.\n");
        }else{
            //Clear the head node's name
            strcpy(head.name,"");

            //Set the head's next node to NULL
            head.next = NULL;

            //Set the head node's done to false
            head.done = false;

            //Let the user know we cleared the default todo.
            printf("Cleared default todo.\n");
        }
    }
}

/*
    Main entry point of the TODO application
*/
int main(int argc, char** argv){
    //Integer to keep track of how many todos we have
    int numberOfTodos = 0;

    //Read the contents of the todos.vigo file and reconstruct the linked list
    numberOfTodos = getExistingTodos();

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
            //List all the todos            
            listAllTodos();
            
            //Remove a todo
            removeTodo(&numberOfTodos);

        } else if(strcmp(trim(userInput),"up") == 0){ //If they want to update a todo
            //TODO: Add functionality to update an intem in the linked list
            printf("You want to update an item from the list\n");
        } else if(strcmp(trim(userInput),"ls") == 0){ //If they want to list all todos
            //Call the function to list all the todos
            listAllTodos();
        } else if(strcmp(trim(userInput),"exit") == 0){
            //Save the contents of our linked list to a file for persistence
            FILE* todosFile = fopen("todos.vigo","w");
            
            //Create a reference to the head of the todos list
            todo* n = &head;

            //Iterate through the list until we hit an empty node
            while(n != NULL){
                //Create a character array to store the next line to save to the todos file
                char newFileLine[200] = ""; 

                //Concatenate in the name
                strcat(newFileLine,n->name);
                
                //Add a comma 
                strcat(newFileLine,",");

                //Add the status
                strcat(newFileLine,n->done ? "true" : "false"); 

                //And for all lines except the last line
                if(n->next != NULL){ 
                    //Advance to the next line by concatenating a newline character
                    strcat(newFileLine,"\n"); 
                }
                
                //Save the line to the file
                fputs(newFileLine,todosFile); 

                //Advance the node to the next node
                n = n->next;
            }

            //Close the file
            fclose(todosFile);

            //Delete our linked list memory to avoid memory leaks.
            todo* nextTodo = &head; //Start off at the head
            int todoIndex = 0; //Start at the head

            //Iterate through all the todos in the linked list
            while(nextTodo != NULL){
                //Save a refrence to the next todo
                todo* nextTodoRef = nextTodo->next; 

                //Free the memory for all todos except the head
                if(todoIndex != 0) free(nextTodo);

                //Increment the todo index
                todoIndex++; 

                //Advance the next todo to the next one
                nextTodo = nextTodoRef; 
            }

            //Clear the head pointers data so we don't leak
            strcpy(head.name,"");
            head.done = false;
            head.next = NULL;

            //Break out of the loop
            keepLooping = false; 
        }

        //Clear the user input string
        strcpy(userInput,"");

    }while(keepLooping); //While we're still looping

    //Exit the program
    return 0;
}