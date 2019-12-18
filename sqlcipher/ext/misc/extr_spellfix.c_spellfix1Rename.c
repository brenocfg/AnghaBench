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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_2__ {char* zTableName; int /*<<< orphan*/  zDbName; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ spellfix1_vtab ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  spellfix1DbExec (int*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 

__attribute__((used)) static int spellfix1Rename(sqlite3_vtab *pVTab, const char *zNew){
  spellfix1_vtab *p = (spellfix1_vtab*)pVTab;
  sqlite3 *db = p->db;
  int rc = SQLITE_OK;
  char *zNewName = sqlite3_mprintf("%s", zNew);
  if( zNewName==0 ){
    return SQLITE_NOMEM;
  }
  spellfix1DbExec(&rc, db, 
     "ALTER TABLE \"%w\".\"%w_vocab\" RENAME TO \"%w_vocab\"",
     p->zDbName, p->zTableName, zNewName
  );
  if( rc==SQLITE_OK ){
    sqlite3_free(p->zTableName);
    p->zTableName = zNewName;
  }else{
    sqlite3_free(zNewName);
  }
  return rc;
}