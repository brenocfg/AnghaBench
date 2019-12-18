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
typedef  int u16 ;

/* Variables and functions */

void lsmPutU16(u8 *aOut, u16 nVal){
  aOut[0] = (u8)((nVal>>8) & 0xFF);
  aOut[1] = (u8)(nVal & 0xFF);
}