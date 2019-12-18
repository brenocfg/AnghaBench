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
struct TYPE_4__ {int range_; int nb_bits_; int /*<<< orphan*/ * buf_; scalar_t__ error_; scalar_t__ max_pos_; scalar_t__ pos_; scalar_t__ run_; scalar_t__ value_; } ;
typedef  TYPE_1__ VP8BitWriter ;

/* Variables and functions */
 int BitWriterResize (TYPE_1__* const,size_t) ; 

int VP8BitWriterInit(VP8BitWriter* const bw, size_t expected_size) {
  bw->range_   = 255 - 1;
  bw->value_   = 0;
  bw->run_     = 0;
  bw->nb_bits_ = -8;
  bw->pos_     = 0;
  bw->max_pos_ = 0;
  bw->error_   = 0;
  bw->buf_     = NULL;
  return (expected_size > 0) ? BitWriterResize(bw, expected_size) : 1;
}