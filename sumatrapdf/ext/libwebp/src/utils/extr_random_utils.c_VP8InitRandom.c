#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int index2_; int amp_; scalar_t__ index1_; int /*<<< orphan*/  tab_; } ;
typedef  TYPE_1__ VP8Random ;

/* Variables and functions */
 int VP8_RANDOM_DITHER_FIX ; 
 int /*<<< orphan*/  kRandomTable ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void VP8InitRandom(VP8Random* const rg, float dithering) {
  memcpy(rg->tab_, kRandomTable, sizeof(rg->tab_));
  rg->index1_ = 0;
  rg->index2_ = 31;
  rg->amp_ = (dithering < 0.0) ? 0
           : (dithering > 1.0) ? (1 << VP8_RANDOM_DITHER_FIX)
           : (uint32_t)((1 << VP8_RANDOM_DITHER_FIX) * dithering);
}