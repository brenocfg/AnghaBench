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
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_3__ {int /*<<< orphan*/  buf_max_; int /*<<< orphan*/  buf_end_; int /*<<< orphan*/ * buf_; } ;
typedef  TYPE_1__ VP8BitReader ;

/* Variables and functions */

void VP8RemapBitReader(VP8BitReader* const br, ptrdiff_t offset) {
  if (br->buf_ != NULL) {
    br->buf_ += offset;
    br->buf_end_ += offset;
    br->buf_max_ += offset;
  }
}