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
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  RtreeNode ;
typedef  int /*<<< orphan*/  Rtree ;

/* Variables and functions */
 int NCELL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTREE_IS_CORRUPT (int /*<<< orphan*/ *) ; 
 int SQLITE_CORRUPT_VTAB ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ nodeGetRowid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nodeRowidIndex(
  Rtree *pRtree, 
  RtreeNode *pNode, 
  i64 iRowid,
  int *piIndex
){
  int ii;
  int nCell = NCELL(pNode);
  assert( nCell<200 );
  for(ii=0; ii<nCell; ii++){
    if( nodeGetRowid(pRtree, pNode, ii)==iRowid ){
      *piIndex = ii;
      return SQLITE_OK;
    }
  }
  RTREE_IS_CORRUPT(pRtree);
  return SQLITE_CORRUPT_VTAB;
}