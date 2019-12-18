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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static void ckptChecksum(u32 *aCkpt, u32 nCkpt, u32 *piCksum1, u32 *piCksum2){
  u32 i;
  u32 cksum1 = 1;
  u32 cksum2 = 2;

  if( nCkpt % 2 ){
    cksum1 += aCkpt[nCkpt-3] & 0x0000FFFF;
    cksum2 += aCkpt[nCkpt-3] & 0xFFFF0000;
  }

  for(i=0; (i+3)<nCkpt; i+=2){
    cksum1 += cksum2 + aCkpt[i];
    cksum2 += cksum1 + aCkpt[i+1];
  }

  *piCksum1 = cksum1;
  *piCksum2 = cksum2;
}