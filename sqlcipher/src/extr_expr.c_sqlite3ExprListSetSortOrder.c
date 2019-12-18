#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_5__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_4__ {scalar_t__ sortOrder; } ;
typedef  TYPE_2__ ExprList ;

/* Variables and functions */
 scalar_t__ SQLITE_SO_ASC ; 
 scalar_t__ SQLITE_SO_DESC ; 
 scalar_t__ SQLITE_SO_UNDEFINED ; 
 int /*<<< orphan*/  assert (int) ; 

void sqlite3ExprListSetSortOrder(ExprList *p, int iSortOrder){
  if( p==0 ) return;
  assert( SQLITE_SO_UNDEFINED<0 && SQLITE_SO_ASC>=0 && SQLITE_SO_DESC>0 );
  assert( p->nExpr>0 );
  if( iSortOrder<0 ){
    assert( p->a[p->nExpr-1].sortOrder==SQLITE_SO_ASC );
    return;
  }
  p->a[p->nExpr-1].sortOrder = (u8)iSortOrder;
}