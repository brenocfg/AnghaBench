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
struct TYPE_3__ {char const* data; struct TYPE_3__** from; struct TYPE_3__* next; } ;
typedef  TYPE_1__ x1node ;
struct s_x1 {int size; int count; TYPE_1__** ht; TYPE_1__* tbl; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int strhash (char const*) ; 
 struct s_x1* x1a ; 

int Strsafe_insert(const char *data)
{
  x1node *np;
  unsigned h;
  unsigned ph;

  if( x1a==0 ) return 0;
  ph = strhash(data);
  h = ph & (x1a->size-1);
  np = x1a->ht[h];
  while( np ){
    if( strcmp(np->data,data)==0 ){
      /* An existing entry with the same key is found. */
      /* Fail because overwrite is not allows. */
      return 0;
    }
    np = np->next;
  }
  if( x1a->count>=x1a->size ){
    /* Need to make the hash table bigger */
    int i,arrSize;
    struct s_x1 array;
    array.size = arrSize = x1a->size*2;
    array.count = x1a->count;
    array.tbl = (x1node*)calloc(arrSize, sizeof(x1node) + sizeof(x1node*));
    if( array.tbl==0 ) return 0;  /* Fail due to malloc failure */
    array.ht = (x1node**)&(array.tbl[arrSize]);
    for(i=0; i<arrSize; i++) array.ht[i] = 0;
    for(i=0; i<x1a->count; i++){
      x1node *oldnp, *newnp;
      oldnp = &(x1a->tbl[i]);
      h = strhash(oldnp->data) & (arrSize-1);
      newnp = &(array.tbl[i]);
      if( array.ht[h] ) array.ht[h]->from = &(newnp->next);
      newnp->next = array.ht[h];
      newnp->data = oldnp->data;
      newnp->from = &(array.ht[h]);
      array.ht[h] = newnp;
    }
    free(x1a->tbl);
    *x1a = array;
  }
  /* Insert the new data */
  h = ph & (x1a->size-1);
  np = &(x1a->tbl[x1a->count++]);
  np->data = data;
  if( x1a->ht[h] ) x1a->ht[h]->from = &(np->next);
  np->next = x1a->ht[h];
  x1a->ht[h] = np;
  np->from = &(x1a->ht[h]);
  return 1;
}