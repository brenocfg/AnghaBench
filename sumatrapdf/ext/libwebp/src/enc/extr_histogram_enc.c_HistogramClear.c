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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int palette_code_bits_; int /*<<< orphan*/ * literal_; } ;
typedef  TYPE_1__ VP8LHistogram ;

/* Variables and functions */
 int VP8LGetHistogramSize (int const) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void HistogramClear(VP8LHistogram* const p) {
  uint32_t* const literal = p->literal_;
  const int cache_bits = p->palette_code_bits_;
  const int histo_size = VP8LGetHistogramSize(cache_bits);
  memset(p, 0, histo_size);
  p->palette_code_bits_ = cache_bits;
  p->literal_ = literal;
}