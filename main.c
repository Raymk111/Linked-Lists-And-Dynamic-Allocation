#include <stdio.h>
#include "stdlib.h"
#include "string.h"

FILE * fptr;

typedef struct
{
    char title[30];
    char dpt[40];
    char offNo[8];
    char offPh[16];
    char mobPh[16];
    char fax[16];
} job;

typedef struct
{
    char addr[30];
    char city[30];
    char state[20];
    char zip[10];
    char country[30];
    
} address;

struct contacts
{
    char uName[30];
    char fName[30];
    char lName[30];
    char dName[60];
    job *jobd;
    address *address;
    struct contacts *prevContact;
    struct contacts *nextContact;
};

void openFile()
{
    fptr = fopen("contacts.txt", "r");
    if(fptr==NULL)
    {
        printf("Error opening File");
    }
}

void closeFile()
{
    fclose(fptr);
}


struct contacts * initP()
{
    struct contacts *uPtr = NULL;
    uPtr = (struct contacts*)malloc(sizeof(struct contacts));
    uPtr->jobd = (job*)malloc(sizeof(job));
    uPtr->address = (address*)malloc(sizeof(address));
    uPtr->nextContact = NULL;
    uPtr->prevContact = NULL;
    return uPtr;
}

void readFile(struct contacts *startPtr)
{
    char strBuff[200];
    fgets(strBuff, 199, fptr);
    int i = 0;
    struct contacts *prevPtr = NULL;
    struct contacts *currPtr;
    prevPtr = startPtr;
    currPtr = prevPtr;
    while(fgets(strBuff, 199, fptr)!=NULL)
    {
        if(i>0)
        {
            prevPtr = currPtr;
            currPtr = initP();
            currPtr->prevContact = prevPtr;
            prevPtr->nextContact = currPtr;
        }
        char delim[] = ",";
        char *token;
        
        token = strtok(&strBuff[0], delim);
        strcpy(currPtr->uName, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->fName, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->lName, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->dName, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->jobd->title, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->jobd->dpt, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->jobd->offNo, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->jobd->offPh, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->jobd->mobPh, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->jobd->fax, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->address->addr, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->address->city, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->address->state, token);
        token = strtok(NULL, delim);
        strcpy(currPtr->address->zip, token);
        token = strtok(NULL, "\r\n");
        strcpy(currPtr->address->country, token);
        i++;
    }
    
}

//prints linked list and frees pointers
void printLList(struct contacts *startPtr)
{
    struct contacts *currPtr;
    currPtr = startPtr;
    
    while(currPtr!=NULL)
    {
        printf("User Name: %s\n", currPtr->uName);
        printf("First Name: %s\n", currPtr->fName);
        printf("Last Name: %s\n", currPtr->lName);
        printf("Display Name: %s\n", currPtr->dName);
        printf("Job Title: %s\n", currPtr->jobd->title);
        printf("Departement: %s\n", currPtr->jobd->dpt);
        printf("Office Number: %s\n", currPtr->jobd->offNo);
        printf("Office Phone: %s\n", currPtr->jobd->offPh);
        printf("Mobile Phone: %s\n", currPtr->jobd->mobPh);
        printf("Fax: %s\n", currPtr->jobd->fax);
        printf("Address: %s\n", currPtr->address->addr);
        printf("City: %s\n", currPtr->address->city);
        printf("State: %s\n", currPtr->address->state);
        printf("ZIP: %s\n", currPtr->address->zip);
        printf("Country or Region: %s\n", currPtr->address->country);
        printf("_____________________________________\n\n");
        if(currPtr->nextContact==NULL)
        {
            free(currPtr->prevContact);
            currPtr->prevContact = NULL;
            free(currPtr);
            currPtr = NULL;
        }
        else
        {
            currPtr = currPtr->nextContact;
            free(currPtr->prevContact);
            currPtr->prevContact=NULL;
        }
    }
}

int main()
{
    openFile();
    struct contacts *startPtr = NULL;
    startPtr = initP();
    readFile(startPtr);
    closeFile();
    printLList(startPtr);
    return 0;
}
