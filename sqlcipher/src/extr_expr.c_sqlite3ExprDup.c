#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int EXPRDUP_REDUCE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * exprDup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

Expr *sqlite3ExprDup(sqlite3 *db, Expr *p, int flags){
  assert( flags==0 || flags==EXPRDUP_REDUCE );
  return p ? exprDup(db, p, flags, 0) : 0;
}