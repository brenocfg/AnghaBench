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
typedef  int sqlite3_uint64 ;
typedef  int sqlite3_int64 ;

/* Variables and functions */
 int lsm1PutVarint64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lsm1PutSignedVarint64(u8 *z, sqlite3_int64 v){
  sqlite3_uint64 u;
  if( v>=0 ){
    u = (sqlite3_uint64)v;
    return lsm1PutVarint64(z, u*2);
  }else{
    u = (sqlite3_uint64)(-1-v);
    return lsm1PutVarint64(z, u*2+1);
  }
}