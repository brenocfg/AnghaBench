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

void sqlite3Fts5Put32(u8 *aBuf, int iVal){
  aBuf[0] = (iVal>>24) & 0x00FF;
  aBuf[1] = (iVal>>16) & 0x00FF;
  aBuf[2] = (iVal>> 8) & 0x00FF;
  aBuf[3] = (iVal>> 0) & 0x00FF;
}