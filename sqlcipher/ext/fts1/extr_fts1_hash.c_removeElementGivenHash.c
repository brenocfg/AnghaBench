#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct _fts1ht {scalar_t__ count; TYPE_2__* chain; } ;
struct TYPE_10__ {struct TYPE_10__* pKey; struct TYPE_10__* next; TYPE_1__* prev; } ;
typedef  TYPE_2__ fts1HashElem ;
struct TYPE_11__ {scalar_t__ count; scalar_t__ first; int /*<<< orphan*/  (* xFree ) (TYPE_2__*) ;scalar_t__ copyKey; struct _fts1ht* ht; } ;
typedef  TYPE_3__ fts1Hash ;
struct TYPE_9__ {TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts1HashClear (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static void removeElementGivenHash(
  fts1Hash *pH,         /* The pH containing "elem" */
  fts1HashElem* elem,   /* The element to be removed from the pH */
  int h                 /* Hash value for the element */
){
  struct _fts1ht *pEntry;
  if( elem->prev ){
    elem->prev->next = elem->next; 
  }else{
    pH->first = elem->next;
  }
  if( elem->next ){
    elem->next->prev = elem->prev;
  }
  pEntry = &pH->ht[h];
  if( pEntry->chain==elem ){
    pEntry->chain = elem->next;
  }
  pEntry->count--;
  if( pEntry->count<=0 ){
    pEntry->chain = 0;
  }
  if( pH->copyKey && elem->pKey ){
    pH->xFree(elem->pKey);
  }
  pH->xFree( elem );
  pH->count--;
  if( pH->count<=0 ){
    assert( pH->first==0 );
    assert( pH->count==0 );
    fts1HashClear(pH);
  }
}