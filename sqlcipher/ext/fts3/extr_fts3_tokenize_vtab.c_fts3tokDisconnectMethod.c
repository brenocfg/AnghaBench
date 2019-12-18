#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {int /*<<< orphan*/  pTok; TYPE_1__* pMod; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* xDestroy ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ Fts3tokTable ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts3tokDisconnectMethod(sqlite3_vtab *pVtab){
  Fts3tokTable *pTab = (Fts3tokTable *)pVtab;

  pTab->pMod->xDestroy(pTab->pTok);
  sqlite3_free(pTab);
  return SQLITE_OK;
}