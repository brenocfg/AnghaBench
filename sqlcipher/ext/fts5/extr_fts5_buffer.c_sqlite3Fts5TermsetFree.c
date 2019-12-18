#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_6__ {struct TYPE_6__* pNext; struct TYPE_6__** apHash; } ;
typedef  TYPE_1__ Fts5TermsetEntry ;
typedef  TYPE_1__ Fts5Termset ;

/* Variables and functions */
 size_t ArraySize (TYPE_1__**) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

void sqlite3Fts5TermsetFree(Fts5Termset *p){
  if( p ){
    u32 i;
    for(i=0; i<ArraySize(p->apHash); i++){
      Fts5TermsetEntry *pEntry = p->apHash[i];
      while( pEntry ){
        Fts5TermsetEntry *pDel = pEntry;
        pEntry = pEntry->pNext;
        sqlite3_free(pDel);
      }
    }
    sqlite3_free(p);
  }
}