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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_4__ {int /*<<< orphan*/  pReadRowid; } ;
typedef  int /*<<< orphan*/  RtreeNode ;
typedef  TYPE_1__ Rtree ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int nodeAcquire (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int findLeafNode(
  Rtree *pRtree,              /* RTree to search */
  i64 iRowid,                 /* The rowid searching for */
  RtreeNode **ppLeaf,         /* Write the node here */
  sqlite3_int64 *piNode       /* Write the node-id here */
){
  int rc;
  *ppLeaf = 0;
  sqlite3_bind_int64(pRtree->pReadRowid, 1, iRowid);
  if( sqlite3_step(pRtree->pReadRowid)==SQLITE_ROW ){
    i64 iNode = sqlite3_column_int64(pRtree->pReadRowid, 0);
    if( piNode ) *piNode = iNode;
    rc = nodeAcquire(pRtree, iNode, 0, ppLeaf);
    sqlite3_reset(pRtree->pReadRowid);
  }else{
    rc = sqlite3_reset(pRtree->pReadRowid);
  }
  return rc;
}