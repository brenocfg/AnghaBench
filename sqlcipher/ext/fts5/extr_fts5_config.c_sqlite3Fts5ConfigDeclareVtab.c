#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nCol; char const* zName; int /*<<< orphan*/  db; int /*<<< orphan*/ * azCol; } ;
typedef  TYPE_1__ Fts5Config ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_RANK_NAME ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* sqlite3Fts5Mprintf (int*,char*,...) ; 
 int sqlite3_declare_vtab (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 

int sqlite3Fts5ConfigDeclareVtab(Fts5Config *pConfig){
  int i;
  int rc = SQLITE_OK;
  char *zSql;

  zSql = sqlite3Fts5Mprintf(&rc, "CREATE TABLE x(");
  for(i=0; zSql && i<pConfig->nCol; i++){
    const char *zSep = (i==0?"":", ");
    zSql = sqlite3Fts5Mprintf(&rc, "%z%s%Q", zSql, zSep, pConfig->azCol[i]);
  }
  zSql = sqlite3Fts5Mprintf(&rc, "%z, %Q HIDDEN, %s HIDDEN)", 
      zSql, pConfig->zName, FTS5_RANK_NAME
  );

  assert( zSql || rc==SQLITE_NOMEM );
  if( zSql ){
    rc = sqlite3_declare_vtab(pConfig->db, zSql);
    sqlite3_free(zSql);
  }
  
  return rc;
}