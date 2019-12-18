#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__** from; struct TYPE_3__* next; struct state* data; struct config* key; } ;
typedef  TYPE_1__ x3node ;
struct state {int dummy; } ;
struct s_x3 {int size; int count; TYPE_1__** ht; TYPE_1__* tbl; } ;
struct config {int dummy; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ statecmp (struct config*,struct config*) ; 
 int statehash (struct config*) ; 
 struct s_x3* x3a ; 

int State_insert(struct state *data, struct config *key)
{
  x3node *np;
  unsigned h;
  unsigned ph;

  if( x3a==0 ) return 0;
  ph = statehash(key);
  h = ph & (x3a->size-1);
  np = x3a->ht[h];
  while( np ){
    if( statecmp(np->key,key)==0 ){
      /* An existing entry with the same key is found. */
      /* Fail because overwrite is not allows. */
      return 0;
    }
    np = np->next;
  }
  if( x3a->count>=x3a->size ){
    /* Need to make the hash table bigger */
    int i,arrSize;
    struct s_x3 array;
    array.size = arrSize = x3a->size*2;
    array.count = x3a->count;
    array.tbl = (x3node*)calloc(arrSize, sizeof(x3node) + sizeof(x3node*));
    if( array.tbl==0 ) return 0;  /* Fail due to malloc failure */
    array.ht = (x3node**)&(array.tbl[arrSize]);
    for(i=0; i<arrSize; i++) array.ht[i] = 0;
    for(i=0; i<x3a->count; i++){
      x3node *oldnp, *newnp;
      oldnp = &(x3a->tbl[i]);
      h = statehash(oldnp->key) & (arrSize-1);
      newnp = &(array.tbl[i]);
      if( array.ht[h] ) array.ht[h]->from = &(newnp->next);
      newnp->next = array.ht[h];
      newnp->key = oldnp->key;
      newnp->data = oldnp->data;
      newnp->from = &(array.ht[h]);
      array.ht[h] = newnp;
    }
    free(x3a->tbl);
    *x3a = array;
  }
  /* Insert the new data */
  h = ph & (x3a->size-1);
  np = &(x3a->tbl[x3a->count++]);
  np->key = key;
  np->data = data;
  if( x3a->ht[h] ) x3a->ht[h]->from = &(np->next);
  np->next = x3a->ht[h];
  x3a->ht[h] = np;
  np->from = &(x3a->ht[h]);
  return 1;
}