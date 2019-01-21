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
#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    if (q!=NULL)
    {
        /* What if malloc returned NULL? */
        q->head = NULL;
        q->list_size = 0;
        return q;
    }
    return NULL;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    if(q!=NULL)
    {
        while(q->head->next!=NULL)
        {
            free(q->head->value);
            q->head = q->head->next; 
        }
        int i=0;
        while(i<q->list_size-1)
        {
            free(q->address_list[i]);
            i++;
        }
        free(q->head->value);
        free(q->head);
        free(q);
    }
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
    /* What should you do if the q is NULL? */
    if (NULL==q)
    return false;    
    newh = malloc(sizeof(list_ele_t));
    int char_block =0;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (q!=NULL && newh != NULL)
    {
	newh->next = q->head;
    	q->head = newh;
        int temp_pos;
	newh->value = malloc(sizeof(char*)*strlen(s));
	for (char_block=0; char_block<strlen(s);char_block++)
	    newh->value[char_block]=s[char_block];
	newh->value[char_block]=0;
	for (temp_pos=q->list_size; temp_pos>0;temp_pos--)
	    q->address_list[temp_pos]=q->address_list[temp_pos-1];
	q->address_list[0] = q->head;
	q->list_size = q->list_size +1;
    	return true;
    }
    else
	return false;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Arguments points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if(NULL==q)
    return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    int char_block=0;
    if(newh!=NULL)
    {
        newh->value = malloc(sizeof(char*)*strlen(s));  
	newh->next = NULL;
        for (char_block=0; char_block<strlen(s);char_block++)
            newh->value[char_block]=s[char_block];
        newh->value[char_block]=0;
        if(q->list_size>0)
        {
    	    q->address_list[q->list_size-1]->next = newh;
    	    q->address_list[q->list_size]= newh;
        }
        else
        {
	    q->head = newh;
	    q->address_list[0] = newh;
        }
        q->list_size = q->list_size+1;
        return true;
    }
    return false;
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
    list_ele_t *oldh;
    int sp_i=0;
    int arr_pos;
    oldh = malloc(sizeof(list_ele_t));
    if (q!=NULL)
    {
    	if(sp!=NULL)
    	{
    	    for(sp_i=0;sp_i<bufsize-1;sp_i++)
	        sp[sp_i]=q->head->value[sp_i];
    	}
        oldh = q->head;
        q->head = q->head->next;
        free(oldh);
        for(arr_pos = 0; arr_pos<q->list_size-1;arr_pos++)
            q->address_list[arr_pos] = q->address_list[arr_pos+1];
        q->list_size = q->list_size-1;
        return true;
    }
    return false;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->list_size;
}

/*
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
 /* You need to write the code for this function */
    int i=0,j=q->list_size;
    for (i=0;i<q->list_size;i++)
    {
	if(i<j-1)
	{
            q->last_element=q->address_list[i];
	    q->address_list[i] = q->address_list[j-1];
            q->address_list[j-1]= q->last_element;	
	    j = j-1;
	}
    }
    q->head = q->address_list[0];
    list_ele_t *temp = q->head;
    for(i=0;i<q->list_size-1;i++)
    {
        temp->next = q->address_list[i+1];
	temp = temp->next;  
    }
    temp->next = NULL;    
}

