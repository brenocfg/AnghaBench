#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* pKey; struct TYPE_7__* next; } ;
typedef  TYPE_1__ fts1HashElem ;
struct TYPE_8__ {scalar_t__ count; int /*<<< orphan*/  (* xFree ) (TYPE_1__*) ;scalar_t__ copyKey; scalar_t__ htsize; TYPE_1__* ht; TYPE_1__* first; } ;
typedef  TYPE_2__ fts1Hash ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*) ; 

void sqlite3Fts1HashClear(fts1Hash *pH){
  fts1HashElem *elem;         /* For looping over all elements of the table */

  assert( pH!=0 );
  elem = pH->first;
  pH->first = 0;
  if( pH->ht ) pH->xFree(pH->ht);
  pH->ht = 0;
  pH->htsize = 0;
  while( elem ){
    fts1HashElem *next_elem = elem->next;
    if( pH->copyKey && elem->pKey ){
      pH->xFree(elem->pKey);
    }
    pH->xFree(elem);
    elem = next_elem;
  }
  pH->count = 0;
}