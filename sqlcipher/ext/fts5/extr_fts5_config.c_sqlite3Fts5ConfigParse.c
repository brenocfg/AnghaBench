#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_9__ {int iCookie; char** azCol; char const* zName; int bColumnsize; int bPrefixIndex; scalar_t__ pTok; scalar_t__ zContent; scalar_t__ eContent; scalar_t__ zContentRowid; void* zDb; int /*<<< orphan*/  eDetail; int /*<<< orphan*/ * abUnindexed; int /*<<< orphan*/ * db; } ;
typedef  int /*<<< orphan*/  Fts5Global ;
typedef  TYPE_1__ Fts5Config ;

/* Variables and functions */
 scalar_t__ FTS5_CONTENT_NONE ; 
 scalar_t__ FTS5_CONTENT_NORMAL ; 
 int /*<<< orphan*/  FTS5_DETAIL_FULL ; 
 int /*<<< orphan*/  FTS5_RANK_NAME ; 
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5ConfigDefaultTokenizer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* fts5ConfigGobbleWord (int*,char const*,char**,int*) ; 
 int fts5ConfigMakeExprlist (TYPE_1__*) ; 
 int fts5ConfigParseColumn (TYPE_1__*,char*,char*,char**) ; 
 int fts5ConfigParseSpecial (int /*<<< orphan*/ *,TYPE_1__*,char*,char*,char**) ; 
 char* fts5ConfigSkipWhitespace (char const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3Fts5ConfigFree (TYPE_1__*) ; 
 scalar_t__ sqlite3Fts5MallocZero (int*,int) ; 
 scalar_t__ sqlite3Fts5Mprintf (int*,char*,void*,char const*,char const*) ; 
 void* sqlite3Fts5Strndup (int*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 scalar_t__ sqlite3_malloc (int) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 scalar_t__ sqlite3_stricmp (char const*,int /*<<< orphan*/ ) ; 

int sqlite3Fts5ConfigParse(
  Fts5Global *pGlobal,
  sqlite3 *db,
  int nArg,                       /* Number of arguments */
  const char **azArg,             /* Array of nArg CREATE VIRTUAL TABLE args */
  Fts5Config **ppOut,             /* OUT: Results of parse */
  char **pzErr                    /* OUT: Error message */
){
  int rc = SQLITE_OK;             /* Return code */
  Fts5Config *pRet;               /* New object to return */
  int i;
  sqlite3_int64 nByte;

  *ppOut = pRet = (Fts5Config*)sqlite3_malloc(sizeof(Fts5Config));
  if( pRet==0 ) return SQLITE_NOMEM;
  memset(pRet, 0, sizeof(Fts5Config));
  pRet->db = db;
  pRet->iCookie = -1;

  nByte = nArg * (sizeof(char*) + sizeof(u8));
  pRet->azCol = (char**)sqlite3Fts5MallocZero(&rc, nByte);
  pRet->abUnindexed = (u8*)&pRet->azCol[nArg];
  pRet->zDb = sqlite3Fts5Strndup(&rc, azArg[1], -1);
  pRet->zName = sqlite3Fts5Strndup(&rc, azArg[2], -1);
  pRet->bColumnsize = 1;
  pRet->eDetail = FTS5_DETAIL_FULL;
#ifdef SQLITE_DEBUG
  pRet->bPrefixIndex = 1;
#endif
  if( rc==SQLITE_OK && sqlite3_stricmp(pRet->zName, FTS5_RANK_NAME)==0 ){
    *pzErr = sqlite3_mprintf("reserved fts5 table name: %s", pRet->zName);
    rc = SQLITE_ERROR;
  }

  for(i=3; rc==SQLITE_OK && i<nArg; i++){
    const char *zOrig = azArg[i];
    const char *z;
    char *zOne = 0;
    char *zTwo = 0;
    int bOption = 0;
    int bMustBeCol = 0;

    z = fts5ConfigGobbleWord(&rc, zOrig, &zOne, &bMustBeCol);
    z = fts5ConfigSkipWhitespace(z);
    if( z && *z=='=' ){
      bOption = 1;
      z++;
      if( bMustBeCol ) z = 0;
    }
    z = fts5ConfigSkipWhitespace(z);
    if( z && z[0] ){
      int bDummy;
      z = fts5ConfigGobbleWord(&rc, z, &zTwo, &bDummy);
      if( z && z[0] ) z = 0;
    }

    if( rc==SQLITE_OK ){
      if( z==0 ){
        *pzErr = sqlite3_mprintf("parse error in \"%s\"", zOrig);
        rc = SQLITE_ERROR;
      }else{
        if( bOption ){
          rc = fts5ConfigParseSpecial(pGlobal, pRet, zOne, zTwo?zTwo:"", pzErr);
        }else{
          rc = fts5ConfigParseColumn(pRet, zOne, zTwo, pzErr);
          zOne = 0;
        }
      }
    }

    sqlite3_free(zOne);
    sqlite3_free(zTwo);
  }

  /* If a tokenizer= option was successfully parsed, the tokenizer has
  ** already been allocated. Otherwise, allocate an instance of the default
  ** tokenizer (unicode61) now.  */
  if( rc==SQLITE_OK && pRet->pTok==0 ){
    rc = fts5ConfigDefaultTokenizer(pGlobal, pRet);
  }

  /* If no zContent option was specified, fill in the default values. */
  if( rc==SQLITE_OK && pRet->zContent==0 ){
    const char *zTail = 0;
    assert( pRet->eContent==FTS5_CONTENT_NORMAL 
         || pRet->eContent==FTS5_CONTENT_NONE 
    );
    if( pRet->eContent==FTS5_CONTENT_NORMAL ){
      zTail = "content";
    }else if( pRet->bColumnsize ){
      zTail = "docsize";
    }

    if( zTail ){
      pRet->zContent = sqlite3Fts5Mprintf(
          &rc, "%Q.'%q_%s'", pRet->zDb, pRet->zName, zTail
      );
    }
  }

  if( rc==SQLITE_OK && pRet->zContentRowid==0 ){
    pRet->zContentRowid = sqlite3Fts5Strndup(&rc, "rowid", -1);
  }

  /* Formulate the zContentExprlist text */
  if( rc==SQLITE_OK ){
    rc = fts5ConfigMakeExprlist(pRet);
  }

  if( rc!=SQLITE_OK ){
    sqlite3Fts5ConfigFree(pRet);
    *ppOut = 0;
  }
  return rc;
}