#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nDb; } ;
typedef  TYPE_1__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_7__ {TYPE_1__* db; } ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  OP_AutoCommit ; 
 int /*<<< orphan*/  OP_Transaction ; 
 int /*<<< orphan*/  SQLITE_TRANSACTION ; 
 int TK_DEFERRED ; 
 int TK_EXCLUSIVE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3AuthCheck (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeUsesBtree (int /*<<< orphan*/ *,int) ; 

void sqlite3BeginTransaction(Parse *pParse, int type){
  sqlite3 *db;
  Vdbe *v;
  int i;

  assert( pParse!=0 );
  db = pParse->db;
  assert( db!=0 );
  if( sqlite3AuthCheck(pParse, SQLITE_TRANSACTION, "BEGIN", 0, 0) ){
    return;
  }
  v = sqlite3GetVdbe(pParse);
  if( !v ) return;
  if( type!=TK_DEFERRED ){
    for(i=0; i<db->nDb; i++){
      sqlite3VdbeAddOp2(v, OP_Transaction, i, (type==TK_EXCLUSIVE)+1);
      sqlite3VdbeUsesBtree(v, i);
    }
  }
  sqlite3VdbeAddOp0(v, OP_AutoCommit);
}