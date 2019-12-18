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
typedef  int sqlite3_uint64 ;

/* Variables and functions */

__attribute__((used)) static int fuzzGetVarint(u8 *p, int *pnVal){
  int i;
  sqlite3_uint64 nVal = 0;
  for(i=0; i<9; i++){
    nVal = (nVal<<7) + (p[i] & 0x7F);
    if( (p[i] & 0x80)==0 ){
      i++;
      break;
    }
  }
  *pnVal = (int)nVal;
  return i;
}