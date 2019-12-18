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
struct TYPE_3__ {int /*<<< orphan*/  keyframe_; int /*<<< orphan*/  best_delta_; scalar_t__ flush_count_; scalar_t__ count_; scalar_t__ start_; } ;
typedef  TYPE_1__ WebPAnimEncoder ;

/* Variables and functions */
 int /*<<< orphan*/  DELTA_INFINITY ; 
 int /*<<< orphan*/  KEYFRAME_NONE ; 

__attribute__((used)) static void ResetCounters(WebPAnimEncoder* const enc) {
  enc->start_ = 0;
  enc->count_ = 0;
  enc->flush_count_ = 0;
  enc->best_delta_ = DELTA_INFINITY;
  enc->keyframe_ = KEYFRAME_NONE;
}