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
struct TYPE_3__ {int type_; scalar_t__ alpha_; scalar_t__ segment_; scalar_t__ skip_; scalar_t__ uv_mode_; } ;
typedef  TYPE_1__ VP8MBInfo ;

/* Variables and functions */

__attribute__((used)) static void DefaultMBInfo(VP8MBInfo* const mb) {
  mb->type_ = 1;     // I16x16
  mb->uv_mode_ = 0;
  mb->skip_ = 0;     // not skipped
  mb->segment_ = 0;  // default segment
  mb->alpha_ = 0;
}