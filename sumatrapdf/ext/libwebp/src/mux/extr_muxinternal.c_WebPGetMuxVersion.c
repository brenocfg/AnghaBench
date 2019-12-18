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
 int MUX_MAJ_VERSION ; 
 int MUX_MIN_VERSION ; 
 int MUX_REV_VERSION ; 

int WebPGetMuxVersion(void) {
  return (MUX_MAJ_VERSION << 16) | (MUX_MIN_VERSION << 8) | MUX_REV_VERSION;
}