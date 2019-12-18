#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* zCandidates; int /*<<< orphan*/  hIdx; int /*<<< orphan*/  pWrite; int /*<<< orphan*/  pTable; int /*<<< orphan*/  pStatement; int /*<<< orphan*/  pScan; int /*<<< orphan*/  dbv; int /*<<< orphan*/  dbm; } ;
typedef  TYPE_1__ sqlite3expert ;

/* Variables and functions */
 int /*<<< orphan*/  idxHashClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idxScanFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idxStatementFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idxTableFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idxWriteFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

void sqlite3_expert_destroy(sqlite3expert *p){
  if( p ){
    sqlite3_close(p->dbm);
    sqlite3_close(p->dbv);
    idxScanFree(p->pScan, 0);
    idxStatementFree(p->pStatement, 0);
    idxTableFree(p->pTable);
    idxWriteFree(p->pWrite);
    idxHashClear(&p->hIdx);
    sqlite3_free(p->zCandidates);
    sqlite3_free(p);
  }
}