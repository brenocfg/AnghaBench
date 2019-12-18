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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  lsm_db ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  treeShmalloc (int /*<<< orphan*/ *,int,int,int*) ; 
 void* treeShmptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *treeShmallocZero(lsm_db *pDb, int nByte, u32 *piPtr, int *pRc){
  u32 iPtr;
  void *p;
  iPtr = treeShmalloc(pDb, 1, nByte, pRc);
  p = treeShmptr(pDb, iPtr);
  if( p ){
    assert( *pRc==LSM_OK );
    memset(p, 0, nByte);
    *piPtr = iPtr;
  }
  return p;
}