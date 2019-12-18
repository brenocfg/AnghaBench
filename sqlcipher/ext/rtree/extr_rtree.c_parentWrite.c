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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_3__ {int /*<<< orphan*/  pWriteParent; } ;
typedef  TYPE_1__ Rtree ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parentWrite(Rtree *pRtree, sqlite3_int64 iNode, sqlite3_int64 iPar){
  sqlite3_bind_int64(pRtree->pWriteParent, 1, iNode);
  sqlite3_bind_int64(pRtree->pWriteParent, 2, iPar);
  sqlite3_step(pRtree->pWriteParent);
  return sqlite3_reset(pRtree->pWriteParent);
}