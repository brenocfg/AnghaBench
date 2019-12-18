#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t iPKey; int /*<<< orphan*/  zName; TYPE_1__* aCol; } ;
typedef  TYPE_2__ Table ;
struct TYPE_9__ {int /*<<< orphan*/  db; } ;
struct TYPE_7__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  P4_DYNAMIC ; 
 int /*<<< orphan*/  P5_ConstraintUnique ; 
 int SQLITE_CONSTRAINT_PRIMARYKEY ; 
 int SQLITE_CONSTRAINT_ROWID ; 
 int /*<<< orphan*/  sqlite3HaltConstraint (TYPE_3__*,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* sqlite3MPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

void sqlite3RowidConstraint(
  Parse *pParse,    /* Parsing context */
  int onError,      /* Conflict resolution algorithm */
  Table *pTab       /* The table with the non-unique rowid */ 
){
  char *zMsg;
  int rc;
  if( pTab->iPKey>=0 ){
    zMsg = sqlite3MPrintf(pParse->db, "%s.%s", pTab->zName,
                          pTab->aCol[pTab->iPKey].zName);
    rc = SQLITE_CONSTRAINT_PRIMARYKEY;
  }else{
    zMsg = sqlite3MPrintf(pParse->db, "%s.rowid", pTab->zName);
    rc = SQLITE_CONSTRAINT_ROWID;
  }
  sqlite3HaltConstraint(pParse, rc, onError, zMsg, P4_DYNAMIC,
                        P5_ConstraintUnique);
}