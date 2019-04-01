/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
	if (q == NULL)
	{
		printf("ERROR: malloc returned NULL, q_new returning NULL.\n");
		return NULL;
	}
	q->head = q->tail = NULL;
	q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
	if (q->size > 0)
	{
		list_ele_t *curr = q->head,
				   *next = NULL;
		while (curr != NULL) // If curr is NULL then it is at the last node.
		{
			next = curr->next;	// Get the next node.
			printf("%s\n", curr->value); // For testing.
			free(curr->value);	// Free the string.
			free(curr);			// Free the node itself.		
			curr = next;		// Onto the next node.
		}
	}
	if (q != NULL)
		free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
	/* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
	if (q == NULL)
	{
		printf("ERROR: (0) q is null, q_insert_head returning false.\n");
		return false;
	}
	
    list_ele_t *newh; // Create the new node.
	newh = malloc(sizeof(list_ele_t));
	if (newh == NULL)
	{
		printf("ERROR: (1) malloc returned NULL, q_insert_head returning false.\n");
		return false;
	}

	newh->value = strdup(s); // strdup uses malloc, copies strings.
	if (newh->value == NULL)
	{
		printf("ERROR: (2) malloc returned NULL, q_insert_head returning false.\n");
		return false;
	}
	
	newh->next = q->head; // Old head is newh's next.
    q->head = newh;		  // The head now points to the most recent node.
	if (q->size == 0)	  // If empty, tail and head point to the same place.
		q->tail = newh;
	q->size++;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
	if (q == NULL)
	{
		printf("ERROR: (0) q is null, q_insert_tail returning false.\n");
		return false;
	}
	
	list_ele_t *newt;
	newt = malloc(sizeof(list_ele_t));
	if (newt == NULL)
	{
		printf("ERROR: (1) malloc returned NULL, q_insert_tail returning false.\n");
		return false;
	}

	newt->value = strdup(s);
	if (newt->value == NULL)
	{
		printf("ERROR: (2) malloc returned NULL, q_insert_tail returning false.\n");
		return false;
	}

	newt->next = NULL;    // Last node will always point to NULL.
	q->tail->next = newt; // Update last node to be 2nd to last node, now point to newt.
	q->tail = newt;		  // Tail now points to the last node.
	if (q->size == 0)	  // If empty, tail and head point to the same place.
		q->head = newt;
	q->size++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
	if (q->size == 0 || q == NULL)
	{
		printf("ERROR: (0) Invalid queue, remove_head returning false.\n");
		return false;
	}

	list_ele_t *temp = q->head;
    q->head = q->head->next;	 // Move head to next node.
	printf("%s\n", temp->value); // For testing purposes.
	sp = (char*)malloc(bufsize);
	if (sp == NULL)
	{
		printf("ERROR: (1) malloc returned NULL, q_remove_head returning false.\n");
		return false;
	}

	if (temp->value != NULL)
		strcpy(sp, temp->value);

	free(temp->value); // Delete everything.
	free(temp);
	free(sp);		   // I'm not sure what the purpose of sp is if it just gets deleted in the end anyways.
	q->size--;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
	if (q == NULL)
	{
		printf("ERROR: queue is NULL, returning zero.\n");
		return 0;
	}
	return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
	if (q->size <= 1 || q == NULL)
	{
		printf("ERROR: queue cannot be reversed.\n");
		return;
	}
	list_ele_t *curr, 
			   *prev = NULL, // The previous node (towards the tail) of curr.
			   *next = NULL; // Next node (towards the end) of curr.
	curr = q->head;
	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev; // Point the next node to the previous node.
		prev = curr;	   // Move previous up one node (towards end).
		curr = next;	   // Move current node up one node (towards end).
	}
	q->tail = q->head;	   // Head is now the last node, reflect the change.
	q->head = prev;		   // At the end of the while loop prev will be first in the queue.
}

/* For testing purposes only */
/*int main()
{
	queue_t *a = q_new();	
	char *b = "dolphin";
	char *c = "bear";
	char *d = "gerbil";
	char *e = "meerkat";
	char *f = "bear";
	q_insert_head(a, b);
	q_insert_head(a, c);
	q_insert_head(a, d);
	q_insert_tail(a, e);
	q_insert_tail(a, f);
	q_reverse(a);
	printf("%d\n", q_size(a));
	char *x, *y, *z, *r, *q;
	q_remove_head(a, x, 100);
	q_remove_head(a, y, 100);
	q_remove_head(a, z, 100);
	q_remove_head(a, r, 100);
	q_remove_head(a, q, 100);

	//free(x);
	//free(y); free(z); free(r); free(q);

	q_free(a);

	//printf("%d\n", q_size(a));
}*/
