#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct RowSetChunk {struct RowSetChunk* pNextChunk; } ;
struct TYPE_2__ {int /*<<< orphan*/  rsFlags; scalar_t__ pForest; scalar_t__ pLast; scalar_t__ pEntry; scalar_t__ nFresh; struct RowSetChunk* pChunk; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ RowSet ;

/* Variables and functions */
 int /*<<< orphan*/  ROWSET_SORTED ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ ,struct RowSetChunk*) ; 

void sqlite3RowSetClear(void *pArg){
  RowSet *p = (RowSet*)pArg;
  struct RowSetChunk *pChunk, *pNextChunk;
  for(pChunk=p->pChunk; pChunk; pChunk = pNextChunk){
    pNextChunk = pChunk->pNextChunk;
    sqlite3DbFree(p->db, pChunk);
  }
  p->pChunk = 0;
  p->nFresh = 0;
  p->pEntry = 0;
  p->pLast = 0;
  p->pForest = 0;
  p->rsFlags = ROWSET_SORTED;
}