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
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_5__ {scalar_t__ db; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  OP_AutoCommit ; 
 int /*<<< orphan*/  SQLITE_TRANSACTION ; 
 int TK_COMMIT ; 
 int TK_END ; 
 int TK_ROLLBACK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3AuthCheck (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

void sqlite3EndTransaction(Parse *pParse, int eType){
  Vdbe *v;
  int isRollback;

  assert( pParse!=0 );
  assert( pParse->db!=0 );
  assert( eType==TK_COMMIT || eType==TK_END || eType==TK_ROLLBACK );
  isRollback = eType==TK_ROLLBACK;
  if( sqlite3AuthCheck(pParse, SQLITE_TRANSACTION, 
       isRollback ? "ROLLBACK" : "COMMIT", 0, 0) ){
    return;
  }
  v = sqlite3GetVdbe(pParse);
  if( v ){
    sqlite3VdbeAddOp2(v, OP_AutoCommit, 1, isRollback);
  }
}