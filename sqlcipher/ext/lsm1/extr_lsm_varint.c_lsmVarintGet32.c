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
typedef  int u8 ;
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int lsmSqlite4GetVarint64 (int*,scalar_t__*) ; 

int lsmVarintGet32(u8 *z, int *piVal){
  u64 i;
  int ret;

  if( z[0]<=240 ){
    *piVal = z[0];
    return 1;
  }
  if( z[0]<=248 ){
    *piVal = (z[0]-241)*256 + z[1] + 240;
    return 2;
  }
  if( z[0]==249 ){
    *piVal = 2288 + 256*z[1] + z[2];
    return 3;
  }
  if( z[0]==250 ){
    *piVal = (z[1]<<16) + (z[2]<<8) + z[3];
    return 4;
  }

  ret = lsmSqlite4GetVarint64(z, &i);
  *piVal = (int)i;
  return ret;
}