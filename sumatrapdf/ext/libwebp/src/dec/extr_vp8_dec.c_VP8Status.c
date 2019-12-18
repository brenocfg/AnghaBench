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
typedef  int /*<<< orphan*/  VP8StatusCode ;
struct TYPE_3__ {int /*<<< orphan*/  status_; } ;
typedef  TYPE_1__ VP8Decoder ;

/* Variables and functions */
 int /*<<< orphan*/  VP8_STATUS_INVALID_PARAM ; 

VP8StatusCode VP8Status(VP8Decoder* const dec) {
  if (!dec) return VP8_STATUS_INVALID_PARAM;
  return dec->status_;
}