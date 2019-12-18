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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 size_t CKPT_HDR_NWRITE ; 
 int /*<<< orphan*/  lsmGetU32 (int /*<<< orphan*/ *) ; 

u32 lsmCheckpointNWrite(u32 *aCkpt, int bDisk){
  if( bDisk ){
    return lsmGetU32((u8 *)&aCkpt[CKPT_HDR_NWRITE]);
  }else{
    return aCkpt[CKPT_HDR_NWRITE];
  }
}