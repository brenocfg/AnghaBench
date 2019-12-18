#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int sqlite3_int64 ;
struct TYPE_14__ {int rc; TYPE_4__* pPhrase; } ;
typedef  TYPE_2__ TokenCtx ;
struct TYPE_16__ {int nTerm; TYPE_1__* aTerm; } ;
struct TYPE_15__ {int rc; int nPhrase; TYPE_4__** apPhrase; int /*<<< orphan*/ * pConfig; } ;
struct TYPE_13__ {scalar_t__ bPrefix; } ;
typedef  int /*<<< orphan*/  Fts5Token ;
typedef  TYPE_3__ Fts5Parse ;
typedef  TYPE_4__ Fts5ExprPhrase ;
typedef  int /*<<< orphan*/  Fts5Config ;

/* Variables and functions */
 int FTS5_TOKENIZE_PREFIX ; 
 int FTS5_TOKENIZE_QUERY ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts5ExprPhraseFree (TYPE_4__*) ; 
 int fts5ParseStringFromToken (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  fts5ParseTokenize ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3Fts5Dequote (char*) ; 
 TYPE_4__* sqlite3Fts5MallocZero (int*,int) ; 
 int sqlite3Fts5Tokenize (int /*<<< orphan*/ *,int,char*,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 scalar_t__ sqlite3_realloc64 (TYPE_4__**,int) ; 
 scalar_t__ strlen (char*) ; 

Fts5ExprPhrase *sqlite3Fts5ParseTerm(
  Fts5Parse *pParse,              /* Parse context */
  Fts5ExprPhrase *pAppend,        /* Phrase to append to */
  Fts5Token *pToken,              /* String to tokenize */
  int bPrefix                     /* True if there is a trailing "*" */
){
  Fts5Config *pConfig = pParse->pConfig;
  TokenCtx sCtx;                  /* Context object passed to callback */
  int rc;                         /* Tokenize return code */
  char *z = 0;

  memset(&sCtx, 0, sizeof(TokenCtx));
  sCtx.pPhrase = pAppend;

  rc = fts5ParseStringFromToken(pToken, &z);
  if( rc==SQLITE_OK ){
    int flags = FTS5_TOKENIZE_QUERY | (bPrefix ? FTS5_TOKENIZE_PREFIX : 0);
    int n;
    sqlite3Fts5Dequote(z);
    n = (int)strlen(z);
    rc = sqlite3Fts5Tokenize(pConfig, flags, z, n, &sCtx, fts5ParseTokenize);
  }
  sqlite3_free(z);
  if( rc || (rc = sCtx.rc) ){
    pParse->rc = rc;
    fts5ExprPhraseFree(sCtx.pPhrase);
    sCtx.pPhrase = 0;
  }else{

    if( pAppend==0 ){
      if( (pParse->nPhrase % 8)==0 ){
        sqlite3_int64 nByte = sizeof(Fts5ExprPhrase*) * (pParse->nPhrase + 8);
        Fts5ExprPhrase **apNew;
        apNew = (Fts5ExprPhrase**)sqlite3_realloc64(pParse->apPhrase, nByte);
        if( apNew==0 ){
          pParse->rc = SQLITE_NOMEM;
          fts5ExprPhraseFree(sCtx.pPhrase);
          return 0;
        }
        pParse->apPhrase = apNew;
      }
      pParse->nPhrase++;
    }

    if( sCtx.pPhrase==0 ){
      /* This happens when parsing a token or quoted phrase that contains
      ** no token characters at all. (e.g ... MATCH '""'). */
      sCtx.pPhrase = sqlite3Fts5MallocZero(&pParse->rc, sizeof(Fts5ExprPhrase));
    }else if( sCtx.pPhrase->nTerm ){
      sCtx.pPhrase->aTerm[sCtx.pPhrase->nTerm-1].bPrefix = (u8)bPrefix;
    }
    pParse->apPhrase[pParse->nPhrase-1] = sCtx.pPhrase;
  }

  return sCtx.pPhrase;
}