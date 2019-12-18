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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_4__ {scalar_t__* pzErrmsg; int iCookie; int /*<<< orphan*/  db; int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; int /*<<< orphan*/  nHashSize; int /*<<< orphan*/  nCrisisMerge; int /*<<< orphan*/  nUsermerge; int /*<<< orphan*/  nAutomerge; int /*<<< orphan*/  pgsz; } ;
typedef  TYPE_1__ Fts5Config ;

/* Variables and functions */
 int FTS5_CURRENT_VERSION ; 
 int /*<<< orphan*/  FTS5_DEFAULT_AUTOMERGE ; 
 int /*<<< orphan*/  FTS5_DEFAULT_CRISISMERGE ; 
 int /*<<< orphan*/  FTS5_DEFAULT_HASHSIZE ; 
 int /*<<< orphan*/  FTS5_DEFAULT_PAGE_SIZE ; 
 int /*<<< orphan*/  FTS5_DEFAULT_USERMERGE ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3Fts5ConfigSetValue (TYPE_1__*,char const*,int /*<<< orphan*/ *,int*) ; 
 char* sqlite3Fts5Mprintf (int*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3_column_value (int /*<<< orphan*/ *,int) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 scalar_t__ sqlite3_mprintf (char*,int,int) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_stricmp (char const*,char*) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 

int sqlite3Fts5ConfigLoad(Fts5Config *pConfig, int iCookie){
  const char *zSelect = "SELECT k, v FROM %Q.'%q_config'";
  char *zSql;
  sqlite3_stmt *p = 0;
  int rc = SQLITE_OK;
  int iVersion = 0;

  /* Set default values */
  pConfig->pgsz = FTS5_DEFAULT_PAGE_SIZE;
  pConfig->nAutomerge = FTS5_DEFAULT_AUTOMERGE;
  pConfig->nUsermerge = FTS5_DEFAULT_USERMERGE;
  pConfig->nCrisisMerge = FTS5_DEFAULT_CRISISMERGE;
  pConfig->nHashSize = FTS5_DEFAULT_HASHSIZE;

  zSql = sqlite3Fts5Mprintf(&rc, zSelect, pConfig->zDb, pConfig->zName);
  if( zSql ){
    rc = sqlite3_prepare_v2(pConfig->db, zSql, -1, &p, 0);
    sqlite3_free(zSql);
  }

  assert( rc==SQLITE_OK || p==0 );
  if( rc==SQLITE_OK ){
    while( SQLITE_ROW==sqlite3_step(p) ){
      const char *zK = (const char*)sqlite3_column_text(p, 0);
      sqlite3_value *pVal = sqlite3_column_value(p, 1);
      if( 0==sqlite3_stricmp(zK, "version") ){
        iVersion = sqlite3_value_int(pVal);
      }else{
        int bDummy = 0;
        sqlite3Fts5ConfigSetValue(pConfig, zK, pVal, &bDummy);
      }
    }
    rc = sqlite3_finalize(p);
  }
  
  if( rc==SQLITE_OK && iVersion!=FTS5_CURRENT_VERSION ){
    rc = SQLITE_ERROR;
    if( pConfig->pzErrmsg ){
      assert( 0==*pConfig->pzErrmsg );
      *pConfig->pzErrmsg = sqlite3_mprintf(
          "invalid fts5 file format (found %d, expected %d) - run 'rebuild'",
          iVersion, FTS5_CURRENT_VERSION
      );
    }
  }

  if( rc==SQLITE_OK ){
    pConfig->iCookie = iCookie;
  }
  return rc;
}