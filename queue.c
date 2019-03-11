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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;

    q->head = NULL;
    q->rear = q->head;
    q->count = 0;

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL)
        return;

    list_ele_t *tmp_list;
    while (q->head != NULL) {
        tmp_list = q->head->next;
        free(q->head->value);
        free(q->head);
        q->head = tmp_list;
    }
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
    list_ele_t *newh;
    char *str;

    /* What should you do if the q is NULL? */
    if (q == NULL)
        return false;

    str = malloc((strlen(s) + 1) * sizeof(char));
    if (str == NULL)
        return false;

    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        free(str);
        return false;
    }

    if (q->count <= 1)
        q->rear = q->head;

    strcpy(str, s);
    newh->value = &str[0];
    newh->next = q->head;
    q->head = newh;
    q->count++;

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
    list_ele_t *newt;
    char *str;

    if (q == NULL)
        return false;

    if (q->head == NULL) {
        q_insert_head(q, s);
        return true;
    }
    str = malloc((strlen(s) + 1) * sizeof(char));
    if (str == NULL)
        return false;

    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) {
        free(str);
        return false;
    }

    if (q->count <= 1)
        q->rear = q->head;

    strcpy(str, s);
    q->rear->next = newt;
    newt->value = &str[0];
    newt->next = NULL;
    q->rear = newt;
    q->count++;

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
    list_ele_t *tmp_list;

    /* You need to fix up this code. */
    if ((q == NULL) || (q->head == NULL) || (q->head->value == NULL))
        return false;

    if (sp) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    bufsize -= 1;
    tmp_list = q->head->next;
    free(q->head->value);
    free(q->head);
    q->head = tmp_list;
    q->count -= 1;

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
        return 0;

    return q->count;
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
    list_ele_t *previous = NULL;
    list_ele_t *current, *preceding;

    if ((q == NULL) || (q->head == NULL) || (q->head->next == NULL) ||
        (q->rear == NULL))
        return;

    current = q->head;
    preceding = q->head->next;

    q->rear = current;
    while (preceding != NULL) {
        current->next = previous;
        previous = current;
        current = preceding;
        preceding = preceding->next;
    }
    current->next = previous;
    q->head = current;
    /* You need to write the code for this function */
}
