#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_16__ {int iPhrase; TYPE_6__* pPhrase; } ;
struct TYPE_12__ {char* pList; } ;
struct TYPE_15__ {int iColumn; TYPE_3__ doclist; } ;
struct TYPE_14__ {int nColumn; } ;
struct TYPE_13__ {scalar_t__ flag; int nCol; int* aMatchinfo; TYPE_2__* pCursor; } ;
struct TYPE_10__ {scalar_t__ pVtab; } ;
struct TYPE_11__ {TYPE_1__ base; } ;
typedef  TYPE_4__ MatchInfo ;
typedef  TYPE_5__ Fts3Table ;
typedef  TYPE_6__ Fts3Phrase ;
typedef  TYPE_7__ Fts3Expr ;

/* Variables and functions */
 scalar_t__ FTS3_MATCHINFO_LHITS ; 
 scalar_t__ FTS3_MATCHINFO_LHITS_BM ; 
 int FTS_CORRUPT_VTAB ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3ColumnlistCount (char**) ; 
 int /*<<< orphan*/  fts3GetVarint32 (char*,int*) ; 

__attribute__((used)) static int fts3ExprLHits(
  Fts3Expr *pExpr,                /* Phrase expression node */
  MatchInfo *p                    /* Matchinfo context */
){
  Fts3Table *pTab = (Fts3Table *)p->pCursor->base.pVtab;
  int iStart;
  Fts3Phrase *pPhrase = pExpr->pPhrase;
  char *pIter = pPhrase->doclist.pList;
  int iCol = 0;

  assert( p->flag==FTS3_MATCHINFO_LHITS_BM || p->flag==FTS3_MATCHINFO_LHITS );
  if( p->flag==FTS3_MATCHINFO_LHITS ){
    iStart = pExpr->iPhrase * p->nCol;
  }else{
    iStart = pExpr->iPhrase * ((p->nCol + 31) / 32);
  }

  while( 1 ){
    int nHit = fts3ColumnlistCount(&pIter);
    if( (pPhrase->iColumn>=pTab->nColumn || pPhrase->iColumn==iCol) ){
      if( p->flag==FTS3_MATCHINFO_LHITS ){
        p->aMatchinfo[iStart + iCol] = (u32)nHit;
      }else if( nHit ){
        p->aMatchinfo[iStart + (iCol+1)/32] |= (1 << (iCol&0x1F));
      }
    }
    assert( *pIter==0x00 || *pIter==0x01 );
    if( *pIter!=0x01 ) break;
    pIter++;
    pIter += fts3GetVarint32(pIter, &iCol);
    if( iCol>=p->nCol ) return FTS_CORRUPT_VTAB;
  }
  return SQLITE_OK;
}