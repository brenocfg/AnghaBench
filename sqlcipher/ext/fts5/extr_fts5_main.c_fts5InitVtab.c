#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_12__ {char** pzErrmsg; } ;
struct TYPE_10__ {int /*<<< orphan*/  pIndex; TYPE_3__* pConfig; } ;
struct TYPE_11__ {TYPE_1__ p; int /*<<< orphan*/  pStorage; int /*<<< orphan*/ * pGlobal; } ;
typedef  int /*<<< orphan*/  Fts5Global ;
typedef  TYPE_2__ Fts5FullTable ;
typedef  TYPE_3__ Fts5Config ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_BEGIN ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5CheckTransactionState (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5FreeVtab (TYPE_2__*) ; 
 int sqlite3Fts5ConfigDeclareVtab (TYPE_3__*) ; 
 int sqlite3Fts5ConfigParse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const**,TYPE_3__**,char**) ; 
 int sqlite3Fts5IndexLoadConfig (int /*<<< orphan*/ ) ; 
 int sqlite3Fts5IndexOpen (TYPE_3__*,int,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  sqlite3Fts5IndexRollback (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3Fts5MallocZero (int*,int) ; 
 int sqlite3Fts5StorageOpen (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static int fts5InitVtab(
  int bCreate,                    /* True for xCreate, false for xConnect */
  sqlite3 *db,                    /* The SQLite database connection */
  void *pAux,                     /* Hash table containing tokenizers */
  int argc,                       /* Number of elements in argv array */
  const char * const *argv,       /* xCreate/xConnect argument array */
  sqlite3_vtab **ppVTab,          /* Write the resulting vtab structure here */
  char **pzErr                    /* Write any error message here */
){
  Fts5Global *pGlobal = (Fts5Global*)pAux;
  const char **azConfig = (const char**)argv;
  int rc = SQLITE_OK;             /* Return code */
  Fts5Config *pConfig = 0;        /* Results of parsing argc/argv */
  Fts5FullTable *pTab = 0;        /* New virtual table object */

  /* Allocate the new vtab object and parse the configuration */
  pTab = (Fts5FullTable*)sqlite3Fts5MallocZero(&rc, sizeof(Fts5FullTable));
  if( rc==SQLITE_OK ){
    rc = sqlite3Fts5ConfigParse(pGlobal, db, argc, azConfig, &pConfig, pzErr);
    assert( (rc==SQLITE_OK && *pzErr==0) || pConfig==0 );
  }
  if( rc==SQLITE_OK ){
    pTab->p.pConfig = pConfig;
    pTab->pGlobal = pGlobal;
  }

  /* Open the index sub-system */
  if( rc==SQLITE_OK ){
    rc = sqlite3Fts5IndexOpen(pConfig, bCreate, &pTab->p.pIndex, pzErr);
  }

  /* Open the storage sub-system */
  if( rc==SQLITE_OK ){
    rc = sqlite3Fts5StorageOpen(
        pConfig, pTab->p.pIndex, bCreate, &pTab->pStorage, pzErr
    );
  }

  /* Call sqlite3_declare_vtab() */
  if( rc==SQLITE_OK ){
    rc = sqlite3Fts5ConfigDeclareVtab(pConfig);
  }

  /* Load the initial configuration */
  if( rc==SQLITE_OK ){
    assert( pConfig->pzErrmsg==0 );
    pConfig->pzErrmsg = pzErr;
    rc = sqlite3Fts5IndexLoadConfig(pTab->p.pIndex);
    sqlite3Fts5IndexRollback(pTab->p.pIndex);
    pConfig->pzErrmsg = 0;
  }

  if( rc!=SQLITE_OK ){
    fts5FreeVtab(pTab);
    pTab = 0;
  }else if( bCreate ){
    fts5CheckTransactionState(pTab, FTS5_BEGIN, 0);
  }
  *ppVTab = (sqlite3_vtab*)pTab;
  return rc;
}