#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sSrc ;
typedef  int /*<<< orphan*/  sNC ;
struct TYPE_10__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_2__ Table ;
struct TYPE_11__ {int nSrc; int ncFlags; struct TYPE_11__* pSrcList; int /*<<< orphan*/ * pParse; TYPE_1__* a; } ;
struct TYPE_9__ {int iCursor; TYPE_2__* pTab; int /*<<< orphan*/  zName; } ;
typedef  TYPE_3__ SrcList ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_3__ NameContext ;
typedef  int /*<<< orphan*/  ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int NC_IdxExpr ; 
 int NC_IsCheck ; 
 int NC_PartIdx ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3ResolveExprListNames (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int sqlite3ResolveExprNames (TYPE_3__*,int /*<<< orphan*/ *) ; 

int sqlite3ResolveSelfReference(
  Parse *pParse,      /* Parsing context */
  Table *pTab,        /* The table being referenced, or NULL */
  int type,           /* NC_IsCheck or NC_PartIdx or NC_IdxExpr, or 0 */
  Expr *pExpr,        /* Expression to resolve.  May be NULL. */
  ExprList *pList     /* Expression list to resolve.  May be NULL. */
){
  SrcList sSrc;                   /* Fake SrcList for pParse->pNewTable */
  NameContext sNC;                /* Name context for pParse->pNewTable */
  int rc;

  assert( type==0 || pTab!=0 );
  assert( type==NC_IsCheck || type==NC_PartIdx || type==NC_IdxExpr || pTab==0 );
  memset(&sNC, 0, sizeof(sNC));
  memset(&sSrc, 0, sizeof(sSrc));
  if( pTab ){
    sSrc.nSrc = 1;
    sSrc.a[0].zName = pTab->zName;
    sSrc.a[0].pTab = pTab;
    sSrc.a[0].iCursor = -1;
  }
  sNC.pParse = pParse;
  sNC.pSrcList = &sSrc;
  sNC.ncFlags = type;
  if( (rc = sqlite3ResolveExprNames(&sNC, pExpr))!=SQLITE_OK ) return rc;
  if( pList ) rc = sqlite3ResolveExprListNames(&sNC, pList);
  return rc;
}