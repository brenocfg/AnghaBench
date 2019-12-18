#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mb_y_; int /*<<< orphan*/  filter_row_; } ;
struct TYPE_6__ {int tl_mb_x_; int br_mb_x_; TYPE_1__ thread_ctx_; } ;
typedef  TYPE_2__ VP8Decoder ;

/* Variables and functions */
 int /*<<< orphan*/  DoFilter (TYPE_2__ const* const,int,int const) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void FilterRow(const VP8Decoder* const dec) {
  int mb_x;
  const int mb_y = dec->thread_ctx_.mb_y_;
  assert(dec->thread_ctx_.filter_row_);
  for (mb_x = dec->tl_mb_x_; mb_x < dec->br_mb_x_; ++mb_x) {
    DoFilter(dec, mb_x, mb_y);
  }
}