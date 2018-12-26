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

/*#include "harness.h"*/
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q==NULL){   
        return NULL;
    }
    else{
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
        return q;
    }
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if(q!=NULL){
        list_ele_t *q_head_tmp;  
        while(q->head!=NULL){
            q_head_tmp = q->head;
            q->head = q->head->next;
            free(q_head_tmp->value);//First Free the strings
            free(q_head_tmp);//Second Free the elements
        }
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
    /* What should you do if the q is NULL? */
    if(q==NULL){return false;}
    list_ele_t *newh;
	char *s1;
	s1 = malloc((strlen(s)+1) * (sizeof(char)));
	strcpy(s1, s);
    newh = malloc(sizeof(list_ele_t));
    if(newh==NULL){return false;}
    /* Don't forget to allocate space for the string and copy it */
    newh->value = malloc((strlen(s)+1)*(sizeof(char)));//allocate space for the string
    if(newh->value==NULL){return false;}
    newh->value = s1;
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    q->size+=1;
    if(q_size(q) == 1){q->tail = q->head;}
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
    if(q==NULL){return false;}
    list_ele_t *newt;
   	char *s1;
	s1 = malloc((strlen(s)+1) * (sizeof(char) ));
    newt = malloc(sizeof(list_ele_t));
    if(newt==NULL){return false;}
    /* Don't forget to allocate space for the string and copy it */
    newt->value = malloc((strlen(s)+1)*(sizeof(char)));//allocate space for the string
    if(newt->value==NULL){return false;}
    strcpy(s1,s);
    newt->value = s1;
    /* What if either call to malloc returns NULL? */
    q->tail->next = newt;
    q->tail = newt;
    q->tail->next = NULL;
    q->size+=1;
    if(q_size(q) == 1){q->head = q->tail;}
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
    if(q==NULL||q->size==0){
        return false;
    }
    else{
        list_ele_t *list_tmp;
        list_tmp = q->head;
        q->head = q->head->next;
	    q->size -= 1;
        if (sp!=NULL){
            strncpy(sp,list_tmp->value,bufsize-1);
            sp[bufsize-1]='\0';
        }
        free(list_tmp->value);
        free(list_tmp);
        return true;
        }
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q!=NULL){ 
        return q->size;
    }
    else{
        return 0;
    }
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
    if(q!=NULL&&q->size>1){
        list_ele_t *current;
        list_ele_t *head_tmp;
        current=q->head;
        q->tail=q->head;
        while(current->next!=NULL){
            head_tmp = q->head;    
            q->head = current->next;
            current->next = current->next->next;
            q->head->next = head_tmp;  
        }
    }
}