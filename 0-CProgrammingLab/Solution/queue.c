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
    /* What if malloc returned NULL? */
    if(q){
      q->head = NULL;
      q->tail = NULL;
      q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
  if(q){
    list_ele_t *cur = q->head;
    list_ele_t *next = NULL;
    while(cur){
      free(cur->value);
      next = cur->next;
      free(cur);
      cur = next;
    }
    /* Free queue structure */
    free(q);
  }
}


static int stringLength(char *s){
  int length = 0;
  while(s[length]!='\0'){
    length++;
  }
  return length+1;
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
    if(!q){
      return false;
    }
    
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if(!newh){
      return false;
    }
    char *copyString = malloc(sizeof(char)*stringLength(s));
    if(!copyString){
      free(newh);
      return false;
    }
    strcpy(copyString, s);
    newh->value = copyString;
    newh->next = q->head;
    q->head = newh;
    if(!q->tail){
      q->tail = newh;
    }
    ++q->size;
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
  if(!q){
    return false;
  }
    /* You need to write the complete code for this function */
  
  /* Remember: It should operate in O(1) time */
  list_ele_t *newtail = malloc(sizeof(list_ele_t));
  if(!newtail){
    return false;
  }
  char *copyString = malloc(sizeof(char)*stringLength(s));
  if(!copyString){
    free(newtail);
    return false;
  }
  strcpy(copyString, s);
  newtail->value = copyString;
  newtail ->next = NULL;
  if(q->tail){
    q->tail->next = newtail;
    q->tail = newtail;
  }else{
    q->head = newtail;
    q->tail = newtail;
  }
  ++q->size;
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
  if(!q||!q->head){
    return false;
  }
  list_ele_t *oldhead = q->head;
  list_ele_t *newhead = q->head->next;
  if(sp){
    int i;
    for(i=0; i<bufsize-1 &&*(oldhead->value+i)!='\0';++i){
      *(sp+i) = *(oldhead->value+i);
    }
    *(sp+i) = '\0';
  }
  free(oldhead->value);
  free(oldhead);
  q->head = newhead;
  --q->size;
  return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
  if(!q||!q->head){
    return 0;
  }else{
    return q->size;
  }
  /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
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
  if(q&&q->head){
    list_ele_t *oldhead = q->head;
    //list_ele_t *oldtail = q->tail;
    list_ele_t *cur = q->head;
    list_ele_t *prev = NULL;
    list_ele_t *next = NULL;
    while(cur){
      next = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next;
    }
    q->tail = oldhead;
    q->head = prev;
  }

}

