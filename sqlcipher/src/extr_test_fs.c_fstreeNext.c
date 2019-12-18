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
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_3__ {scalar_t__ pStmt; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ FstreeCsr ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  fstreeCloseFd (TYPE_1__*) ; 
 int /*<<< orphan*/  open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (scalar_t__,int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (scalar_t__) ; 
 int sqlite3_step (scalar_t__) ; 

__attribute__((used)) static int fstreeNext(sqlite3_vtab_cursor *cur){
  FstreeCsr *pCsr = (FstreeCsr*)cur;
  int rc;

  fstreeCloseFd(pCsr);
  rc = sqlite3_step(pCsr->pStmt);
  if( rc!=SQLITE_ROW ){
    rc = sqlite3_finalize(pCsr->pStmt);
    pCsr->pStmt = 0;
  }else{
    rc = SQLITE_OK;
    pCsr->fd = open((const char*)sqlite3_column_text(pCsr->pStmt, 0), O_RDONLY);
  }

  return rc;
}