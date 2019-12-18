#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * cur_pos; } ;
typedef  TYPE_1__ VP8LRefsCursor ;
struct TYPE_9__ {int /*<<< orphan*/ ** histograms; } ;
typedef  TYPE_2__ VP8LHistogramSet ;
typedef  int /*<<< orphan*/  VP8LHistogram ;
typedef  int /*<<< orphan*/  VP8LBackwardRefs ;
typedef  int /*<<< orphan*/  PixOrCopy ;

/* Variables and functions */
 scalar_t__ PixOrCopyLength (int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  VP8LHistogramAddSinglePixOrCopy (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP8LHistogramSetClear (TYPE_2__* const) ; 
 TYPE_1__ VP8LRefsCursorInit (int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  VP8LRefsCursorNext (TYPE_1__*) ; 
 scalar_t__ VP8LRefsCursorOk (TYPE_1__*) ; 
 int VP8LSubSampleSize (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void HistogramBuild(
    int xsize, int histo_bits, const VP8LBackwardRefs* const backward_refs,
    VP8LHistogramSet* const image_histo) {
  int x = 0, y = 0;
  const int histo_xsize = VP8LSubSampleSize(xsize, histo_bits);
  VP8LHistogram** const histograms = image_histo->histograms;
  VP8LRefsCursor c = VP8LRefsCursorInit(backward_refs);
  assert(histo_bits > 0);
  VP8LHistogramSetClear(image_histo);
  while (VP8LRefsCursorOk(&c)) {
    const PixOrCopy* const v = c.cur_pos;
    const int ix = (y >> histo_bits) * histo_xsize + (x >> histo_bits);
    VP8LHistogramAddSinglePixOrCopy(histograms[ix], v, NULL, 0);
    x += PixOrCopyLength(v);
    while (x >= xsize) {
      x -= xsize;
      ++y;
    }
    VP8LRefsCursorNext(&c);
  }
}