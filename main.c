#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Project.h"

int main()

{
    int choice;
    int i=0;

    do
    {
        printf("Enter the number corresponding to the function you need:\n\n1-Load\n2-Add new contact\n3-Search for a contact\n4-Display all contacts\n5-Delete a contact\n6-Modify a contact\n7-Sort contacts\n8-Save changes\n9-exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            load();
            break;

        case 2:
            Add_Contact();
            break;

        case 3:
            Search();
            break;
        case 4:
            for(i=0; i<count; i++)
                Display(i);
                printf("\n");
            break;

        case 5:
            Delete();
            break;

        case 6:
            Modify();
            break;
        case 7:
            sort();
            break;
        case 8:
            Save();
            break;
        case 9:
            Exit_program();
            break;
        default:
            printf("enter a valid number\n");

        }

    }
    while(choice!=9);


    return 0;
}
