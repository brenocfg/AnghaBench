#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ uv_alpha; scalar_t__ alpha; scalar_t__* alphas; } ;
typedef  TYPE_1__ SegmentJob ;

/* Variables and functions */
 int MAX_ALPHA ; 

__attribute__((used)) static void MergeJobs(const SegmentJob* const src, SegmentJob* const dst) {
  int i;
  for (i = 0; i <= MAX_ALPHA; ++i) dst->alphas[i] += src->alphas[i];
  dst->alpha += src->alpha;
  dst->uv_alpha += src->uv_alpha;
}