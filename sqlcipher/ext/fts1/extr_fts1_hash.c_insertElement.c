#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _fts1ht {TYPE_1__* chain; int /*<<< orphan*/  count; } ;
struct TYPE_5__ {struct TYPE_5__* prev; struct TYPE_5__* next; } ;
typedef  TYPE_1__ fts1HashElem ;
struct TYPE_6__ {TYPE_1__* first; } ;
typedef  TYPE_2__ fts1Hash ;

/* Variables and functions */

__attribute__((used)) static void insertElement(
  fts1Hash *pH,            /* The complete hash table */
  struct _fts1ht *pEntry,  /* The entry into which pNew is inserted */
  fts1HashElem *pNew       /* The element to be inserted */
){
  fts1HashElem *pHead;     /* First element already in pEntry */
  pHead = pEntry->chain;
  if( pHead ){
    pNew->next = pHead;
    pNew->prev = pHead->prev;
    if( pHead->prev ){ pHead->prev->next = pNew; }
    else             { pH->first = pNew; }
    pHead->prev = pNew;
  }else{
    pNew->next = pH->first;
    if( pH->first ){ pH->first->prev = pNew; }
    pNew->prev = 0;
    pH->first = pNew;
  }
  pEntry->count++;
  pEntry->chain = pNew;
}