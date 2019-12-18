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
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {char* zDb; char* zName; int nIndex; int /*<<< orphan*/ * db; } ;
struct TYPE_4__ {TYPE_2__* pFts3Tab; } ;
typedef  TYPE_1__ Fts3auxTable ;
typedef  TYPE_2__ Fts3Table ;

/* Variables and functions */
 int /*<<< orphan*/  FTS3_AUX_SCHEMA ; 
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3Fts3Dequote (char*) ; 
 int /*<<< orphan*/  sqlite3Fts3ErrMsg (char**,char*) ; 
 int sqlite3_declare_vtab (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 
 scalar_t__ sqlite3_strnicmp (char*,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int fts3auxConnectMethod(
  sqlite3 *db,                    /* Database connection */
  void *pUnused,                  /* Unused */
  int argc,                       /* Number of elements in argv array */
  const char * const *argv,       /* xCreate/xConnect argument array */
  sqlite3_vtab **ppVtab,          /* OUT: New sqlite3_vtab object */
  char **pzErr                    /* OUT: sqlite3_malloc'd error message */
){
  char const *zDb;                /* Name of database (e.g. "main") */
  char const *zFts3;              /* Name of fts3 table */
  int nDb;                        /* Result of strlen(zDb) */
  int nFts3;                      /* Result of strlen(zFts3) */
  sqlite3_int64 nByte;            /* Bytes of space to allocate here */
  int rc;                         /* value returned by declare_vtab() */
  Fts3auxTable *p;                /* Virtual table object to return */

  UNUSED_PARAMETER(pUnused);

  /* The user should invoke this in one of two forms:
  **
  **     CREATE VIRTUAL TABLE xxx USING fts4aux(fts4-table);
  **     CREATE VIRTUAL TABLE xxx USING fts4aux(fts4-table-db, fts4-table);
  */
  if( argc!=4 && argc!=5 ) goto bad_args;

  zDb = argv[1]; 
  nDb = (int)strlen(zDb);
  if( argc==5 ){
    if( nDb==4 && 0==sqlite3_strnicmp("temp", zDb, 4) ){
      zDb = argv[3]; 
      nDb = (int)strlen(zDb);
      zFts3 = argv[4];
    }else{
      goto bad_args;
    }
  }else{
    zFts3 = argv[3];
  }
  nFts3 = (int)strlen(zFts3);

  rc = sqlite3_declare_vtab(db, FTS3_AUX_SCHEMA);
  if( rc!=SQLITE_OK ) return rc;

  nByte = sizeof(Fts3auxTable) + sizeof(Fts3Table) + nDb + nFts3 + 2;
  p = (Fts3auxTable *)sqlite3_malloc64(nByte);
  if( !p ) return SQLITE_NOMEM;
  memset(p, 0, nByte);

  p->pFts3Tab = (Fts3Table *)&p[1];
  p->pFts3Tab->zDb = (char *)&p->pFts3Tab[1];
  p->pFts3Tab->zName = &p->pFts3Tab->zDb[nDb+1];
  p->pFts3Tab->db = db;
  p->pFts3Tab->nIndex = 1;

  memcpy((char *)p->pFts3Tab->zDb, zDb, nDb);
  memcpy((char *)p->pFts3Tab->zName, zFts3, nFts3);
  sqlite3Fts3Dequote((char *)p->pFts3Tab->zName);

  *ppVtab = (sqlite3_vtab *)p;
  return SQLITE_OK;

 bad_args:
  sqlite3Fts3ErrMsg(pzErr, "invalid arguments to fts4aux constructor");
  return SQLITE_ERROR;
}