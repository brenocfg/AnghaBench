#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  xExprCallback; int /*<<< orphan*/ * pParse; } ;
typedef  TYPE_1__ Walker ;
typedef  int /*<<< orphan*/  Parse ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  renameUnmapExprCb ; 
 int /*<<< orphan*/  sqlite3WalkExpr (TYPE_1__*,int /*<<< orphan*/ *) ; 

void sqlite3RenameExprUnmap(Parse *pParse, Expr *pExpr){
  Walker sWalker;
  memset(&sWalker, 0, sizeof(Walker));
  sWalker.pParse = pParse;
  sWalker.xExprCallback = renameUnmapExprCb;
  sqlite3WalkExpr(&sWalker, pExpr);
}