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

__attribute__((used)) static void putRecordSize(u8 *aBuf, int nByte, int bFree){
  aBuf[0] = (u8)(nByte >> 14) | 0x80;
  aBuf[1] = ((u8)(nByte >>  7) & 0x7F) | (bFree ? 0x00 : 0x80);
  aBuf[2] = (u8)nByte | 0x80;
}