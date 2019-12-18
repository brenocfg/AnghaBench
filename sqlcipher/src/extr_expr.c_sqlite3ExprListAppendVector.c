#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  mallocFailed; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_34__ {scalar_t__ op; int iTable; struct TYPE_34__* pRight; } ;
struct TYPE_33__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_32__ {int nId; TYPE_1__* a; } ;
struct TYPE_31__ {TYPE_3__* db; } ;
struct TYPE_29__ {TYPE_7__* pExpr; scalar_t__ zName; } ;
struct TYPE_28__ {scalar_t__ zName; } ;
typedef  TYPE_4__ Parse ;
typedef  TYPE_5__ IdList ;
typedef  TYPE_6__ ExprList ;
typedef  TYPE_7__ Expr ;

/* Variables and functions */
 scalar_t__ ALWAYS (int) ; 
 scalar_t__ IN_RENAME_OBJECT ; 
 scalar_t__ NEVER (int) ; 
 scalar_t__ TK_SELECT ; 
 scalar_t__ TK_SELECT_COLUMN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_4__*,char*,int,int) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_3__*,TYPE_7__*) ; 
 TYPE_7__* sqlite3ExprForVectorField (TYPE_4__*,TYPE_7__*,int) ; 
 TYPE_6__* sqlite3ExprListAppend (TYPE_4__*,TYPE_6__*,TYPE_7__*) ; 
 int sqlite3ExprVectorSize (TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3IdListDelete (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3RenameExprUnmap (TYPE_4__*,TYPE_7__*) ; 

ExprList *sqlite3ExprListAppendVector(
  Parse *pParse,         /* Parsing context */
  ExprList *pList,       /* List to which to append. Might be NULL */
  IdList *pColumns,      /* List of names of LHS of the assignment */
  Expr *pExpr            /* Vector expression to be appended. Might be NULL */
){
  sqlite3 *db = pParse->db;
  int n;
  int i;
  int iFirst = pList ? pList->nExpr : 0;
  /* pColumns can only be NULL due to an OOM but an OOM will cause an
  ** exit prior to this routine being invoked */
  if( NEVER(pColumns==0) ) goto vector_append_error;
  if( pExpr==0 ) goto vector_append_error;

  /* If the RHS is a vector, then we can immediately check to see that 
  ** the size of the RHS and LHS match.  But if the RHS is a SELECT, 
  ** wildcards ("*") in the result set of the SELECT must be expanded before
  ** we can do the size check, so defer the size check until code generation.
  */
  if( pExpr->op!=TK_SELECT && pColumns->nId!=(n=sqlite3ExprVectorSize(pExpr)) ){
    sqlite3ErrorMsg(pParse, "%d columns assigned %d values",
                    pColumns->nId, n);
    goto vector_append_error;
  }

  for(i=0; i<pColumns->nId; i++){
    Expr *pSubExpr = sqlite3ExprForVectorField(pParse, pExpr, i);
    pList = sqlite3ExprListAppend(pParse, pList, pSubExpr);
    if( pList ){
      assert( pList->nExpr==iFirst+i+1 );
      pList->a[pList->nExpr-1].zName = pColumns->a[i].zName;
      pColumns->a[i].zName = 0;
    }
  }

  if( !db->mallocFailed && pExpr->op==TK_SELECT && ALWAYS(pList!=0) ){
    Expr *pFirst = pList->a[iFirst].pExpr;
    assert( pFirst!=0 );
    assert( pFirst->op==TK_SELECT_COLUMN );
     
    /* Store the SELECT statement in pRight so it will be deleted when
    ** sqlite3ExprListDelete() is called */
    pFirst->pRight = pExpr;
    pExpr = 0;

    /* Remember the size of the LHS in iTable so that we can check that
    ** the RHS and LHS sizes match during code generation. */
    pFirst->iTable = pColumns->nId;
  }

vector_append_error:
  if( IN_RENAME_OBJECT ){
    sqlite3RenameExprUnmap(pParse, pExpr);
  }
  sqlite3ExprDelete(db, pExpr);
  sqlite3IdListDelete(db, pColumns);
  return pList;
}