#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int prereqRight; int eOperator; } ;
typedef  TYPE_1__ WhereTerm ;
typedef  int /*<<< orphan*/  WhereScan ;
typedef  int /*<<< orphan*/  WhereClause ;
typedef  int /*<<< orphan*/  Index ;
typedef  int Bitmask ;

/* Variables and functions */
 int WO_EQ ; 
 int WO_IS ; 
 int /*<<< orphan*/  testcase (int) ; 
 TYPE_1__* whereScanInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* whereScanNext (int /*<<< orphan*/ *) ; 

WhereTerm *sqlite3WhereFindTerm(
  WhereClause *pWC,     /* The WHERE clause to be searched */
  int iCur,             /* Cursor number of LHS */
  int iColumn,          /* Column number of LHS */
  Bitmask notReady,     /* RHS must not overlap with this mask */
  u32 op,               /* Mask of WO_xx values describing operator */
  Index *pIdx           /* Must be compatible with this index, if not NULL */
){
  WhereTerm *pResult = 0;
  WhereTerm *p;
  WhereScan scan;

  p = whereScanInit(&scan, pWC, iCur, iColumn, op, pIdx);
  op &= WO_EQ|WO_IS;
  while( p ){
    if( (p->prereqRight & notReady)==0 ){
      if( p->prereqRight==0 && (p->eOperator&op)!=0 ){
        testcase( p->eOperator & WO_IS );
        return p;
      }
      if( pResult==0 ) pResult = p;
    }
    p = whereScanNext(&scan);
  }
  return pResult;
}