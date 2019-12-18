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
struct TYPE_4__ {int palette_code_bits_; int bit_cost_; int literal_cost_; int red_cost_; int blue_cost_; int /*<<< orphan*/  is_used_; scalar_t__ trivial_symbol_; } ;
typedef  TYPE_1__ VP8LHistogram ;

/* Variables and functions */
 int /*<<< orphan*/  HistogramClear (TYPE_1__* const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void VP8LHistogramInit(VP8LHistogram* const p, int palette_code_bits,
                       int init_arrays) {
  p->palette_code_bits_ = palette_code_bits;
  if (init_arrays) {
    HistogramClear(p);
  } else {
    p->trivial_symbol_ = 0;
    p->bit_cost_ = 0.;
    p->literal_cost_ = 0.;
    p->red_cost_ = 0.;
    p->blue_cost_ = 0.;
    memset(p->is_used_, 0, sizeof(p->is_used_));
  }
}