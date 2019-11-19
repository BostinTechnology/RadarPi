/* 
 * File:   linkedList.h
 * Author: Ciaran Morgan <ciaran.morgan@bostintechnology.com>
 *
 * Created on 21 September 2019, 10:20
 * 
 * Example code for providing double linked lists. Linked lists are a collection of structures
 * that can be accessed in a similar fashion to an array, but held in memory.
 * Each element points at it's predessor and sucessor and the overall structure holds
 * the first and last values
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* This is the structure required for each value (node) in the linked list.
 */
typedef struct _node 
{
	float 	reading;
	struct	_node *prevnode;
	struct	_node *nextnode;
} Node;

/* This is the strcuture used to control the nodes in the linked list. This must be
 initialised using the function described below. */
typedef struct _linkedlist 
{
	Node *listHead;
	Node *listTail;
	Node *currentNode;
    float   max_reading;
    float   min_reading;
    int     qty_readings;
} Linkedlist;


/*
 *****************************************************************************
 * Overview: Initialise the linked list ready for use
 *
 * param[in] *list : A pointer to the linked list to be initialised 
 *
 * No value is returned
 *****************************************************************************
 */
void	listInitialise      (Linkedlist *list);

/*
 *****************************************************************************
 * Overview: insert the given reading at the beginning of the list
 *
 * param[in]    *list : A pointer to the linked list
 * param[in]    reading : The value to be added into the linked list
 *
 * No return value
 * 
 *****************************************************************************
 */
void	listAddHead         (Linkedlist *list, float reading);

/*
 *****************************************************************************
 * Overview: insert the given reading at the end of the list
 *
 * param[in]    *list : A pointer to the linked list
 * param[in]    reading : The value to be added into the linked list
 *
 * No return value
 * 
 *****************************************************************************
 */
void	listAddTail         (Linkedlist *list, float reading);

/*
 *****************************************************************************
 * Overview: insert the given reading into the list after the given node
 *
 * param[in]    *list : A pointer to the linked list
 * param[in]    reading : The value to be added into the linked list
 * param[in]    *currentnode : The node to be removed from the list 
 *
 * No return value
 * 
 *****************************************************************************
 */
void	listInsertNode      (Linkedlist *list, float reading, Node *currentnode);

/*
 *****************************************************************************
 * Overview: Delete the given node from the list, be it the head, tail or one
 *          from the middle
 *
 * param[in]    *list : A pointer to the linked list 
 * param[in]    *currentnode : The node to be removed from the list 
 *
 * return status meanings         
 *          0 : success
 *          1 : <error description>
 * 
 * NOTE: NOT yet implemented
 *****************************************************************************
 */
void	listDeleteNode      (Linkedlist *list, Node *currentnode);

/*
 *****************************************************************************
 * Overview: Delete the tail node from the list. If recalc is true, the routine
 *         will recalculate the max and min values of the list
 *
 * param[in]    *list : A pointer to the linked list
 * param[in]    recalc : Set to true or false
 *
 * return status meanings         
 *          0 : success
 *          1 : invalid parameters
 * 
 * NOTE: NOT yet implemented
 *****************************************************************************
 */
void	listDeleteTail      (Linkedlist *list, int recalc);

/*
 *****************************************************************************
 * Overview: Delete the head node from the list. If recalc is true, the routine
 *         will recalculate the max and min values of the list
 *
 * param[in]    *list : A pointer to the linked list 
 * param[in]    recalc : Set to true or false
 *
 * return status meanings         
 *          0 : success
 *          1 : invalid parameters
 * 
 * NOTE: NOT yet implemented
 *****************************************************************************
 */
void	listDeleteHead      (Linkedlist *list, int recalc);
/*
 *****************************************************************************
 * Overview: Set the list maximum value property of the linked list
 *
 * param[in]    *list : A pointer to the linked list in use 
 * param[in]    maxvalue : the maximum value to be set 
 *
 * No return value 
 *****************************************************************************
 */
void    listSetMax          (Linkedlist *list, float maxvalue);

/*
 *****************************************************************************
 * Overview: Set the list minimum value property of the linked list
 *
 * param[in]    *list : A pointer to the linked list in use 
 * param[in]    minvalue : the minimum value to be set 
 *
 * No return value 
 *****************************************************************************
 */
void    listSetMin          (Linkedlist *list, float minvalue);



#endif /*LINKEDLIST_H */