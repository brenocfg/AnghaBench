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
 int DMUX_MAJ_VERSION ; 
 int DMUX_MIN_VERSION ; 
 int DMUX_REV_VERSION ; 

int WebPGetDemuxVersion(void) {
  return (DMUX_MAJ_VERSION << 16) | (DMUX_MIN_VERSION << 8) | DMUX_REV_VERSION;
}