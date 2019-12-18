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
struct TYPE_4__ {scalar_t__ eFrmType; scalar_t__ eStart; scalar_t__ eEnd; scalar_t__ eExclude; int /*<<< orphan*/  pOrderBy; int /*<<< orphan*/  pPartition; int /*<<< orphan*/  pEnd; int /*<<< orphan*/  pStart; } ;
typedef  TYPE_1__ Window ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 scalar_t__ sqlite3ExprCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3ExprListCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int sqlite3WindowCompare(Parse *pParse, Window *p1, Window *p2){
  if( p1->eFrmType!=p2->eFrmType ) return 1;
  if( p1->eStart!=p2->eStart ) return 1;
  if( p1->eEnd!=p2->eEnd ) return 1;
  if( p1->eExclude!=p2->eExclude ) return 1;
  if( sqlite3ExprCompare(pParse, p1->pStart, p2->pStart, -1) ) return 1;
  if( sqlite3ExprCompare(pParse, p1->pEnd, p2->pEnd, -1) ) return 1;
  if( sqlite3ExprListCompare(p1->pPartition, p2->pPartition, -1) ) return 1;
  if( sqlite3ExprListCompare(p1->pOrderBy, p2->pOrderBy, -1) ) return 1;
  return 0;
}