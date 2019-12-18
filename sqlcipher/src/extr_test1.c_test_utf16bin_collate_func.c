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

/* Variables and functions */
 int memcmp (void const*,void const*,int) ; 

__attribute__((used)) static int test_utf16bin_collate_func(
  void *pCtx, 
  int nA, const void *zA,
  int nB, const void *zB
){
  int nCmp = (nA>nB ? nB : nA);
  int res = memcmp(zA, zB, nCmp);
  if( res==0 ) res = nA - nB;
  return res;
}