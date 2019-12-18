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
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sNC ;
typedef  int /*<<< orphan*/  sCol ;
struct TYPE_31__ {TYPE_10__* pUpsertIdx; TYPE_9__* pUpsertTargetWhere; TYPE_11__* pUpsertTarget; } ;
typedef  TYPE_6__ Upsert ;
struct TYPE_32__ {TYPE_10__* pIndex; } ;
typedef  TYPE_7__ Table ;
struct TYPE_27__ {char* zToken; } ;
struct TYPE_34__ {scalar_t__ op; scalar_t__ iColumn; int iTable; struct TYPE_34__* pLeft; TYPE_2__ u; TYPE_8__* pSrcList; int /*<<< orphan*/ * pParse; } ;
struct TYPE_33__ {int nSrc; TYPE_1__* a; } ;
struct TYPE_30__ {TYPE_9__* pExpr; } ;
struct TYPE_29__ {int nExpr; TYPE_3__* a; } ;
struct TYPE_28__ {TYPE_9__* pExpr; } ;
struct TYPE_26__ {int iCursor; TYPE_7__* pTab; } ;
struct TYPE_25__ {int nExpr; TYPE_5__* a; } ;
struct TYPE_24__ {int nKeyCol; scalar_t__* aiColumn; TYPE_4__* aColExpr; scalar_t__* azColl; TYPE_9__* pPartIdxWhere; struct TYPE_24__* pNext; } ;
typedef  TYPE_8__ SrcList ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_9__ NameContext ;
typedef  TYPE_10__ Index ;
typedef  TYPE_11__ ExprList ;
typedef  TYPE_9__ Expr ;

/* Variables and functions */
 scalar_t__ HasRowid (TYPE_7__*) ; 
 int /*<<< orphan*/  IsUniqueIndex (TYPE_10__*) ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 scalar_t__ TK_COLLATE ; 
 scalar_t__ TK_COLUMN ; 
 scalar_t__ XN_EXPR ; 
 scalar_t__ XN_ROWID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (int /*<<< orphan*/ *,char*) ; 
 int sqlite3ExprCompare (int /*<<< orphan*/ *,TYPE_9__*,TYPE_9__*,int) ; 
 int sqlite3ResolveExprListNames (TYPE_9__*,TYPE_11__*) ; 
 int sqlite3ResolveExprNames (TYPE_9__*,TYPE_9__*) ; 

int sqlite3UpsertAnalyzeTarget(
  Parse *pParse,     /* The parsing context */
  SrcList *pTabList, /* Table into which we are inserting */
  Upsert *pUpsert    /* The ON CONFLICT clauses */
){
  Table *pTab;            /* That table into which we are inserting */
  int rc;                 /* Result code */
  int iCursor;            /* Cursor used by pTab */
  Index *pIdx;            /* One of the indexes of pTab */
  ExprList *pTarget;      /* The conflict-target clause */
  Expr *pTerm;            /* One term of the conflict-target clause */
  NameContext sNC;        /* Context for resolving symbolic names */
  Expr sCol[2];           /* Index column converted into an Expr */

  assert( pTabList->nSrc==1 );
  assert( pTabList->a[0].pTab!=0 );
  assert( pUpsert!=0 );
  assert( pUpsert->pUpsertTarget!=0 );

  /* Resolve all symbolic names in the conflict-target clause, which
  ** includes both the list of columns and the optional partial-index
  ** WHERE clause.
  */
  memset(&sNC, 0, sizeof(sNC));
  sNC.pParse = pParse;
  sNC.pSrcList = pTabList;
  rc = sqlite3ResolveExprListNames(&sNC, pUpsert->pUpsertTarget);
  if( rc ) return rc;
  rc = sqlite3ResolveExprNames(&sNC, pUpsert->pUpsertTargetWhere);
  if( rc ) return rc;

  /* Check to see if the conflict target matches the rowid. */  
  pTab = pTabList->a[0].pTab;
  pTarget = pUpsert->pUpsertTarget;
  iCursor = pTabList->a[0].iCursor;
  if( HasRowid(pTab) 
   && pTarget->nExpr==1
   && (pTerm = pTarget->a[0].pExpr)->op==TK_COLUMN
   && pTerm->iColumn==XN_ROWID
  ){
    /* The conflict-target is the rowid of the primary table */
    assert( pUpsert->pUpsertIdx==0 );
    return SQLITE_OK;
  }

  /* Initialize sCol[0..1] to be an expression parse tree for a
  ** single column of an index.  The sCol[0] node will be the TK_COLLATE
  ** operator and sCol[1] will be the TK_COLUMN operator.  Code below
  ** will populate the specific collation and column number values
  ** prior to comparing against the conflict-target expression.
  */
  memset(sCol, 0, sizeof(sCol));
  sCol[0].op = TK_COLLATE;
  sCol[0].pLeft = &sCol[1];
  sCol[1].op = TK_COLUMN;
  sCol[1].iTable = pTabList->a[0].iCursor;

  /* Check for matches against other indexes */
  for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
    int ii, jj, nn;
    if( !IsUniqueIndex(pIdx) ) continue;
    if( pTarget->nExpr!=pIdx->nKeyCol ) continue;
    if( pIdx->pPartIdxWhere ){
      if( pUpsert->pUpsertTargetWhere==0 ) continue;
      if( sqlite3ExprCompare(pParse, pUpsert->pUpsertTargetWhere,
                             pIdx->pPartIdxWhere, iCursor)!=0 ){
        continue;
      }
    }
    nn = pIdx->nKeyCol;
    for(ii=0; ii<nn; ii++){
      Expr *pExpr;
      sCol[0].u.zToken = (char*)pIdx->azColl[ii];
      if( pIdx->aiColumn[ii]==XN_EXPR ){
        assert( pIdx->aColExpr!=0 );
        assert( pIdx->aColExpr->nExpr>ii );
        pExpr = pIdx->aColExpr->a[ii].pExpr;
        if( pExpr->op!=TK_COLLATE ){
          sCol[0].pLeft = pExpr;
          pExpr = &sCol[0];
        }
      }else{
        sCol[0].pLeft = &sCol[1];
        sCol[1].iColumn = pIdx->aiColumn[ii];
        pExpr = &sCol[0];
      }
      for(jj=0; jj<nn; jj++){
        if( sqlite3ExprCompare(pParse, pTarget->a[jj].pExpr, pExpr,iCursor)<2 ){
          break;  /* Column ii of the index matches column jj of target */
        }
      }
      if( jj>=nn ){
        /* The target contains no match for column jj of the index */
        break;
      }
    }
    if( ii<nn ){
      /* Column ii of the index did not match any term of the conflict target.
      ** Continue the search with the next index. */
      continue;
    }
    pUpsert->pUpsertIdx = pIdx;
    return SQLITE_OK;
  }
  sqlite3ErrorMsg(pParse, "ON CONFLICT clause does not match any "
                          "PRIMARY KEY or UNIQUE constraint");
  return SQLITE_ERROR;
}