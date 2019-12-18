#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct SrcList_item {int /*<<< orphan*/  iCursor; } ;
struct ExprList_item {TYPE_12__* pExpr; } ;
struct AggInfo_func {int iDistinct; int /*<<< orphan*/  pFunc; int /*<<< orphan*/  iMem; TYPE_12__* pExpr; } ;
struct AggInfo_col {int iSorterColumn; TYPE_12__* pExpr; int /*<<< orphan*/  iMem; int /*<<< orphan*/  iColumn; int /*<<< orphan*/  iTable; int /*<<< orphan*/  pTab; } ;
typedef  void* i16 ;
struct TYPE_26__ {TYPE_10__* pNC; } ;
struct TYPE_32__ {int /*<<< orphan*/  walkerDepth; TYPE_1__ u; } ;
typedef  TYPE_7__ Walker ;
struct TYPE_34__ {int /*<<< orphan*/  nTab; int /*<<< orphan*/  db; int /*<<< orphan*/  nMem; } ;
struct TYPE_33__ {int nSrc; struct SrcList_item* a; } ;
struct TYPE_31__ {TYPE_5__* pList; } ;
struct TYPE_30__ {int /*<<< orphan*/  nExpr; } ;
struct TYPE_29__ {int /*<<< orphan*/  zToken; } ;
struct TYPE_28__ {int /*<<< orphan*/  pTab; } ;
struct TYPE_27__ {TYPE_13__* pAggInfo; } ;
struct TYPE_25__ {int nColumn; int nFunc; struct AggInfo_func* aFunc; int /*<<< orphan*/  nSortingColumn; TYPE_11__* pGroupBy; struct AggInfo_col* aCol; } ;
struct TYPE_24__ {int op; int flags; TYPE_13__* pAggInfo; void* iAgg; TYPE_6__ x; TYPE_4__ u; int /*<<< orphan*/  op2; int /*<<< orphan*/  iColumn; int /*<<< orphan*/  iTable; TYPE_3__ y; } ;
struct TYPE_23__ {int nExpr; struct ExprList_item* a; } ;
struct TYPE_22__ {int ncFlags; TYPE_2__ uNC; TYPE_8__* pSrcList; TYPE_9__* pParse; } ;
typedef  TYPE_8__ SrcList ;
typedef  TYPE_9__ Parse ;
typedef  TYPE_10__ NameContext ;
typedef  TYPE_11__ ExprList ;
typedef  TYPE_12__ Expr ;
typedef  TYPE_13__ AggInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS (int) ; 
 int /*<<< orphan*/  ENC (int /*<<< orphan*/ ) ; 
 int EP_Distinct ; 
 int EP_IntValue ; 
 int /*<<< orphan*/  EP_NoReduce ; 
 int EP_Reduced ; 
 int EP_TokenOnly ; 
 int EP_xIsSelect ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_12__*,int) ; 
 int /*<<< orphan*/  ExprSetVVAProperty (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int NC_InAggFunc ; 
 int NC_UAggInfo ; 
#define  TK_AGG_COLUMN 130 
#define  TK_AGG_FUNCTION 129 
#define  TK_COLUMN 128 
 int WRC_Continue ; 
 int WRC_Prune ; 
 int addAggInfoColumn (int /*<<< orphan*/ ,TYPE_13__*) ; 
 int addAggInfoFunc (int /*<<< orphan*/ ,TYPE_13__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ExprCompare (int /*<<< orphan*/ ,TYPE_12__*,TYPE_12__*,int) ; 
 int /*<<< orphan*/  sqlite3FindFunction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int analyzeAggregate(Walker *pWalker, Expr *pExpr){
  int i;
  NameContext *pNC = pWalker->u.pNC;
  Parse *pParse = pNC->pParse;
  SrcList *pSrcList = pNC->pSrcList;
  AggInfo *pAggInfo = pNC->uNC.pAggInfo;

  assert( pNC->ncFlags & NC_UAggInfo );
  switch( pExpr->op ){
    case TK_AGG_COLUMN:
    case TK_COLUMN: {
      testcase( pExpr->op==TK_AGG_COLUMN );
      testcase( pExpr->op==TK_COLUMN );
      /* Check to see if the column is in one of the tables in the FROM
      ** clause of the aggregate query */
      if( ALWAYS(pSrcList!=0) ){
        struct SrcList_item *pItem = pSrcList->a;
        for(i=0; i<pSrcList->nSrc; i++, pItem++){
          struct AggInfo_col *pCol;
          assert( !ExprHasProperty(pExpr, EP_TokenOnly|EP_Reduced) );
          if( pExpr->iTable==pItem->iCursor ){
            /* If we reach this point, it means that pExpr refers to a table
            ** that is in the FROM clause of the aggregate query.  
            **
            ** Make an entry for the column in pAggInfo->aCol[] if there
            ** is not an entry there already.
            */
            int k;
            pCol = pAggInfo->aCol;
            for(k=0; k<pAggInfo->nColumn; k++, pCol++){
              if( pCol->iTable==pExpr->iTable &&
                  pCol->iColumn==pExpr->iColumn ){
                break;
              }
            }
            if( (k>=pAggInfo->nColumn)
             && (k = addAggInfoColumn(pParse->db, pAggInfo))>=0 
            ){
              pCol = &pAggInfo->aCol[k];
              pCol->pTab = pExpr->y.pTab;
              pCol->iTable = pExpr->iTable;
              pCol->iColumn = pExpr->iColumn;
              pCol->iMem = ++pParse->nMem;
              pCol->iSorterColumn = -1;
              pCol->pExpr = pExpr;
              if( pAggInfo->pGroupBy ){
                int j, n;
                ExprList *pGB = pAggInfo->pGroupBy;
                struct ExprList_item *pTerm = pGB->a;
                n = pGB->nExpr;
                for(j=0; j<n; j++, pTerm++){
                  Expr *pE = pTerm->pExpr;
                  if( pE->op==TK_COLUMN && pE->iTable==pExpr->iTable &&
                      pE->iColumn==pExpr->iColumn ){
                    pCol->iSorterColumn = j;
                    break;
                  }
                }
              }
              if( pCol->iSorterColumn<0 ){
                pCol->iSorterColumn = pAggInfo->nSortingColumn++;
              }
            }
            /* There is now an entry for pExpr in pAggInfo->aCol[] (either
            ** because it was there before or because we just created it).
            ** Convert the pExpr to be a TK_AGG_COLUMN referring to that
            ** pAggInfo->aCol[] entry.
            */
            ExprSetVVAProperty(pExpr, EP_NoReduce);
            pExpr->pAggInfo = pAggInfo;
            pExpr->op = TK_AGG_COLUMN;
            pExpr->iAgg = (i16)k;
            break;
          } /* endif pExpr->iTable==pItem->iCursor */
        } /* end loop over pSrcList */
      }
      return WRC_Prune;
    }
    case TK_AGG_FUNCTION: {
      if( (pNC->ncFlags & NC_InAggFunc)==0
       && pWalker->walkerDepth==pExpr->op2
      ){
        /* Check to see if pExpr is a duplicate of another aggregate 
        ** function that is already in the pAggInfo structure
        */
        struct AggInfo_func *pItem = pAggInfo->aFunc;
        for(i=0; i<pAggInfo->nFunc; i++, pItem++){
          if( sqlite3ExprCompare(0, pItem->pExpr, pExpr, -1)==0 ){
            break;
          }
        }
        if( i>=pAggInfo->nFunc ){
          /* pExpr is original.  Make a new entry in pAggInfo->aFunc[]
          */
          u8 enc = ENC(pParse->db);
          i = addAggInfoFunc(pParse->db, pAggInfo);
          if( i>=0 ){
            assert( !ExprHasProperty(pExpr, EP_xIsSelect) );
            pItem = &pAggInfo->aFunc[i];
            pItem->pExpr = pExpr;
            pItem->iMem = ++pParse->nMem;
            assert( !ExprHasProperty(pExpr, EP_IntValue) );
            pItem->pFunc = sqlite3FindFunction(pParse->db,
                   pExpr->u.zToken, 
                   pExpr->x.pList ? pExpr->x.pList->nExpr : 0, enc, 0);
            if( pExpr->flags & EP_Distinct ){
              pItem->iDistinct = pParse->nTab++;
            }else{
              pItem->iDistinct = -1;
            }
          }
        }
        /* Make pExpr point to the appropriate pAggInfo->aFunc[] entry
        */
        assert( !ExprHasProperty(pExpr, EP_TokenOnly|EP_Reduced) );
        ExprSetVVAProperty(pExpr, EP_NoReduce);
        pExpr->iAgg = (i16)i;
        pExpr->pAggInfo = pAggInfo;
        return WRC_Prune;
      }else{
        return WRC_Continue;
      }
    }
  }
  return WRC_Continue;
}