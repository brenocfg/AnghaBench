#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_3__ {int /*<<< orphan*/  iCell; } ;
typedef  TYPE_1__ RtreeSearchPoint ;
typedef  int /*<<< orphan*/  RtreeNode ;
typedef  int /*<<< orphan*/  RtreeCursor ;

/* Variables and functions */
 int /*<<< orphan*/  RTREE_OF_CURSOR (int /*<<< orphan*/ *) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  nodeGetRowid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rtreeNodeOfFirstSearchPoint (int /*<<< orphan*/ *,int*) ; 
 TYPE_1__* rtreeSearchPointFirst (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtreeRowid(sqlite3_vtab_cursor *pVtabCursor, sqlite_int64 *pRowid){
  RtreeCursor *pCsr = (RtreeCursor *)pVtabCursor;
  RtreeSearchPoint *p = rtreeSearchPointFirst(pCsr);
  int rc = SQLITE_OK;
  RtreeNode *pNode = rtreeNodeOfFirstSearchPoint(pCsr, &rc);
  if( rc==SQLITE_OK && p ){
    *pRowid = nodeGetRowid(RTREE_OF_CURSOR(pCsr), pNode, p->iCell);
  }
  return rc;
}