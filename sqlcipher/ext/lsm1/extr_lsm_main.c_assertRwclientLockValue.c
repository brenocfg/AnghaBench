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
typedef  int u64 ;
struct TYPE_3__ {scalar_t__ iRwclient; int mLock; } ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 scalar_t__ LSM_LOCK_NRWCLIENT ; 
 int LSM_LOCK_RWCLIENT (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void assertRwclientLockValue(lsm_db *db){
#ifndef NDEBUG
  u64 msk;                        /* Mask of mLock bits for RWCLIENT locks */
  u64 rwclient = 0;               /* Bit corresponding to db->iRwclient */

  if( db->iRwclient>=0 ){
    rwclient = ((u64)1 << (LSM_LOCK_RWCLIENT(db->iRwclient)-1));
  }
  msk  = ((u64)1 << (LSM_LOCK_RWCLIENT(LSM_LOCK_NRWCLIENT)-1)) - 1;
  msk -= (((u64)1 << (LSM_LOCK_RWCLIENT(0)-1)) - 1);

  assert( (db->mLock & msk)==rwclient );
#endif
}