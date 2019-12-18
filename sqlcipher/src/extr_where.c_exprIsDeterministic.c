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
typedef  int /*<<< orphan*/  w ;
struct TYPE_4__ {int eCode; int /*<<< orphan*/  xSelectCallback; int /*<<< orphan*/  xExprCallback; } ;
typedef  TYPE_1__ Walker ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  exprNodeIsDeterministic ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3SelectWalkFail ; 
 int /*<<< orphan*/  sqlite3WalkExpr (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exprIsDeterministic(Expr *p){
  Walker w;
  memset(&w, 0, sizeof(w));
  w.eCode = 1;
  w.xExprCallback = exprNodeIsDeterministic;
  w.xSelectCallback = sqlite3SelectWalkFail;
  sqlite3WalkExpr(&w, p);
  return w.eCode;
}