#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* pRewrite; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pSub; TYPE_1__ u; int /*<<< orphan*/  xSelectCallback; int /*<<< orphan*/  xExprCallback; int /*<<< orphan*/ * pParse; int /*<<< orphan*/ * pSrc; int /*<<< orphan*/ * pWin; } ;
typedef  TYPE_2__ WindowRewrite ;
typedef  int /*<<< orphan*/  Window ;
typedef  TYPE_2__ Walker ;
typedef  int /*<<< orphan*/  SrcList ;
typedef  int /*<<< orphan*/  Parse ;
typedef  int /*<<< orphan*/  ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  selectWindowRewriteExprCb ; 
 int /*<<< orphan*/  selectWindowRewriteSelectCb ; 
 int /*<<< orphan*/  sqlite3WalkExprList (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void selectWindowRewriteEList(
  Parse *pParse, 
  Window *pWin,
  SrcList *pSrc,
  ExprList *pEList,               /* Rewrite expressions in this list */
  ExprList **ppSub                /* IN/OUT: Sub-select expression-list */
){
  Walker sWalker;
  WindowRewrite sRewrite;

  memset(&sWalker, 0, sizeof(Walker));
  memset(&sRewrite, 0, sizeof(WindowRewrite));

  sRewrite.pSub = *ppSub;
  sRewrite.pWin = pWin;
  sRewrite.pSrc = pSrc;

  sWalker.pParse = pParse;
  sWalker.xExprCallback = selectWindowRewriteExprCb;
  sWalker.xSelectCallback = selectWindowRewriteSelectCb;
  sWalker.u.pRewrite = &sRewrite;

  (void)sqlite3WalkExprList(&sWalker, pEList);

  *ppSub = sRewrite.pSub;
}