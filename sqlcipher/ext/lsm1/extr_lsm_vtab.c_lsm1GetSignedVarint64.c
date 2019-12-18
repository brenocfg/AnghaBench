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
typedef  int sqlite3_uint64 ;
typedef  scalar_t__ sqlite3_int64 ;

/* Variables and functions */
 int lsm1GetVarint64 (unsigned char const*,int,int*) ; 

__attribute__((used)) static int lsm1GetSignedVarint64(
  const unsigned char *z,
  int n,
  sqlite3_int64 *pResult
){
  sqlite3_uint64 u = 0;
  n = lsm1GetVarint64(z, n, &u);
  if( u&1 ){
    *pResult = -1 - (sqlite3_int64)(u>>1);
  }else{
    *pResult = (sqlite3_int64)(u>>1);
  }
  return n;
}