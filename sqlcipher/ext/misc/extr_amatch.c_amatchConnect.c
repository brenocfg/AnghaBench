#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_6__ {scalar_t__ zClassName; scalar_t__ zSelf; scalar_t__ zVocabTab; scalar_t__ zVocabWord; scalar_t__ zVocabLang; scalar_t__ zCostTab; int /*<<< orphan*/  base; void* zDb; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ amatch_vtab ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 void* amatchDequote (char const*) ; 
 int /*<<< orphan*/  amatchFree (TYPE_1__*) ; 
 int amatchLoadRules (int /*<<< orphan*/ *,TYPE_1__*,char**) ; 
 char* amatchValueOfKey (char*,char const* const) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3_declare_vtab (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 TYPE_1__* sqlite3_malloc (int) ; 
 void* sqlite3_mprintf (char*,...) ; 

__attribute__((used)) static int amatchConnect(
  sqlite3 *db,
  void *pAux,
  int argc, const char *const*argv,
  sqlite3_vtab **ppVtab,
  char **pzErr
){
  int rc = SQLITE_OK;             /* Return code */
  amatch_vtab *pNew = 0;          /* New virtual table */
  const char *zModule = argv[0];
  const char *zDb = argv[1];
  const char *zVal;
  int i;

  (void)pAux;
  *ppVtab = 0;
  pNew = sqlite3_malloc( sizeof(*pNew) );
  if( pNew==0 ) return SQLITE_NOMEM;
  rc = SQLITE_NOMEM;
  memset(pNew, 0, sizeof(*pNew));
  pNew->db = db;
  pNew->zClassName = sqlite3_mprintf("%s", zModule);
  if( pNew->zClassName==0 ) goto amatchConnectError;
  pNew->zDb = sqlite3_mprintf("%s", zDb);
  if( pNew->zDb==0 ) goto amatchConnectError;
  pNew->zSelf = sqlite3_mprintf("%s", argv[2]);
  if( pNew->zSelf==0 ) goto amatchConnectError;
  for(i=3; i<argc; i++){
    zVal = amatchValueOfKey("vocabulary_table", argv[i]);
    if( zVal ){
      sqlite3_free(pNew->zVocabTab);
      pNew->zVocabTab = amatchDequote(zVal);
      if( pNew->zVocabTab==0 ) goto amatchConnectError;
      continue;
    }
    zVal = amatchValueOfKey("vocabulary_word", argv[i]);
    if( zVal ){
      sqlite3_free(pNew->zVocabWord);
      pNew->zVocabWord = amatchDequote(zVal);
      if( pNew->zVocabWord==0 ) goto amatchConnectError;
      continue;
    }
    zVal = amatchValueOfKey("vocabulary_language", argv[i]);
    if( zVal ){
      sqlite3_free(pNew->zVocabLang);
      pNew->zVocabLang = amatchDequote(zVal);
      if( pNew->zVocabLang==0 ) goto amatchConnectError;
      continue;
    }
    zVal = amatchValueOfKey("edit_distances", argv[i]);
    if( zVal ){
      sqlite3_free(pNew->zCostTab);
      pNew->zCostTab = amatchDequote(zVal);
      if( pNew->zCostTab==0 ) goto amatchConnectError;
      continue;
    }
    *pzErr = sqlite3_mprintf("unrecognized argument: [%s]\n", argv[i]);
    amatchFree(pNew);
    *ppVtab = 0;
    return SQLITE_ERROR;
  }
  rc = SQLITE_OK;
  if( pNew->zCostTab==0 ){
    *pzErr = sqlite3_mprintf("no edit_distances table specified");
    rc = SQLITE_ERROR;
  }else{
    rc = amatchLoadRules(db, pNew, pzErr);
  }
  if( rc==SQLITE_OK ){
    rc = sqlite3_declare_vtab(db,
           "CREATE TABLE x(word,distance,language,"
           "command HIDDEN,nword HIDDEN)"
         );
#define AMATCH_COL_WORD       0
#define AMATCH_COL_DISTANCE   1
#define AMATCH_COL_LANGUAGE   2
#define AMATCH_COL_COMMAND    3
#define AMATCH_COL_NWORD      4
  }
  if( rc!=SQLITE_OK ){
    amatchFree(pNew);
  }
  *ppVtab = &pNew->base;
  return rc;

amatchConnectError:
  amatchFree(pNew);
  return rc;
}