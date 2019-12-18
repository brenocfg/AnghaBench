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
typedef  int /*<<< orphan*/  VP8LHistogramSet ;

/* Variables and functions */
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ * const) ; 

void VP8LFreeHistogramSet(VP8LHistogramSet* const histo) {
  WebPSafeFree(histo);
}