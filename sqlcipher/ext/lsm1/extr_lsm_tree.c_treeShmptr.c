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
typedef  int u32 ;
struct TYPE_4__ {int* apShm; scalar_t__ nShm; } ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 void* treeShmptrUnsafe (TYPE_1__*,int) ; 

__attribute__((used)) static void *treeShmptr(lsm_db *pDb, u32 iPtr){

  assert( (iPtr>>15)<(u32)pDb->nShm );
  assert( pDb->apShm[iPtr>>15] );

  return iPtr ? treeShmptrUnsafe(pDb, iPtr) : 0;
}