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

__attribute__((used)) static unsigned int randInt(void){
  static unsigned int x = 0x333a13cd;
  static unsigned int y = 0xecb2adea;
  x = (x>>1) ^ ((1+~(x&1)) & 0xd0000001);
  y = y*1103515245 + 12345;
  return x^y;
}