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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int i64 ;

/* Variables and functions */
 int CKPT_HDR_ID_LSW ; 
 int CKPT_HDR_ID_MSW ; 
 scalar_t__ lsmGetU32 (int /*<<< orphan*/ *) ; 

i64 lsmCheckpointId(u32 *aCkpt, int bDisk){
  i64 iId;
  if( bDisk ){
    u8 *aData = (u8 *)aCkpt;
    iId = (((i64)lsmGetU32(&aData[CKPT_HDR_ID_MSW*4])) << 32);
    iId += ((i64)lsmGetU32(&aData[CKPT_HDR_ID_LSW*4]));
  }else{
    iId = ((i64)aCkpt[CKPT_HDR_ID_MSW] << 32) + (i64)aCkpt[CKPT_HDR_ID_LSW];
  }
  return iId;
}