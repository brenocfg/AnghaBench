#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int (* xNext ) (int /*<<< orphan*/ *,char const**,int*,int*,int*,int*) ;int /*<<< orphan*/  (* xClose ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ sqlite3_tokenizer_module ;
typedef  int /*<<< orphan*/  sqlite3_tokenizer_cursor ;
struct TYPE_12__ {TYPE_2__* pModule; } ;
typedef  TYPE_3__ sqlite3_tokenizer ;
typedef  int sqlite3_int64 ;
struct TYPE_15__ {TYPE_5__* pPhrase; int /*<<< orphan*/  eType; } ;
struct TYPE_14__ {int nToken; int iColumn; TYPE_1__* aToken; } ;
struct TYPE_13__ {int isNot; scalar_t__ bFts4; int /*<<< orphan*/  iLangid; TYPE_3__* pTokenizer; } ;
struct TYPE_10__ {int n; char* z; int isPrefix; int bFirst; } ;
typedef  TYPE_4__ ParseContext ;
typedef  TYPE_5__ Fts3Phrase ;
typedef  TYPE_6__ Fts3Expr ;

/* Variables and functions */
 int /*<<< orphan*/  FTSQUERY_PHRASE ; 
 int SQLITE_DONE ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ fts3MallocZero (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int sqlite3Fts3OpenTokenizer (TYPE_3__*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **) ; 
 scalar_t__ sqlite3_fts3_enable_parentheses ; 
 int stub1 (int /*<<< orphan*/ *,char const**,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int getNextToken(
  ParseContext *pParse,                   /* fts3 query parse context */
  int iCol,                               /* Value for Fts3Phrase.iColumn */
  const char *z, int n,                   /* Input string */
  Fts3Expr **ppExpr,                      /* OUT: expression */
  int *pnConsumed                         /* OUT: Number of bytes consumed */
){
  sqlite3_tokenizer *pTokenizer = pParse->pTokenizer;
  sqlite3_tokenizer_module const *pModule = pTokenizer->pModule;
  int rc;
  sqlite3_tokenizer_cursor *pCursor;
  Fts3Expr *pRet = 0;
  int i = 0;

  /* Set variable i to the maximum number of bytes of input to tokenize. */
  for(i=0; i<n; i++){
    if( sqlite3_fts3_enable_parentheses && (z[i]=='(' || z[i]==')') ) break;
    if( z[i]=='"' ) break;
  }

  *pnConsumed = i;
  rc = sqlite3Fts3OpenTokenizer(pTokenizer, pParse->iLangid, z, i, &pCursor);
  if( rc==SQLITE_OK ){
    const char *zToken;
    int nToken = 0, iStart = 0, iEnd = 0, iPosition = 0;
    sqlite3_int64 nByte;                    /* total space to allocate */

    rc = pModule->xNext(pCursor, &zToken, &nToken, &iStart, &iEnd, &iPosition);
    if( rc==SQLITE_OK ){
      nByte = sizeof(Fts3Expr) + sizeof(Fts3Phrase) + nToken;
      pRet = (Fts3Expr *)fts3MallocZero(nByte);
      if( !pRet ){
        rc = SQLITE_NOMEM;
      }else{
        pRet->eType = FTSQUERY_PHRASE;
        pRet->pPhrase = (Fts3Phrase *)&pRet[1];
        pRet->pPhrase->nToken = 1;
        pRet->pPhrase->iColumn = iCol;
        pRet->pPhrase->aToken[0].n = nToken;
        pRet->pPhrase->aToken[0].z = (char *)&pRet->pPhrase[1];
        memcpy(pRet->pPhrase->aToken[0].z, zToken, nToken);

        if( iEnd<n && z[iEnd]=='*' ){
          pRet->pPhrase->aToken[0].isPrefix = 1;
          iEnd++;
        }

        while( 1 ){
          if( !sqlite3_fts3_enable_parentheses 
           && iStart>0 && z[iStart-1]=='-' 
          ){
            pParse->isNot = 1;
            iStart--;
          }else if( pParse->bFts4 && iStart>0 && z[iStart-1]=='^' ){
            pRet->pPhrase->aToken[0].bFirst = 1;
            iStart--;
          }else{
            break;
          }
        }

      }
      *pnConsumed = iEnd;
    }else if( i && rc==SQLITE_DONE ){
      rc = SQLITE_OK;
    }

    pModule->xClose(pCursor);
  }
  
  *ppExpr = pRet;
  return rc;
}