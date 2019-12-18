#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int simple_; scalar_t__ i4x4_lf_delta_; scalar_t__ sharpness_; scalar_t__ level_; } ;
struct TYPE_4__ {TYPE_2__ filter_hdr_; } ;
typedef  TYPE_1__ VP8Encoder ;
typedef  TYPE_2__ VP8EncFilterHeader ;

/* Variables and functions */

__attribute__((used)) static void ResetFilterHeader(VP8Encoder* const enc) {
  VP8EncFilterHeader* const hdr = &enc->filter_hdr_;
  hdr->simple_ = 1;
  hdr->level_ = 0;
  hdr->sharpness_ = 0;
  hdr->i4x4_lf_delta_ = 0;
}