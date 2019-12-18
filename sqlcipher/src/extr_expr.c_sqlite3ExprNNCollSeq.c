#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* db; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pDfltColl; } ;
typedef  TYPE_2__ Parse ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * sqlite3ExprCollSeq (TYPE_2__*,int /*<<< orphan*/ *) ; 

CollSeq *sqlite3ExprNNCollSeq(Parse *pParse, Expr *pExpr){
  CollSeq *p = sqlite3ExprCollSeq(pParse, pExpr);
  if( p==0 ) p = pParse->db->pDfltColl;
  assert( p!=0 );
  return p;
}