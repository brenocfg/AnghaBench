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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static int lsmSqlite4GetVarint64(const unsigned char *z, u64 *pResult){
  unsigned int x;
  if( z[0]<=240 ){
    *pResult = z[0];
    return 1;
  }
  if( z[0]<=248 ){
    *pResult = (z[0]-241)*256 + z[1] + 240;
    return 2;
  }
  if( z[0]==249 ){
    *pResult = 2288 + 256*z[1] + z[2];
    return 3;
  }
  if( z[0]==250 ){
    *pResult = (z[1]<<16) + (z[2]<<8) + z[3];
    return 4;
  }
  x = (z[1]<<24) + (z[2]<<16) + (z[3]<<8) + z[4];
  if( z[0]==251 ){
    *pResult = x;
    return 5;
  }
  if( z[0]==252 ){
    *pResult = (((u64)x)<<8) + z[5];
    return 6;
  }
  if( z[0]==253 ){
    *pResult = (((u64)x)<<16) + (z[5]<<8) + z[6];
    return 7;
  }
  if( z[0]==254 ){
    *pResult = (((u64)x)<<24) + (z[5]<<16) + (z[6]<<8) + z[7];
    return 8;
  }
  *pResult = (((u64)x)<<32) +
               (0xffffffff & ((z[5]<<24) + (z[6]<<16) + (z[7]<<8) + z[8]));
  return 9;
}