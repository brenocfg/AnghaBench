#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  nHeight; } ;
struct TYPE_7__ {scalar_t__ nErr; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  exprSetHeight (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3ExprCheckHeight (TYPE_1__*,int /*<<< orphan*/ ) ; 

void sqlite3ExprSetHeightAndFlags(Parse *pParse, Expr *p){
  if( pParse->nErr ) return;
  exprSetHeight(p);
  sqlite3ExprCheckHeight(pParse, p->nHeight);
}