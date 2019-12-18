#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nSample; scalar_t__ pnBytesFreed; TYPE_2__* aSample; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_10__ {struct TYPE_10__* p; } ;
typedef  TYPE_2__ IndexSample ;
typedef  TYPE_1__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,TYPE_2__*) ; 

void sqlite3DeleteIndexSamples(sqlite3 *db, Index *pIdx){
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  if( pIdx->aSample ){
    int j;
    for(j=0; j<pIdx->nSample; j++){
      IndexSample *p = &pIdx->aSample[j];
      sqlite3DbFree(db, p->p);
    }
    sqlite3DbFree(db, pIdx->aSample);
  }
  if( db && db->pnBytesFreed==0 ){
    pIdx->nSample = 0;
    pIdx->aSample = 0;
  }
#else
  UNUSED_PARAMETER(db);
  UNUSED_PARAMETER(pIdx);
#endif /* SQLITE_ENABLE_STAT3_OR_STAT4 */
}