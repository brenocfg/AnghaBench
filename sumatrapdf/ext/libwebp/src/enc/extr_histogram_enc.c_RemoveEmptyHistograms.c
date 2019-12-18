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
typedef  int uint32_t ;
struct TYPE_3__ {int size; int /*<<< orphan*/ ** histograms; } ;
typedef  TYPE_1__ VP8LHistogramSet ;

/* Variables and functions */

__attribute__((used)) static void RemoveEmptyHistograms(VP8LHistogramSet* const image_histo) {
  uint32_t size;
  int i;
  for (i = 0, size = 0; i < image_histo->size; ++i) {
    if (image_histo->histograms[i] == NULL) continue;
    image_histo->histograms[size++] = image_histo->histograms[i];
  }
  image_histo->size = size;
}