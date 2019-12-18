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
struct TYPE_5__ {struct TYPE_5__* pKey; struct TYPE_5__* next; } ;
typedef  TYPE_1__ fts2HashElem ;
struct TYPE_6__ {scalar_t__ count; scalar_t__ copyKey; scalar_t__ htsize; TYPE_1__* ht; TYPE_1__* first; } ;
typedef  TYPE_2__ fts2Hash ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts2HashFree (TYPE_1__*) ; 

void sqlite3Fts2HashClear(fts2Hash *pH){
  fts2HashElem *elem;         /* For looping over all elements of the table */

  assert( pH!=0 );
  elem = pH->first;
  pH->first = 0;
  fts2HashFree(pH->ht);
  pH->ht = 0;
  pH->htsize = 0;
  while( elem ){
    fts2HashElem *next_elem = elem->next;
    if( pH->copyKey && elem->pKey ){
      fts2HashFree(elem->pKey);
    }
    fts2HashFree(elem);
    elem = next_elem;
  }
  pH->count = 0;
}