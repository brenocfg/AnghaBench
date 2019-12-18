#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int sqlite3_int64 ;
struct TYPE_3__ {int* aPage; } ;
typedef  TYPE_1__ GState ;

/* Variables and functions */

__attribute__((used)) static sqlite3_int64 ofstVarint(GState *p, int *pOfst){
  sqlite3_int64 x = 0;
  u8 *a = &p->aPage[*pOfst];
  int n = 0;
  while( n<8 && (a[0] & 0x80)!=0 ){
    x = (x<<7) + (a[0] & 0x7f);
    n++;
    a++;
  }
  if( n==8 ){
    x = (x<<8) + a[0];
  }else{
    x = (x<<7) + a[0];
  }
  *pOfst += (n+1);
  return x;
}