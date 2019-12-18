#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pStmt; } ;
struct TYPE_5__ {scalar_t__ pSql; scalar_t__ pArray; TYPE_2__* pPreStmt; int /*<<< orphan*/  pDb; } ;
typedef  TYPE_1__ DbEvalContext ;

/* Variables and functions */
 int /*<<< orphan*/  Tcl_DecrRefCount (scalar_t__) ; 
 int /*<<< orphan*/  dbReleaseColumnNames (TYPE_1__*) ; 
 int /*<<< orphan*/  dbReleaseStmt (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dbEvalFinalize(DbEvalContext *p){
  if( p->pPreStmt ){
    sqlite3_reset(p->pPreStmt->pStmt);
    dbReleaseStmt(p->pDb, p->pPreStmt, 0);
    p->pPreStmt = 0;
  }
  if( p->pArray ){
    Tcl_DecrRefCount(p->pArray);
    p->pArray = 0;
  }
  Tcl_DecrRefCount(p->pSql);
  dbReleaseColumnNames(p);
}