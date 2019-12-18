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
typedef  unsigned int u8 ;

/* Variables and functions */

__attribute__((used)) static unsigned int fts5HashKey(int nSlot, const u8 *p, int n){
  int i;
  unsigned int h = 13;
  for(i=n-1; i>=0; i--){
    h = (h << 3) ^ h ^ p[i];
  }
  return (h % nSlot);
}