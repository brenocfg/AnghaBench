#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_3__ {scalar_t__* aStmt; } ;
typedef  TYPE_1__ Fts5Storage ;

/* Variables and functions */
 int FTS5_STMT_LOOKUP ; 
 int FTS5_STMT_SCAN_ASC ; 
 int FTS5_STMT_SCAN_DESC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 

void sqlite3Fts5StorageStmtRelease(
  Fts5Storage *p, 
  int eStmt, 
  sqlite3_stmt *pStmt
){
  assert( eStmt==FTS5_STMT_SCAN_ASC
       || eStmt==FTS5_STMT_SCAN_DESC
       || eStmt==FTS5_STMT_LOOKUP
  );
  if( p->aStmt[eStmt]==0 ){
    sqlite3_reset(pStmt);
    p->aStmt[eStmt] = pStmt;
  }else{
    sqlite3_finalize(pStmt);
  }
}