#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int sqlite3_int64 ;
struct TYPE_12__ {scalar_t__ pVtab; } ;
struct TYPE_14__ {int /*<<< orphan*/  pDeferred; int /*<<< orphan*/ * pExpr; int /*<<< orphan*/  iPrevId; TYPE_1__ base; } ;
struct TYPE_13__ {char flag; int* aMatchinfo; int nPhrase; int nCol; int nDoc; } ;
typedef  TYPE_2__ MatchInfo ;
typedef  int /*<<< orphan*/  Fts3Table ;
typedef  int /*<<< orphan*/  Fts3Expr ;
typedef  TYPE_3__ Fts3Cursor ;

/* Variables and functions */
#define  FTS3_MATCHINFO_AVGLENGTH 135 
 char const FTS3_MATCHINFO_HITS ; 
#define  FTS3_MATCHINFO_LCS 134 
#define  FTS3_MATCHINFO_LENGTH 133 
#define  FTS3_MATCHINFO_LHITS 132 
#define  FTS3_MATCHINFO_LHITS_BM 131 
#define  FTS3_MATCHINFO_NCOL 130 
#define  FTS3_MATCHINFO_NDOC 129 
#define  FTS3_MATCHINFO_NPHRASE 128 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3ExprGlobalHitsCb ; 
 int fts3ExprIterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int fts3ExprLHitGather (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int fts3ExprLoadDoclists (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts3ExprLocalHitsCb ; 
 int fts3MatchinfoLcs (TYPE_3__*,TYPE_2__*) ; 
 int fts3MatchinfoSelectDoctotal (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,char const**) ; 
 int fts3MatchinfoSize (TYPE_2__*,char const) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sqlite3Fts3EvalTestDeferred (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  sqlite3Fts3GetVarint (char const*,int*) ; 
 int sqlite3Fts3SelectDocsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 char* sqlite3_column_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3MatchinfoValues(
  Fts3Cursor *pCsr,               /* FTS3 cursor object */
  int bGlobal,                    /* True to grab the global stats */
  MatchInfo *pInfo,               /* Matchinfo context object */
  const char *zArg                /* Matchinfo format string */
){
  int rc = SQLITE_OK;
  int i;
  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
  sqlite3_stmt *pSelect = 0;

  for(i=0; rc==SQLITE_OK && zArg[i]; i++){
    pInfo->flag = zArg[i];
    switch( zArg[i] ){
      case FTS3_MATCHINFO_NPHRASE:
        if( bGlobal ) pInfo->aMatchinfo[0] = pInfo->nPhrase;
        break;

      case FTS3_MATCHINFO_NCOL:
        if( bGlobal ) pInfo->aMatchinfo[0] = pInfo->nCol;
        break;
        
      case FTS3_MATCHINFO_NDOC:
        if( bGlobal ){
          sqlite3_int64 nDoc = 0;
          rc = fts3MatchinfoSelectDoctotal(pTab, &pSelect, &nDoc, 0);
          pInfo->aMatchinfo[0] = (u32)nDoc;
        }
        break;

      case FTS3_MATCHINFO_AVGLENGTH: 
        if( bGlobal ){
          sqlite3_int64 nDoc;     /* Number of rows in table */
          const char *a;          /* Aggregate column length array */

          rc = fts3MatchinfoSelectDoctotal(pTab, &pSelect, &nDoc, &a);
          if( rc==SQLITE_OK ){
            int iCol;
            for(iCol=0; iCol<pInfo->nCol; iCol++){
              u32 iVal;
              sqlite3_int64 nToken;
              a += sqlite3Fts3GetVarint(a, &nToken);
              iVal = (u32)(((u32)(nToken&0xffffffff)+nDoc/2)/nDoc);
              pInfo->aMatchinfo[iCol] = iVal;
            }
          }
        }
        break;

      case FTS3_MATCHINFO_LENGTH: {
        sqlite3_stmt *pSelectDocsize = 0;
        rc = sqlite3Fts3SelectDocsize(pTab, pCsr->iPrevId, &pSelectDocsize);
        if( rc==SQLITE_OK ){
          int iCol;
          const char *a = sqlite3_column_blob(pSelectDocsize, 0);
          for(iCol=0; iCol<pInfo->nCol; iCol++){
            sqlite3_int64 nToken;
            a += sqlite3Fts3GetVarint(a, &nToken);
            pInfo->aMatchinfo[iCol] = (u32)nToken;
          }
        }
        sqlite3_reset(pSelectDocsize);
        break;
      }

      case FTS3_MATCHINFO_LCS:
        rc = fts3ExprLoadDoclists(pCsr, 0, 0);
        if( rc==SQLITE_OK ){
          rc = fts3MatchinfoLcs(pCsr, pInfo);
        }
        break;

      case FTS3_MATCHINFO_LHITS_BM:
      case FTS3_MATCHINFO_LHITS: {
        size_t nZero = fts3MatchinfoSize(pInfo, zArg[i]) * sizeof(u32);
        memset(pInfo->aMatchinfo, 0, nZero);
        rc = fts3ExprLHitGather(pCsr->pExpr, pInfo);
        break;
      }

      default: {
        Fts3Expr *pExpr;
        assert( zArg[i]==FTS3_MATCHINFO_HITS );
        pExpr = pCsr->pExpr;
        rc = fts3ExprLoadDoclists(pCsr, 0, 0);
        if( rc!=SQLITE_OK ) break;
        if( bGlobal ){
          if( pCsr->pDeferred ){
            rc = fts3MatchinfoSelectDoctotal(pTab, &pSelect, &pInfo->nDoc, 0);
            if( rc!=SQLITE_OK ) break;
          }
          rc = fts3ExprIterate(pExpr, fts3ExprGlobalHitsCb,(void*)pInfo);
          sqlite3Fts3EvalTestDeferred(pCsr, &rc);
          if( rc!=SQLITE_OK ) break;
        }
        (void)fts3ExprIterate(pExpr, fts3ExprLocalHitsCb,(void*)pInfo);
        break;
      }
    }

    pInfo->aMatchinfo += fts3MatchinfoSize(pInfo, zArg[i]);
  }

  sqlite3_reset(pSelect);
  return rc;
}