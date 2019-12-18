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
typedef  scalar_t__ u8 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 zipfileGetU32(const u8 *aBuf){
  return ((u32)(aBuf[3]) << 24)
       + ((u32)(aBuf[2]) << 16)
       + ((u32)(aBuf[1]) <<  8)
       + ((u32)(aBuf[0]) <<  0);
}