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

#include "linkedList.h"

void	listInitialise	(Linkedlist *list)
{
	// initialise the list by pointing to NULL
	list->listHead = NULL;
	list->listTail = NULL;
	list->currentNode = NULL;

}


void	listAddHead		(Linkedlist *list, void* data)
{
	// Create new node
	Node	*node	= (Node*) malloc(sizeof(Node));
	node->data = data;
	
    // Check if the list is empty
	if (list->listHead == NULL) 
	{
		list->listTail = node;
		node->nextnode = NULL;
		node->prevnode = NULL;
	}
	else  // list already exists
	{
		node->nextnode = list->listHead;
		list->listHead->prevnode = node;
	}
	
	// update the list structure with a new head
	list->listHead = node;
    
    return;
}

void	listAddTail		(Linkedlist *list, void* data)
{
    // Create new node
	Node	*node	= (Node*) malloc(sizeof(Node));
	node->data = data;
	node->nextnode	=	NULL;

    // Check if the list is empty, if so create a new list
	if (list->listHead == NULL)
	{
		list->listHead = node;
		node->nextnode = NULL;
		node->prevnode = NULL;
	}
	else
	{
		list->listTail->nextnode = node;
		node->prevnode = list->listTail;
	}
	
	// Update the list structure with a new tail
	list->listTail = node;
    
    return;
}

// Insert a new node after the current node
void	listInsertNode	(Linkedlist *list, void* data, Node *currentnode)
{
    // Check if there is a next node, if not pass to listAddTail
    if (currentnode->nextnode == NULL) {
        listAddTail(list, data);            // Should this be &list, &data????
    }
    // Create new node
	Node	*newnode	= (Node*) malloc(sizeof(Node));
	newnode->data = data;
	newnode->nextnode	= NULL;
    
    // Check if the list is empty, if so create as a new list, else link the pointers
	if (list->listHead == NULL) {
		list->listHead = newnode;
		newnode->nextnode = NULL;
		newnode->prevnode = NULL;
	}
    else {
        
        // new node -> next node to be current node's next node
        newnode->nextnode = currentnode->nextnode;
        // new node -> previous node to be the current node's address
        newnode->prevnode = currentnode;
        // current node -> next node to be the new node's address
        currentnode->nextnode = newnode;
    }

    return;
}

// Delete the given node
void	listDeleteNode	(Linkedlist *list, void* data, Node *deletenode)
{
    // 
    
}


void	listPrintNode	(Linkedlist *list)
{
	
}
