//Name: Richard Gan Soon Ching
//Student ID: 20303960

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int tcount = 1; //book counting
int write = 0;//check if file has been written before

struct book { //book structure
    char *title;  
    char *author; 
    char *subject;
 }; 

struct library {  //library structure
    struct book collection;
    int num_books;
    struct library *next;
 }; 

 typedef struct library Library; // library and Library is the same thing

void copyBook(struct book* dest, struct book* source); //function to copy book
void addBook(struct library** thislib, struct book* newbook); // function to add book
void deleteBookByTitle(struct library** thislib, char* title); // function to delete book by title
void deleteBooksByAuthor(struct library** thislib, char* author); // function to delete books by author
void searchBookByTitle(struct library** thislib, char* title); // function to search book by title
void searchBooksByAuthor(struct library** thislib, char* author); // function to search book by author
void listBooksByAuthor(struct library** thislib, char* author); // function to list books by author in ascending order
void listBooksBySubject(struct library** thislib, char* subject); // function to list books by subject in descending order
void printList(struct library** thislib); // function to print everything
void emptyLibrary(void); // function to print error cuz of empty library
void hitMax(void); // function to print error cuz of max library
void sameBook(void); // function to print error cuz of same book in library
void maxTitle(void); // function to print error title exceeds 49 characters
void maxAuthor(void);// function to print error author exceeds 49 characters
void maxSubject(void);// function to print error subject exceeds 49 characters
void incorrectInput(void);// function to print error input not between 1-8


int main(void){
    struct library* startPtr = NULL; // create startPtr
    FILE *fp; // create FILE pointer
    unsigned int input = 0; // create input for switch
    unsigned int loopnum = 0; // create number of loop
    
    
    fp = fopen("library.txt", "r"); // open file for read
    fscanf(fp,"%d", &loopnum);// read the file to get number of loop

    while(loopnum != 0){ 
        char title[50] = ""; // create title, author and subject variable
        char author[50] = "";
        char subject[50] = "";
        
        fscanf(fp,"%d", &input);
        if(input < 1 || input > 8){// checking for correct inputs
            incorrectInput();
        }
        else{ // read the file for specific command for switch
            switch(input){
                case 1: 
                if(tcount >= 30){ //check for number of books in library
                    hitMax(); // go to hit max function
                }
                else{
                    fseek(fp, -3, SEEK_CUR); // go to end of last line
                    fscanf(fp, "%*d %s %s %s", title, author, subject); // scan for title author and subject
                    if(title[49] != '\0'){// checking to see if title, author and characters exceeded 49 character
                        maxTitle();
                    }
                    else if(author[49] != '\0'){
                        maxAuthor();
                    }
                    else if(subject[49] != '\0'){
                        maxSubject();
                    }
                    else{
                        struct book book2add; // create a structure for newbook
                        for(int i = 0; title[i] != '\0'; i++ ){ // capitalize title author and subject
                            title[i]=toupper(title[i]);
                        }
                        for(int i = 0; author[i] != '\0'; i++ ){
                            author[i]=toupper(author[i]);
                        }
                        for(int i = 0; subject[i] != '\0'; i++ ){
                            subject[i]=toupper(subject[i]);
                        }
                        book2add.title = malloc(sizeof(char)*50); //malloc structure
                        book2add.author = malloc(sizeof(char)*50);
                        book2add.subject = malloc(sizeof(char)*50);
                        book2add.title = title; // input scanned content into structure
                        book2add.author = author;
                        book2add.subject = subject;
                        
                        addBook(&startPtr, &book2add); // pass startPtr and newbook to addBook function
                    }
                }
                break;

                case 2:
                if(startPtr == NULL){ // same as previous cases
                    emptyLibrary();
                }
                else{
                    fseek(fp, -3, SEEK_CUR);
                    fscanf(fp, "%*d %s", title); // scan for title
                    if(title[49] != '\0'){
                        maxTitle();
                    }
                    else{
                        for(int i = 0; title[i] != '\0'; i++ ){ // capitalize
                            title[i] = toupper(title[i]);
                        }
                        deleteBookByTitle(&startPtr, title); //pass startPtr and title to delete to deleteBookByTitle function
                    }
                }
                break;

                case 3:
                if(startPtr == NULL){ // same as previous cases
                    emptyLibrary();
                }
                else{
                    fseek(fp, -3, SEEK_CUR);
                    fscanf(fp, "%*d %s",author);// scan for author
                    if(author[49] != '\0'){
                        maxAuthor();
                    }
                    else{
                        for(int i = 0; author[i] != '\0'; i++ ){
                            author[i] = toupper(author[i]);
                        }
                        deleteBooksByAuthor(&startPtr, author);
                    }
                }
                break;

                case 4:
                if(startPtr == NULL){// same as previous cases
                    emptyLibrary();
                }
                else{
                    fseek(fp, -3, SEEK_CUR);
                    fscanf(fp, "%*d %s", title);// scan for title
                    if(title[49] != '\0'){
                        maxTitle();
                    }
                    else{
                        for(int i = 0; title[i] != '\0'; i++ ){
                            title[i]=toupper(title[i]);
                        }
                        
                        searchBookByTitle(&startPtr, title);
                    }
                }
                break;

                case 5:
                if(startPtr == NULL){// same as previous cases
                    emptyLibrary();
                }
                else{
                    fseek(fp, -3, SEEK_CUR);
                    fscanf(fp, "%*d %s",author);// scan for author
                    if(author[49] != '\0'){
                        maxAuthor();
                    }
                    else{
                        for(int i = 0; author[i] != '\0'; i++ ){
                            author[i] = toupper(author[i]);
                        }

                        searchBooksByAuthor(&startPtr, author);
                    }
                }
                break;

                case 6:
                if(startPtr == NULL){// same as previous cases
                    emptyLibrary();
                }
                else{
                    fseek(fp, -3, SEEK_CUR);
                    fscanf(fp, "%*d %s",author);// scan for author
                    if(author[49] != '\0'){
                        maxAuthor();
                    }
                    else{
                        for(int i = 0; author[i] != '\0'; i++ ){
                            author[i] = toupper(author[i]);
                        }

                        listBooksByAuthor(&startPtr, author);
                    }
                }
                break;

                case 7:
                if(startPtr == NULL){// same as previous cases
                    emptyLibrary();
                }
                else{
                    fseek(fp, -3, SEEK_CUR);
                    fscanf(fp, "%*d %s",subject);// scan for subject
                    if(subject[49] != '\0'){
                        maxSubject();
                    }
                    else{
                        for(int i = 0; subject[i] != '\0'; i++ ){
                            subject[i] = toupper(subject[i]);
                        }

                        listBooksBySubject(&startPtr, subject);
                    }
                }
                break;

                case 8:
                if(startPtr == NULL){// same as previous cases
                    emptyLibrary();
                }
                else{
                printList(&startPtr);
                }
                break;
            }
        }
        loopnum--;
    }
    return 0;
}

void copyBook(struct book* dest, struct book* source){ 
    strcpy(dest->title, source->title); //use strcpy to cpy from source to destination
    strcpy(dest->author, source->author);
    strcpy(dest->subject, source->subject);
}

void addBook(struct library** thislib, struct book* newbook){
    struct library* newNode; // create Nodes
    struct library* previousNode;
    struct library* currentNode;
    int comps; // used to compare for similar books
    FILE* fp;
    if(write == 0){ // check to see if output.txt has been written into before
        fp = fopen("output.txt", "w");//open file to write
        write++;
    }
    else{
        fp = fopen("output.txt", "a");//open file to append
    }

    newNode = malloc(sizeof(Library)); //allocate memeory for newNode
    newNode->collection.title = malloc(50*sizeof(char));
    newNode->collection.author = malloc(50*sizeof(char));
    newNode->collection.subject = malloc(50*sizeof(char));

    if(newNode != NULL){
        strcpy(newNode->collection.title, newbook->title); // input content of newbook into the newNode
        strcpy(newNode->collection.author, newbook->author);
        strcpy(newNode->collection.subject, newbook->subject);
        newNode->num_books = tcount; // num_book counter
        tcount++; // add tcount
        newNode->next = NULL; //set newNode->next to NULL
        previousNode = NULL; //set previousNode to NULL
        currentNode = *thislib; //set currentNode to the start of the linked list
        }
    while(currentNode != NULL){
            if(comps = strcmp(currentNode->collection.title, newbook->title) == 0){
                sameBook(); //if there is the a similar book within the linked list return
                return;
            }
            previousNode = currentNode; // going through the list
            currentNode = currentNode->next;
        }
        
        if(previousNode == NULL){// if there is nothing in the list set the newNode as the starting Node
            newNode->next = *thislib;
            *thislib = newNode;
        }
        else{
            previousNode->next = newNode;// add to the end of the list
            newNode->next = currentNode;
        }
    fprintf(fp, "The book %s author %s subject %s has been added to library.\n\n", newbook->title, newbook->author, newbook->subject);
    fclose(fp);

   
}

void deleteBookByTitle(struct library** thislib, char* title){
    struct library* temp; // set Nodes
    struct library* previousNode;
    struct library* currentNode;
    int comps; //set variable to compare string
    FILE* fp;
    if(write == 0){
        fp = fopen("output.txt", "w");//open file to write
        write++;
    }
    else{
        fp = fopen("output.txt", "a");//open file to append
    }
    
    
    if((comps = strcmp(title, (*thislib) ->collection.title)) == 0) { //delete book if the first Node matches
        temp = *thislib;
        *thislib = (*thislib)->next;
        fprintf(fp, "The book %s has been removed from the library\n\n", title);
        free(temp);
        tcount--;// minus tcount
        fclose(fp);
        return;
    }
    else{
        previousNode = *thislib;
        currentNode = (*thislib)->next;

        while( currentNode->next->next != NULL){ //move to second last Node
            if (( comps = strcmp(title, currentNode->collection.title)) == 0){ //replace currentNode with temp if the title matches
                temp = currentNode;
                previousNode->next = temp;
                temp->next = currentNode->next;
            }
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        if (temp != NULL){ 
            copyBook(&temp->collection, &currentNode->collection); // copy second last Node and replace content of temp with it
            previousNode->next = currentNode->next; //link the previousNode with the next one
            tcount--;// minus tcount
            free(currentNode); //free currentNode
        }
        else{
            if(( comps = strcmp(title, currentNode->collection.title)) == 0){ //check to see if second last Node title matches if so delete
                previousNode->next = currentNode->next;
                tcount--;// minus tcount
                free(currentNode);
            }
            previousNode = currentNode;//check to see if last Node title matches is so delete
            currentNode = currentNode->next;
            if(( comps = strcmp(title, currentNode->collection.title)) == 0){
                previousNode->next = NULL;
                tcount--;// minus tcount
                free(currentNode);
            }
            previousNode = currentNode;
            currentNode = currentNode->next;
            if(currentNode == NULL){ //if there is no match print
                fprintf(fp, "Deletion cannot be performed as the requested item does not exist\n\n");
            }
        }
        fprintf(fp, "The book %s has been removed from the library\n\n", title);
        fclose(fp);
    }
    
}

void deleteBooksByAuthor(struct library** thislib, char* author){ 
    struct library* currentNode1; // set Nodes
    struct library* previousNode1;
    int comps; // set variable to compare string
    int count2delete;// set variable to calculate number of books deleted
    currentNode1 = *thislib;
    previousNode1 = NULL;
    FILE* fp;
    if(write == 0){
        fp = fopen("output.txt", "w");//open file to write
        write++;
    }
    else{
        fp = fopen("output.txt", "a");//open file to append
    }
    
    
    while(currentNode1 != NULL){ //loop while there is currentNode1 isnt empty
        
        if((comps = strcmp(author, currentNode1->collection.author)) == 0) { //delete book if the first Node matches
            *thislib = (*thislib)->next; //set the nextNode as the startNode
            fprintf(fp, "The book %s author %s has been deleted.\n\n", currentNode1->collection.title, currentNode1->collection.author);
            currentNode1 = *thislib; //set currentNOde1 with next startNode
            count2delete++;// count
        }
        else{
            struct library* currentNode2 = *thislib;// set second pair of Nodes to find second last node
            struct library* previousNode2 = NULL;
            
        
            while( currentNode1 != NULL && ( comps = strcmp(author, currentNode1->collection.author)) != 0){ //find the node with matched author
                previousNode1 = currentNode1;
                currentNode1 = currentNode1->next;
            }
            
            while( currentNode2->next->next != NULL ){ // find the second last Node
                previousNode2 = currentNode2;
                currentNode2 = currentNode2->next;
            }

            
            if(currentNode1 != NULL){ // replace content of currentNode1 with second last node(currentNode2)
            fprintf(fp, "The book %s author %s has been deleted.\n\n", currentNode1->collection.title, currentNode1->collection.author);
            copyBook(&currentNode1->collection, &currentNode2->collection);
            count2delete++;//+1 to count2delete
            previousNode2->next = currentNode2->next;//link the previousNode of currentNode2 with the next
            free(currentNode2);
            currentNode1 = currentNode1->next;//move currentNode1 to the next node
            }
            
            
        }
    }
    tcount = tcount - count2delete;//delete number of books
    if(count2delete == 0){
        fprintf(fp, "No books with author %s to be deleted\n\n", author);
    }
    fclose(fp);
}


void searchBookByTitle(struct library** thislib, char* title){
    struct library* previousNode;//set nodes
    struct library* currentNode;
    FILE* fp;
    if(write == 0){
        fp = fopen("output.txt", "w");//open file to write
        write++;
    }
    else{
        fp = fopen("output.txt", "a");//open file to append
    }

    previousNode = NULL;
    currentNode = *thislib;
    int compare;
    while(currentNode != NULL && (compare = strcmp(currentNode->collection.title, title)) != 0){// search for similar titles
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        
        if(currentNode == NULL){
            fprintf( fp, "The book %s is currently not in the library\n\n", title);// print if there is no match
        }
        else{
            fprintf(fp,"The book %s is currently in the library\n\n", title);// print if there is a match
        }
        fclose(fp);
}

void searchBooksByAuthor(struct library** thislib, char* author){
    struct library* previousNode;// set nodes
    struct library* currentNode;
    FILE* fp;
    if(write == 0){
        fp = fopen("output.txt", "w");//open file to write
        write++;
    }
    else{
        fp = fopen("output.txt", "a");//open file to append
    }
    
    previousNode = NULL;
    currentNode = *thislib;
    int compare;
    int bkbyauthor = 0;// set variable to check if there are any matches
    while(currentNode != NULL){
            if((compare = strcmp(currentNode->collection.author, author)) == 0){// if there are any matches print book
                fprintf(fp, "The book %s authored by %s is currently in the library\n", currentNode->collection.title, author);
                bkbyauthor++;// +1 to variable
            }
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        
    if(bkbyauthor == 0){ // if there are no matches print
        fprintf(fp, "No books authored by %s is currently in the library\n\n", author);

    fclose(fp);
    }
}

void listBooksByAuthor(struct library** thislib, char* author){
    struct library* previousNode;// set Nodes
    struct library* currentNode;
    FILE* fp;
    if(write == 0){
        fp = fopen("output.txt", "w");//open file to write
        write++;
    }
    else{
        fp = fopen("output.txt", "a");//open file to append
    }

    char comp = 'A';// set a variable to compare first letter of the alphabet to find book from 'A' to 'Z'
    int compare;
    fprintf(fp, "List all books by %s:\n", author);

    while( comp != '['){// while comp is not '[' which is the end of the alphabetical letters in ascii
        previousNode = NULL;
        currentNode = *thislib;
         while(currentNode != NULL){
             if((compare = strcmp(currentNode->collection.author, author)== 0) && currentNode->collection.title[0] == comp ){// check if there are matches with author and first letter of the book is match with comp
                fprintf(fp,"\t%s %s %s\n", currentNode->collection.title, currentNode->collection.author, currentNode->collection.subject);// if so print
            }
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        comp++;//go to next letter
    }
    fclose(fp);
}

void listBooksBySubject(struct library** thislib, char* subject){
    struct library* previousNode; // set Nodes
    struct library* currentNode;
    FILE* fp;
    if(write == 0){
        fp = fopen("output.txt", "w");//open file to write
        write++;
    }
    else{
        fp = fopen("output.txt", "a");//open file to append
    }

    char comp = 'Z';// similar to list by author function but uses subject instead of author and finds book for 'Z' to 'A'
    int compare;
    char first;
    fprintf(fp, "List all books on %s:\n", subject);
    

    while( comp != '@'){
         previousNode = NULL;
        currentNode = *thislib;
         while(currentNode != NULL){
             if((compare = strcmp(currentNode->collection.subject, subject)) == 0 && currentNode->collection.title[0] == comp ){
                fprintf(fp,"\t%s %s %s\n", currentNode->collection.title, currentNode->collection.author, currentNode->collection.subject);
            }
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        comp--;// go to previous letter
    }
    fclose(fp);
}

void printList(struct library** thislib){ // print every book in linked list
    struct library* currentNode;
    currentNode = *thislib;
    FILE* fp;
    if(write == 0){
        fp = fopen("output.txt", "w");//open file to write
        write++;
    }
    else{
        fp = fopen("output.txt", "a");//open file to append
    }
    
    fprintf(fp, "List all books in library:\n");
     while(currentNode != NULL){   
         fprintf(fp,"\t%s %s %s\n", currentNode->collection.title, currentNode->collection.author, currentNode->collection.subject);
         currentNode = currentNode->next;

        }
    
}

void emptyLibrary(void){// used to print errors
    FILE* fp;
    fp = fopen("output.txt", "a");
    
    fprintf(fp, "The library is empty.\n\n");
    fclose(fp);
}

void hitMax(void){// used to print errors
    FILE* fp;
    fp = fopen("output.txt", "a");
    
    fprintf(fp, "Maximum num of books has been reached.\n\n");
    fclose(fp);
}

void sameBook(void){// used to print errors
    FILE* fp;
    fp = fopen("output.txt", "a");
    
    fprintf(fp, "Similar book in library.\n\n");
    fclose(fp);
}

void maxTitle(void){// used to print errors
    FILE* fp;
    fp = fopen("output.txt", "a");
    
    fprintf(fp, "Title exceeds 49 characters.\n\n");
    fclose(fp);
}

void maxAuthor(void){// used to print errors
    FILE* fp;
    fp = fopen("output.txt", "a");
    
    fprintf(fp, "Author exceeds 49 characters.\n\n");
    fclose(fp);
}

void maxSubject(void){// used to print errors
    FILE* fp;
    fp = fopen("output.txt", "a");
    
    fprintf(fp, "Subject exceeds 49 characters.\n\n");
    fclose(fp);
}

void incorrectInput(void){
    FILE* fp;
    fp = fopen("output.txt", "a");
    
    fprintf(fp, "Input is not within 1-8.\n\n");
    fclose(fp);
}

// -2 search function did not work
// -1 List function has no hints when no books exist
// -1 function(8) did not work
// -2 did not update the variable num_books
// -1 delete function did not update the variable num_books
