#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct RowSetEntry {int dummy; } ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {scalar_t__ iBatch; int /*<<< orphan*/  rsFlags; scalar_t__ nFresh; struct RowSetEntry* pFresh; scalar_t__ pForest; scalar_t__ pLast; scalar_t__ pEntry; int /*<<< orphan*/ * db; scalar_t__ pChunk; } ;
typedef  TYPE_1__ RowSet ;

/* Variables and functions */
 int ROUND8 (int) ; 
 int /*<<< orphan*/  ROWSET_SORTED ; 
 TYPE_1__* sqlite3DbMallocRawNN (int /*<<< orphan*/ *,int) ; 
 int sqlite3DbMallocSize (int /*<<< orphan*/ *,TYPE_1__*) ; 

RowSet *sqlite3RowSetInit(sqlite3 *db){
  RowSet *p = sqlite3DbMallocRawNN(db, sizeof(*p));
  if( p ){
    int N = sqlite3DbMallocSize(db, p);
    p->pChunk = 0;
    p->db = db;
    p->pEntry = 0;
    p->pLast = 0;
    p->pForest = 0;
    p->pFresh = (struct RowSetEntry*)(ROUND8(sizeof(*p)) + (char*)p);
    p->nFresh = (u16)((N - ROUND8(sizeof(*p)))/sizeof(struct RowSetEntry));
    p->rsFlags = ROWSET_SORTED;
    p->iBatch = 0;
  }
  return p;
}