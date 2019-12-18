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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {struct TYPE_4__* zCostTable; int /*<<< orphan*/  pConfig3; struct TYPE_4__* zTableName; int /*<<< orphan*/  zDbName; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ spellfix1_vtab ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  editDist3ConfigDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spellfix1DbExec (int*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static int spellfix1Uninit(int isDestroy, sqlite3_vtab *pVTab){
  spellfix1_vtab *p = (spellfix1_vtab*)pVTab;
  int rc = SQLITE_OK;
  if( isDestroy ){
    sqlite3 *db = p->db;
    spellfix1DbExec(&rc, db, "DROP TABLE IF EXISTS \"%w\".\"%w_vocab\"",
                  p->zDbName, p->zTableName);
  }
  if( rc==SQLITE_OK ){
    sqlite3_free(p->zTableName);
    editDist3ConfigDelete(p->pConfig3);
    sqlite3_free(p->zCostTable);
    sqlite3_free(p);
  }
  return rc;
}