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
typedef  int /*<<< orphan*/  WebPUpsampleLinePairFunc ;

/* Variables and functions */
 int /*<<< orphan*/  DualLineSamplerARGB ; 
 int /*<<< orphan*/  DualLineSamplerBGRA ; 
 size_t MODE_ARGB ; 
 size_t MODE_BGRA ; 
 int /*<<< orphan*/  WebPInitUpsamplers () ; 
 int /*<<< orphan*/ * WebPUpsamplers ; 

WebPUpsampleLinePairFunc WebPGetLinePairConverter(int alpha_is_last) {
  WebPInitUpsamplers();
#ifdef FANCY_UPSAMPLING
  return WebPUpsamplers[alpha_is_last ? MODE_BGRA : MODE_ARGB];
#else
  return (alpha_is_last ? DualLineSamplerBGRA : DualLineSamplerARGB);
#endif
}