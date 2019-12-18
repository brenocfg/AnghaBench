#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_2__ {int inTransaction; int mxSavepoint; scalar_t__ bIgnoreSavepoint; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  TESTONLY (int) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3SyncMethod (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3SavepointMethod(sqlite3_vtab *pVtab, int iSavepoint){
  int rc = SQLITE_OK;
  UNUSED_PARAMETER(iSavepoint);
  assert( ((Fts3Table *)pVtab)->inTransaction );
  assert( ((Fts3Table *)pVtab)->mxSavepoint <= iSavepoint );
  TESTONLY( ((Fts3Table *)pVtab)->mxSavepoint = iSavepoint );
  if( ((Fts3Table *)pVtab)->bIgnoreSavepoint==0 ){
    rc = fts3SyncMethod(pVtab);
  }
  return rc;
}