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
typedef  int u32 ;
typedef  size_t u16 ;

/* Variables and functions */
 size_t NHASH ; 

__attribute__((used)) static u32 hash_once(const char *z){
  u16 a, b, i;
  a = b = z[0];
  for(i=1; i<NHASH; i++){
    a += z[i];
    b += a;
  }
  return a | (((u32)b)<<16);
}