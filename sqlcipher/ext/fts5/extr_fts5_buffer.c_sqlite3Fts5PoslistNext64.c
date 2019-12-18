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
typedef  int i64 ;

/* Variables and functions */
 int /*<<< orphan*/  fts5FastGetVarint32 (int /*<<< orphan*/  const*,int,int) ; 

int sqlite3Fts5PoslistNext64(
  const u8 *a, int n,             /* Buffer containing poslist */
  int *pi,                        /* IN/OUT: Offset within a[] */
  i64 *piOff                      /* IN/OUT: Current offset */
){
  int i = *pi;
  if( i>=n ){
    /* EOF */
    *piOff = -1;
    return 1;  
  }else{
    i64 iOff = *piOff;
    int iVal;
    fts5FastGetVarint32(a, i, iVal);
    if( iVal==1 ){
      fts5FastGetVarint32(a, i, iVal);
      iOff = ((i64)iVal) << 32;
      fts5FastGetVarint32(a, i, iVal);
    }
    *piOff = iOff + ((iVal-2) & 0x7FFFFFFF);
    *pi = i;
    return 0;
  }
}