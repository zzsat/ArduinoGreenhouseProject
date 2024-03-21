#include <stdio.h>
#include <stdlib.h>


void InsertFirst(struct LinkedList**first, struct LinkedList*el)
{ //inserts el at the beginning and updates first

    if (el == NULL)	{
            return;
    }

    el->next = *first;
    *first = el;  
}

int isMember (struct LinkedList **first, struct LinkedList *el) 
{ //function returns 1 if el is a member in the list and 0 otherwise

	struct LinkedList *temp = *first;

	while (temp != NULL)  {
    	if (temp == el)  
                return 1;
		temp = temp ->next;
	}
  	return 0;
}

void printList()  
{
        struct LinkedList *first = List;
	if (first == NULL)
		return;

	struct LinkedList *temp = first;

	while (temp != NULL)	{

              printf("\n");
              printf("Temperature: %f\n ", temp -> temperature);
              
              printf("Date D/M/Y: %i:%i:%i\n", temp->day,temp->month, temp->year);
              
              printf("Time S/M/H: %02d:%02d:%d\n", temp -> second, temp->minute, temp->hour);
              
              temp = temp->next;
	}
}






