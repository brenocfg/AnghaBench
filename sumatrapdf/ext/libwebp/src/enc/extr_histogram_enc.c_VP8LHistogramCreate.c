#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int palette_code_bits_; } ;
typedef  TYPE_1__ VP8LHistogram ;
typedef  int /*<<< orphan*/  VP8LBackwardRefs ;

/* Variables and functions */
 int /*<<< orphan*/  HistogramClear (TYPE_1__* const) ; 
 int /*<<< orphan*/  VP8LHistogramStoreRefs (int /*<<< orphan*/  const* const,TYPE_1__* const) ; 

void VP8LHistogramCreate(VP8LHistogram* const p,
                         const VP8LBackwardRefs* const refs,
                         int palette_code_bits) {
  if (palette_code_bits >= 0) {
    p->palette_code_bits_ = palette_code_bits;
  }
  HistogramClear(p);
  VP8LHistogramStoreRefs(refs, p);
}