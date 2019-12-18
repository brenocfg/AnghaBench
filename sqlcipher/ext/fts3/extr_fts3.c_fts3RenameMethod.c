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
struct TYPE_4__ {scalar_t__ nPendingData; scalar_t__ zContentTbl; int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; scalar_t__ bHasStat; scalar_t__ bHasDocsize; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3DbExec (int*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int fts3SetHasStat (TYPE_1__*) ; 
 int sqlite3Fts3PendingTermsFlush (TYPE_1__*) ; 

__attribute__((used)) static int fts3RenameMethod(
  sqlite3_vtab *pVtab,            /* Virtual table handle */
  const char *zName               /* New name of table */
){
  Fts3Table *p = (Fts3Table *)pVtab;
  sqlite3 *db = p->db;            /* Database connection */
  int rc;                         /* Return Code */

  /* At this point it must be known if the %_stat table exists or not.
  ** So bHasStat may not be 2.  */
  rc = fts3SetHasStat(p);
  
  /* As it happens, the pending terms table is always empty here. This is
  ** because an "ALTER TABLE RENAME TABLE" statement inside a transaction 
  ** always opens a savepoint transaction. And the xSavepoint() method 
  ** flushes the pending terms table. But leave the (no-op) call to
  ** PendingTermsFlush() in in case that changes.
  */
  assert( p->nPendingData==0 );
  if( rc==SQLITE_OK ){
    rc = sqlite3Fts3PendingTermsFlush(p);
  }

  if( p->zContentTbl==0 ){
    fts3DbExec(&rc, db,
      "ALTER TABLE %Q.'%q_content'  RENAME TO '%q_content';",
      p->zDb, p->zName, zName
    );
  }

  if( p->bHasDocsize ){
    fts3DbExec(&rc, db,
      "ALTER TABLE %Q.'%q_docsize'  RENAME TO '%q_docsize';",
      p->zDb, p->zName, zName
    );
  }
  if( p->bHasStat ){
    fts3DbExec(&rc, db,
      "ALTER TABLE %Q.'%q_stat'  RENAME TO '%q_stat';",
      p->zDb, p->zName, zName
    );
  }
  fts3DbExec(&rc, db,
    "ALTER TABLE %Q.'%q_segments' RENAME TO '%q_segments';",
    p->zDb, p->zName, zName
  );
  fts3DbExec(&rc, db,
    "ALTER TABLE %Q.'%q_segdir'   RENAME TO '%q_segdir';",
    p->zDb, p->zName, zName
  );
  return rc;
}