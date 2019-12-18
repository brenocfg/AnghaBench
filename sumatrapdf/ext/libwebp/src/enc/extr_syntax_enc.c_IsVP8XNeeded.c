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
struct TYPE_3__ {int /*<<< orphan*/  has_alpha_; } ;
typedef  TYPE_1__ VP8Encoder ;

/* Variables and functions */

__attribute__((used)) static int IsVP8XNeeded(const VP8Encoder* const enc) {
  return !!enc->has_alpha_;  // Currently the only case when VP8X is needed.
                             // This could change in the future.
}