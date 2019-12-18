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
typedef  int /*<<< orphan*/  WhereMaskSet ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  Bitmask ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3WhereExprUsageNN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Bitmask sqlite3WhereExprUsage(WhereMaskSet *pMaskSet, Expr *p){
  return p ? sqlite3WhereExprUsageNN(pMaskSet,p) : 0;
}