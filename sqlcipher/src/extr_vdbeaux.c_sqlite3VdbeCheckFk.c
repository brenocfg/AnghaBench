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
struct TYPE_5__ {scalar_t__ nDeferredCons; scalar_t__ nDeferredImmCons; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_6__ {scalar_t__ nFkConstraint; int /*<<< orphan*/  errorAction; int /*<<< orphan*/  rc; TYPE_1__* db; } ;
typedef  TYPE_2__ Vdbe ;

/* Variables and functions */
 int /*<<< orphan*/  OE_Abort ; 
 int /*<<< orphan*/  SQLITE_CONSTRAINT_FOREIGNKEY ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3VdbeError (TYPE_2__*,char*) ; 

int sqlite3VdbeCheckFk(Vdbe *p, int deferred){
  sqlite3 *db = p->db;
  if( (deferred && (db->nDeferredCons+db->nDeferredImmCons)>0) 
   || (!deferred && p->nFkConstraint>0) 
  ){
    p->rc = SQLITE_CONSTRAINT_FOREIGNKEY;
    p->errorAction = OE_Abort;
    sqlite3VdbeError(p, "FOREIGN KEY constraint failed");
    return SQLITE_ERROR;
  }
  return SQLITE_OK;
}