#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pVtab; } ;
typedef  TYPE_2__ sqlite3_vtab_cursor ;
struct TYPE_10__ {int /*<<< orphan*/  iPos; int /*<<< orphan*/  iEnd; int /*<<< orphan*/  iStart; int /*<<< orphan*/  nToken; int /*<<< orphan*/  zToken; int /*<<< orphan*/  pCsr; int /*<<< orphan*/  iRowid; } ;
struct TYPE_9__ {TYPE_1__* pMod; } ;
struct TYPE_7__ {int (* xNext ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ Fts3tokTable ;
typedef  TYPE_4__ Fts3tokCursor ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts3tokResetCursor (TYPE_4__*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3tokNextMethod(sqlite3_vtab_cursor *pCursor){
  Fts3tokCursor *pCsr = (Fts3tokCursor *)pCursor;
  Fts3tokTable *pTab = (Fts3tokTable *)(pCursor->pVtab);
  int rc;                         /* Return code */

  pCsr->iRowid++;
  rc = pTab->pMod->xNext(pCsr->pCsr,
      &pCsr->zToken, &pCsr->nToken,
      &pCsr->iStart, &pCsr->iEnd, &pCsr->iPos
  );

  if( rc!=SQLITE_OK ){
    fts3tokResetCursor(pCsr);
    if( rc==SQLITE_DONE ) rc = SQLITE_OK;
  }

  return rc;
}