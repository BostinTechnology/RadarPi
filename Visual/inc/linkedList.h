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
	int 	reading;
	struct	_node *prevnode;
	struct	_node *nextnode;
} Node;

typedef struct _linkedlist 
{
	Node *listHead;
	Node *listTail;
	Node *currentNode;
} Linkedlist;



void	listInitialise	(Linkedlist *list);
void	listAddHead		(Linkedlist *list, int reading);
void	listAddTail		(Linkedlist *list, int reading);
void	listInsertNode	(Linkedlist *list, int reading, Node *currentnode);	
void	listDeleteNode	(Linkedlist *list, int reading, Node *currentnode);
void	listPrintNode	(Linkedlist *list);
