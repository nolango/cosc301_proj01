#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


void list_print(struct node *head){
	printf("*** list contents begin ***\n");
	while(head != NULL){
		printf("%d\n",head->value);
		head = head->next;
	}
	printf("*** list contents end ***\n");	
}

void sorted_insert(int value, struct node **head){
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->value = value;

	// if list is empty
	if((*head) == NULL){
		newnode->next = NULL;
		*head = newnode;
		return;
	}
	
	// if first node value is >= value
	if((*head)->value >= value){
		newnode->next = *head;
		*head = newnode;
		return;
	}

	struct node* current = *head;
	struct node* last = *head;
	// if multiple nodes in list, traverse list
	while(1){

		if(current == NULL){
			newnode->next = NULL;
			last->next = newnode;
			return;
		}
		if(current->value >= value){
			newnode->next = current;
			last->next = newnode;
			return;
		}

		last = current;
		current = current->next;	
	}	
}

int list_delete(const int value, struct node **head){
	if (*head == NULL)
		return 0;
	
	struct node* current = *head;
	struct node* last = NULL;

	while(current != NULL) {
		// if first node is node to delete
		if ((*head)->value == value){
			// if only one node left
			if ((*head)->next == NULL){
				free(current);
				*head = NULL;
				return 1;
			} else {	 								
				*head = (*head)->next;
				free(current);
				return 1;
			}
		} else {									
			if (current->value == value){
					last->next = current->next;
					free(current);
					return 1;
			} // end if
		} // end else

		last = current;
		current = current->next;
	}
	return 0;
}







