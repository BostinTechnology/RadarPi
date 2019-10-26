/* ========================================================================== */
/*                                                                            */
/*   linkedList.h                                                             */
/*   (c) 2019 Ciaran Morgan                                                   */
/*                                                                            */
/*   Implementation of a double linked list                                   */
/*                                                                            */
/*   Added extra test for mid list insertion                                  */
/*                                                                            */
/* ========================================================================== */


typedef struct _node 
{
	float 	reading;
	struct	_node *prevnode;
	struct	_node *nextnode;
} Node;

typedef struct _linkedlist 
{
	Node *listHead;
	Node *listTail;
	Node *currentNode;
    float   max_reading;
    float   min_reading;
    int     qty_readings;
} Linkedlist;



void	listInitialise      (Linkedlist *list);
void	listAddHead         (Linkedlist *list, float reading);
void	listAddTail         (Linkedlist *list, float reading);
void	listInsertNode      (Linkedlist *list, float reading, Node *currentnode);	
void	listDeleteNode      (Linkedlist *list, float reading, Node *currentnode);
void	listPrintNode       (Linkedlist *list);
void    listSetMax          (Linkedlist *list, float maxvalue);
void    listSetMin          (Linkedlist *list, float minvalue);

