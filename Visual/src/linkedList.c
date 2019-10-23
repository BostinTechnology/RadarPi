/* ========================================================================== */
/*                                                                            */
/*   linkedLists.c                                                            */
/*   (c) 2019 Ciaran Morgan                                                   */
/*                                                                            */
/*   Implementation of a double linked list                                   */
/*                                                                            */
/*   Added extra test for mid list insertion                                  */
/*                                                                            */
/* ========================================================================== */

#include <stdlib.h>
#include <stdio.h>

#include "../inc/linkedList.h"

void	listInitialise	(Linkedlist *list)
{
	// initialise the list by pointing to NULL
	list->listHead = NULL;
	list->listTail = NULL;
	list->currentNode = NULL;
    list->max_reading = 0.0;
    list->min_reading = 0.0;
    list->qty_readings = 0;

}


void	listAddHead		(Linkedlist *list, float reading)
{
	// Create new node
	Node	*node	= (Node*) malloc(sizeof(Node));
	node->reading = reading;
	
    // Check if the list is empty
	if (list->listHead == NULL) 
	{
		list->listTail = node;
        list->max_reading = reading;
        list->min_reading = reading;
        list->qty_readings = 1;
		node->nextnode = NULL;
		node->prevnode = NULL;
        
	}
	else  // list already exists
	{
		node->nextnode = list->listHead;
		list->listHead->prevnode = node;
        if (reading > list->max_reading) {
            list->max_reading = reading;
        };
        if (reading < list->min_reading) {
            list->min_reading = reading;
        };
        list->qty_readings ++;
	}
	
	// update the list structure with a new head
	list->listHead = node;
    
    return;
}

void	listAddTail		(Linkedlist *list, float reading)
{
    // Create new node
	Node	*node	= (Node*) malloc(sizeof(Node));
	node->reading = reading;
	node->nextnode	=	NULL;

    // Check if the list is empty, if so create a new list
	if (list->listHead == NULL)
	{
		list->listHead = node;
        list->max_reading = reading;
        list->min_reading = reading;
        list->qty_readings = 1;
		node->nextnode = NULL;
		node->prevnode = NULL;
	}
	else
	{
		list->listTail->nextnode = node;
		node->prevnode = list->listTail;
        if (reading > list->max_reading) {
            list->max_reading = reading;
        };
        if (reading < list->min_reading) {
            list->min_reading = reading;
        };
        list->qty_readings ++;
	}
	
	// Update the list structure with a new tail
	list->listTail = node;
    
    return;
}

// Insert a new node after the current node
void	listInsertNode	(Linkedlist *list, float reading, Node *currentnode)
{
    // Check if there is a next node, if not pass to listAddTail
    if (currentnode->nextnode == NULL) {
        listAddTail(list, reading);            // Should this be &list, &data????
    }
    // Create new node
	Node	*newnode	= (Node*) malloc(sizeof(Node));
	newnode->reading = reading;
	newnode->nextnode	= NULL;
    
    // Check if the list is empty, if so create as a new list, else link the pointers
	if (list->listHead == NULL) {
		list->listHead = newnode;
		newnode->nextnode = NULL;
		newnode->prevnode = NULL;
        list->max_reading = reading;
        list->min_reading = reading;
        list->qty_readings = 1;
	}
    else {
        
        // new node -> next node to be current node's next node
        newnode->nextnode = currentnode->nextnode;
        // new node -> previous node to be the current node's address
        newnode->prevnode = currentnode;
        // current node -> next node to be the new node's address
        currentnode->nextnode = newnode;
        if (reading > list->max_reading) {
            list->max_reading = reading;
        };
        if (reading < list->min_reading) {
            list->min_reading = reading;
        };
        list->qty_readings ++;
    }

    return;
}

// Delete the given node
void	listDeleteNode	(Linkedlist *list, float reading, Node *deletenode)
{
    // 
    
    // ToDo: This will require a new max and min value being calculated
    
}


void	listPrintNode	(Linkedlist *list)
{
	
}
