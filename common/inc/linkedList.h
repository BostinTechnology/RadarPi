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
	void 	*data;
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
void	listAddHead		(Linkedlist *list, void *data);
void	listAddTail		(Linkedlist *list, void *data);
void	listInsertNode	(Linkedlist *list, void* data, Node *currentnode);	
void	listDeleteNode	(Linkedlist *list, void *data, Node *currentnode);
void	listPrintNode	(Linkedlist *list);
