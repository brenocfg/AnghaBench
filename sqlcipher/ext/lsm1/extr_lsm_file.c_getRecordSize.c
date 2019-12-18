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

/* Variables and functions */

__attribute__((used)) static int getRecordSize(u8 *aBuf, int *pbFree){
  int nByte;
  nByte  = (aBuf[0] & 0x7F) << 14;
  nByte += (aBuf[1] & 0x7F) << 7;
  nByte += (aBuf[2] & 0x7F);
  *pbFree = !(aBuf[1] & 0x80);
  return nByte;
}