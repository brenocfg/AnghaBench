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
typedef  int /*<<< orphan*/  const uint32_t ;
typedef  int /*<<< orphan*/  VP8LTransform ;
struct TYPE_3__ {int next_transform_; int width_; int /*<<< orphan*/ * transforms_; int /*<<< orphan*/  const* argb_cache_; } ;
typedef  TYPE_1__ VP8LDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  VP8LInverseTransform (int /*<<< orphan*/ * const,int,int const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const*,int const) ; 

__attribute__((used)) static void ApplyInverseTransforms(VP8LDecoder* const dec,
                                   int start_row, int num_rows,
                                   const uint32_t* const rows) {
  int n = dec->next_transform_;
  const int cache_pixs = dec->width_ * num_rows;
  const int end_row = start_row + num_rows;
  const uint32_t* rows_in = rows;
  uint32_t* const rows_out = dec->argb_cache_;

  // Inverse transforms.
  while (n-- > 0) {
    VP8LTransform* const transform = &dec->transforms_[n];
    VP8LInverseTransform(transform, start_row, end_row, rows_in, rows_out);
    rows_in = rows_out;
  }
  if (rows_in != rows_out) {
    // No transform called, hence just copy.
    memcpy(rows_out, rows_in, cache_pixs * sizeof(*rows_out));
  }
}