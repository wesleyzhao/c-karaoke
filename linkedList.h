/**************************************************\
 * Filename:     linkedList.h                     *
 * Author:       Sue Bogar                        *
 * Edited By:    Katherine Gibson (gibsonk@seas)  *
 * Edited By:    Wesley Zhao (weszhao@seas)  *
 * Date Written: 11/17/98                         *
 * EMail: bogar@cs.umbc.edu                       *
 *                                                *
* This file contains the structure definition of  *
* a node, and typedefs of the types NODE and      *
* NODEPTR.  It also contains the function         *
* prototypes for the functions in linkedlist.c.   *
\**************************************************/


/* NODEPTR is defined as an alias for
   "struct node *" so it can be used within
   the structure before it is completely defined */
typedef struct node * NODEPTR;

typedef struct node {
  SINGER data;
  NODEPTR next;
} NODE;


/********************************************
 ** Function: CreateNode
 ** Input:    none
 ** Output:  memory for a node is malloced
 **           and a pointer (nodePtr) to the 
 **           memory is returned to the user
 ********************************************/ 
NODEPTR CreateNode (void);


/********************************************
 ** Function: SetData
 ** Input:    a pointer to a node (NODEPTR), and
 **           the value to be placed into the node
 ** Output:   none
 *********************************************/
void SetData (NODEPTR temp, SINGER value);


/********************************************
 * Function: Insert
 * Input:    a pointer to a pointer to the head of the 
 *             linked list (headPtr)
 *           a pointer to the node (NODEPTR) to be 
 *             inserted
 * Output:   none
 ********************************************/ 
void Insert (NODEPTR* headPtr, NODEPTR temp);


/********************************************
 * Function: Delete
 * Input:    a pointer to a pointer to the head 
 *             (headPtr) of the linked list
 *           an integer (target) containing the value 
 *             of the data in the node to be deleted
 * Output:   integer expressing operation success
 *            - if found, value found in DELETED node is returned
 *            - if not found, error is printed and -1 is returned
 ********************************************/ 
SINGER Delete (NODEPTR* headPtr, SINGER target);


/********************************************
 * Function: PrintList
 * Input:    a pointer to the head of the list
 * Ouput:    none
 ********************************************/ 
void PrintList (NODEPTR head);

void Move(NODEPTR target, NODEPTR* fromHeadPtr, NODEPTR* toHeadPtr);

void DestroyList(NODEPTR *headPtr);
