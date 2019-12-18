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
struct TYPE_2__ {char* zDb; int /*<<< orphan*/  zName; scalar_t__ zContentTbl; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts3DbExec (int*,int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int fts3DisconnectMethod (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3DestroyMethod(sqlite3_vtab *pVtab){
  Fts3Table *p = (Fts3Table *)pVtab;
  int rc = SQLITE_OK;              /* Return code */
  const char *zDb = p->zDb;        /* Name of database (e.g. "main", "temp") */
  sqlite3 *db = p->db;             /* Database handle */

  /* Drop the shadow tables */
  fts3DbExec(&rc, db, 
    "DROP TABLE IF EXISTS %Q.'%q_segments';"
    "DROP TABLE IF EXISTS %Q.'%q_segdir';"
    "DROP TABLE IF EXISTS %Q.'%q_docsize';"
    "DROP TABLE IF EXISTS %Q.'%q_stat';"
    "%s DROP TABLE IF EXISTS %Q.'%q_content';",
    zDb, p->zName,
    zDb, p->zName,
    zDb, p->zName,
    zDb, p->zName,
    (p->zContentTbl ? "--" : ""), zDb,p->zName
  );

  /* If everything has worked, invoke fts3DisconnectMethod() to free the
  ** memory associated with the Fts3Table structure and return SQLITE_OK.
  ** Otherwise, return an SQLite error code.
  */
  return (rc==SQLITE_OK ? fts3DisconnectMethod(pVtab) : rc);
}