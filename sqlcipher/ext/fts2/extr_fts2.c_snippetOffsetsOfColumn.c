#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int (* xOpen ) (TYPE_3__*,char const*,int,TYPE_2__**) ;int (* xNext ) (TYPE_2__*,char const**,int*,int*,int*,int*) ;int /*<<< orphan*/  (* xClose ) (TYPE_2__*) ;} ;
typedef  TYPE_1__ sqlite3_tokenizer_module ;
struct TYPE_13__ {TYPE_3__* pTokenizer; } ;
typedef  TYPE_2__ sqlite3_tokenizer_cursor ;
struct TYPE_14__ {TYPE_1__* pModule; } ;
typedef  TYPE_3__ sqlite3_tokenizer ;
struct TYPE_15__ {int nColumn; TYPE_3__* pTokenizer; } ;
typedef  TYPE_4__ fulltext_vtab ;
struct TYPE_17__ {int nTerms; TYPE_5__* pTerms; TYPE_4__* pFts; } ;
struct TYPE_16__ {int iColumn; int nTerm; int iPhrase; int /*<<< orphan*/  pTerm; int /*<<< orphan*/  isPrefix; } ;
typedef  int /*<<< orphan*/  Snippet ;
typedef  TYPE_5__ QueryTerm ;
typedef  TYPE_6__ Query ;

/* Variables and functions */
 unsigned int FTS2_ROTOR_MASK ; 
 int FTS2_ROTOR_SZ ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  snippetAppendMatch (int /*<<< orphan*/ *,int,int,int,int) ; 
 int stub1 (TYPE_3__*,char const*,int,TYPE_2__**) ; 
 int stub2 (TYPE_2__*,char const**,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

__attribute__((used)) static void snippetOffsetsOfColumn(
  Query *pQuery,
  Snippet *pSnippet,
  int iColumn,
  const char *zDoc,
  int nDoc
){
  const sqlite3_tokenizer_module *pTModule;  /* The tokenizer module */
  sqlite3_tokenizer *pTokenizer;             /* The specific tokenizer */
  sqlite3_tokenizer_cursor *pTCursor;        /* Tokenizer cursor */
  fulltext_vtab *pVtab;                /* The full text index */
  int nColumn;                         /* Number of columns in the index */
  const QueryTerm *aTerm;              /* Query string terms */
  int nTerm;                           /* Number of query string terms */  
  int i, j;                            /* Loop counters */
  int rc;                              /* Return code */
  unsigned int match, prevMatch;       /* Phrase search bitmasks */
  const char *zToken;                  /* Next token from the tokenizer */
  int nToken;                          /* Size of zToken */
  int iBegin, iEnd, iPos;              /* Offsets of beginning and end */

  /* The following variables keep a circular buffer of the last
  ** few tokens */
  unsigned int iRotor = 0;             /* Index of current token */
  int iRotorBegin[FTS2_ROTOR_SZ];      /* Beginning offset of token */
  int iRotorLen[FTS2_ROTOR_SZ];        /* Length of token */

  pVtab = pQuery->pFts;
  nColumn = pVtab->nColumn;
  pTokenizer = pVtab->pTokenizer;
  pTModule = pTokenizer->pModule;
  rc = pTModule->xOpen(pTokenizer, zDoc, nDoc, &pTCursor);
  if( rc ) return;
  pTCursor->pTokenizer = pTokenizer;
  aTerm = pQuery->pTerms;
  nTerm = pQuery->nTerms;
  if( nTerm>=FTS2_ROTOR_SZ ){
    nTerm = FTS2_ROTOR_SZ - 1;
  }
  prevMatch = 0;
  while(1){
    rc = pTModule->xNext(pTCursor, &zToken, &nToken, &iBegin, &iEnd, &iPos);
    if( rc ) break;
    iRotorBegin[iRotor&FTS2_ROTOR_MASK] = iBegin;
    iRotorLen[iRotor&FTS2_ROTOR_MASK] = iEnd-iBegin;
    match = 0;
    for(i=0; i<nTerm; i++){
      int iCol;
      iCol = aTerm[i].iColumn;
      if( iCol>=0 && iCol<nColumn && iCol!=iColumn ) continue;
      if( aTerm[i].nTerm>nToken ) continue;
      if( !aTerm[i].isPrefix && aTerm[i].nTerm<nToken ) continue;
      assert( aTerm[i].nTerm<=nToken );
      if( memcmp(aTerm[i].pTerm, zToken, aTerm[i].nTerm) ) continue;
      if( aTerm[i].iPhrase>1 && (prevMatch & (1<<i))==0 ) continue;
      match |= 1<<i;
      if( i==nTerm-1 || aTerm[i+1].iPhrase==1 ){
        for(j=aTerm[i].iPhrase-1; j>=0; j--){
          int k = (iRotor-j) & FTS2_ROTOR_MASK;
          snippetAppendMatch(pSnippet, iColumn, i-j,
                iRotorBegin[k], iRotorLen[k]);
        }
      }
    }
    prevMatch = match<<1;
    iRotor++;
  }
  pTModule->xClose(pTCursor);  
}