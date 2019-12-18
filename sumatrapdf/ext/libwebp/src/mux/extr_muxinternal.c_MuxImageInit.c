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
typedef  int /*<<< orphan*/  WebPMuxImage ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 

void MuxImageInit(WebPMuxImage* const wpi) {
  assert(wpi);
  memset(wpi, 0, sizeof(*wpi));
}