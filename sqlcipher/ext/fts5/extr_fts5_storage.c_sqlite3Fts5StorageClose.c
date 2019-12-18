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
struct TYPE_4__ {int /*<<< orphan*/ * aStmt; } ;
typedef  TYPE_1__ Fts5Storage ;

/* Variables and functions */
 int ArraySize (int /*<<< orphan*/ *) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

int sqlite3Fts5StorageClose(Fts5Storage *p){
  int rc = SQLITE_OK;
  if( p ){
    int i;

    /* Finalize all SQL statements */
    for(i=0; i<ArraySize(p->aStmt); i++){
      sqlite3_finalize(p->aStmt[i]);
    }

    sqlite3_free(p);
  }
  return rc;
}