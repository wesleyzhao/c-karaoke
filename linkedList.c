/**************************************************\
 * Filename:     linkedList.c                     *
 * Author:       Sue Bogar                        *
 * Edited By:    Katherine Gibson (gibsonk@seas)  *
 * Edited By:    Wesley Zhao (weszhao@seas)  *
 * Date Written: 11/17/98                         *
 * EMail: bogar@cs.umbc.edu                       *
 *                                                *
 * Description:  This file contains the functions *
 * necessary to work with a linked list.          *
\**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "karaoke.h"

#include "linkedList.h"

/********************************************
 ** Function: CreateNode
 ** Input:    none
 ** Output:  memory for a node is malloced
 **           and a pointer (nodePtr) to the 
 **           memory is returned to the user
 ********************************************/ 
SINGER tempSinger;

NODEPTR CreateNode (void)
{
  NODEPTR newNode;

  /* get the space needed for the node */
  newNode = (NODEPTR) malloc(sizeof(NODE));

  if (newNode == NULL)
  {
    fprintf(stderr, "Out of memory in CreateNode function\n");
    exit(-1);
  }

  /* Initialize the members */
  newNode->data = tempSinger;
  newNode->next = NULL;

  return newNode;
}


/********************************************
 ** Function: SetData
 ** Input:    a pointer to a node (NODEPTR), and
 **           the value to be placed into the node
 ** Output:   none
 *********************************************/
void SetData (NODEPTR temp, SINGER value)
{
  temp->data = value;
} 


/********************************************
 * Function: Insert
 * Input:    a pointer to a pointer to the head of the 
 *             linked list (headPtr)
 *           a pointer to the node (NODEPTR) to be 
 *             inserted
 * Output:   none
 ********************************************/ 
void Insert (NODEPTR* headPtr, NODEPTR temp)
{
  NODEPTR prev, curr;

  /* if list is empty, temp becomes first node */
  if ( *headPtr == NULL )
  {
    *headPtr = temp;
  }
  else
  {
    prev = NULL;
    curr = *headPtr;

    /* traverse the list until the end */
    while (curr != NULL)
    {
      prev = curr;
      curr = curr -> next;
    }
  
    /* insert temp at the end */
    prev -> next = temp;
  }
}


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
SINGER Delete (NODEPTR* headPtr, SINGER target)
{
  SINGER value;
  NODEPTR prev, curr;

  if (*headPtr == NULL)
  {
    printf ("Can't delete from an empty list\n");
    return value;
  }
  /* if node to delete is first in list, move head */
  else if (strcmp(target.name,((*headPtr)->data).name) == 0)
  {
    curr = *headPtr;
    value = (*headPtr)->data;
    *headPtr = (*headPtr)->next;
    free (curr);
    return value;
  }
  /* otherwise, traverse the list until 
     the end or the target value is found */
  else
  {
    prev = *headPtr;
    curr = (*headPtr)->next;

    while (curr != NULL && (strcmp(target.name, (curr->data).name) != 0))
    {
      prev = curr;
      curr = curr -> next;
    }
    /* found the target, not the end of the list */
    if(curr != NULL)
    {
      /* delete the node that contains target value */
      prev->next = curr->next;
      value = curr->data;
      free(curr);
      return value;
    }
    else
    {
      printf("%s was not in the list\n", target.name);
      return (tempSinger);
    }
  }      
}

NODEPTR FindNode (NODEPTR* headPtr, char *singerName)
{
  NODEPTR prev, curr;

  if (*headPtr == NULL)
  {
    printf ("Can't find from an empty list\n");
    return *headPtr;
  }
  /* if node to find is first in list, move head */
  else if (strcmp(singerName,((*headPtr)->data).name) == 0)
  {
    return *headPtr;
  }
  /* otherwise, traverse the list until 
     the end or the target value is found */
  else
  {
    prev = *headPtr;
    curr = (*headPtr)->next;

    while (curr != NULL && (strcmp(singerName, (curr->data).name) != 0))
    {
      prev = curr;
      curr = curr -> next;
    }
    /* found the target, not the end of the list */
    if(curr != NULL)
    {
      /* delete the node that contains target value */
      return curr;
    }
    else
    {
      printf("%s was not in the list\n", singerName);
      return (NULL);
    }
  }      
}


void DestroyList(NODEPTR *headPtr){
  NODEPTR prev, curr, temp;

  if (*headPtr == NULL)
  {
    printf ("Can't delete from an empty list\n");
  }
  /* otherwise, traverse the list until 
     the end or the target value is found */
  curr = (*headPtr);
  while (curr != NULL){
    temp = curr;
    curr = curr->next;
    free(temp);
  }
  free(*headPtr);
  
}

void Move(NODEPTR target, NODEPTR* fromHeadPtr, NODEPTR* toHeadPtr){
  NODEPTR prev, curr;

  if (*fromHeadPtr == NULL)
  {
    printf ("Can't traverse from an empty list\n");
  }

  /* if node to find is first in list, move head */
  else if (strcmp((target->data).name,((*fromHeadPtr)->data).name) == 0)
  {
    curr = *fromHeadPtr;
    *fromHeadPtr = (*fromHeadPtr)->next;
  }
  /* otherwise, traverse the list until 
     the end or the target value is found */
  else
  {
    prev = *fromHeadPtr;
    curr = (*fromHeadPtr)->next;

    while (curr != NULL && (strcmp((target->data).name, (curr->data).name) != 0))
    {
      prev = curr;
      curr = curr -> next;
    }
    /* found the target, not the end of the list */
    if(curr != NULL)
    {
      /* shift the node that contains target value */
      prev->next = curr->next;
      curr->next = NULL;
    }
    else
    {
      printf("%s was not in the list\n", (target->data).name);
    }
  }      
  Insert(toHeadPtr, curr);
}


/********************************************
 * Function: PrintList
 * Input:    a pointer to the head of the list
 * Ouput:    none
 ********************************************/ 
void PrintList (NODEPTR head)
{
  NODEPTR curr;

  if (head == NULL)
  {
    printf ("The list is empty\n");
  }
  else
  {
      
    curr = head;

    /* traverse the list until the end */
    while (curr != NULL)
    {
      /* print the current data item */
      printf("%s ", (curr -> data).name);
      /* printSinger(curr -> data); */

      /* move to the next node */
      curr = curr -> next;
    }
    printf ("\n");
  }   
}
