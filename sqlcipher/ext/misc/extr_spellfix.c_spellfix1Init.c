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
struct TYPE_4__ {char* zDbName; scalar_t__ zTableName; scalar_t__ zCostTable; int /*<<< orphan*/  base; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ spellfix1_vtab ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spellfix1DbExec (int*,int /*<<< orphan*/ *,char*,char const*,char const*,...) ; 
 scalar_t__ spellfix1Dequote (char const*) ; 
 int /*<<< orphan*/  spellfix1Uninit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sqlite3_declare_vtab (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* sqlite3_malloc64 (int) ; 
 void* sqlite3_mprintf (char*,char const* const) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const* const,char*,int) ; 

__attribute__((used)) static int spellfix1Init(
  int isCreate,
  sqlite3 *db,
  void *pAux,
  int argc, const char *const*argv,
  sqlite3_vtab **ppVTab,
  char **pzErr
){
  spellfix1_vtab *pNew = 0;
  /* const char *zModule = argv[0]; // not used */
  const char *zDbName = argv[1];
  const char *zTableName = argv[2];
  int nDbName;
  int rc = SQLITE_OK;
  int i;

  nDbName = (int)strlen(zDbName);
  pNew = sqlite3_malloc64( sizeof(*pNew) + nDbName + 1);
  if( pNew==0 ){
    rc = SQLITE_NOMEM;
  }else{
    memset(pNew, 0, sizeof(*pNew));
    pNew->zDbName = (char*)&pNew[1];
    memcpy(pNew->zDbName, zDbName, nDbName+1);
    pNew->zTableName = sqlite3_mprintf("%s", zTableName);
    pNew->db = db;
    if( pNew->zTableName==0 ){
      rc = SQLITE_NOMEM;
    }else{
      rc = sqlite3_declare_vtab(db, 
           "CREATE TABLE x(word,rank,distance,langid, "
           "score, matchlen, phonehash HIDDEN, "
           "top HIDDEN, scope HIDDEN, srchcnt HIDDEN, "
           "soundslike HIDDEN, command HIDDEN)"
      );
#define SPELLFIX_COL_WORD            0
#define SPELLFIX_COL_RANK            1
#define SPELLFIX_COL_DISTANCE        2
#define SPELLFIX_COL_LANGID          3
#define SPELLFIX_COL_SCORE           4
#define SPELLFIX_COL_MATCHLEN        5
#define SPELLFIX_COL_PHONEHASH       6
#define SPELLFIX_COL_TOP             7
#define SPELLFIX_COL_SCOPE           8
#define SPELLFIX_COL_SRCHCNT         9
#define SPELLFIX_COL_SOUNDSLIKE     10
#define SPELLFIX_COL_COMMAND        11
    }
    if( rc==SQLITE_OK && isCreate ){
      spellfix1DbExec(&rc, db,
         "CREATE TABLE IF NOT EXISTS \"%w\".\"%w_vocab\"(\n"
         "  id INTEGER PRIMARY KEY,\n"
         "  rank INT,\n"
         "  langid INT,\n"
         "  word TEXT,\n"
         "  k1 TEXT,\n"
         "  k2 TEXT\n"
         ");\n",
         zDbName, zTableName
      );
      spellfix1DbExec(&rc, db,
         "CREATE INDEX IF NOT EXISTS \"%w\".\"%w_vocab_index_langid_k2\" "
            "ON \"%w_vocab\"(langid,k2);",
         zDbName, zTableName, zTableName
      );
    }
    for(i=3; rc==SQLITE_OK && i<argc; i++){
      if( strncmp(argv[i],"edit_cost_table=",16)==0 && pNew->zCostTable==0 ){
        pNew->zCostTable = spellfix1Dequote(&argv[i][16]);
        if( pNew->zCostTable==0 ) rc = SQLITE_NOMEM;
        continue;
      }
      *pzErr = sqlite3_mprintf("bad argument to spellfix1(): \"%s\"", argv[i]);
      rc = SQLITE_ERROR; 
    }
  }

  if( rc && pNew ){
    *ppVTab = 0;
    spellfix1Uninit(0, &pNew->base);
  }else{
    *ppVTab = (sqlite3_vtab *)pNew;
  }
  return rc;
}