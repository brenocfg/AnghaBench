#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ iUsedShmid; } ;
struct TYPE_6__ {TYPE_1__ treehdr; } ;
typedef  TYPE_2__ lsm_db ;

/* Variables and functions */
 int LSM_OK ; 
 int isInUse (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int*) ; 

int lsmTreeInUse(lsm_db *db, u32 iShmid, int *pbInUse){
  if( db->treehdr.iUsedShmid==iShmid ){
    *pbInUse = 1;
    return LSM_OK;
  }
  return isInUse(db, 0, iShmid, pbInUse);
}