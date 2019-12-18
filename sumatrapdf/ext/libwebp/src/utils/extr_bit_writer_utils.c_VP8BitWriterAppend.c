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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int nb_bits_; scalar_t__ pos_; scalar_t__ buf_; } ;
typedef  TYPE_1__ VP8BitWriter ;

/* Variables and functions */
 int /*<<< orphan*/  BitWriterResize (TYPE_1__* const,size_t) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 

int VP8BitWriterAppend(VP8BitWriter* const bw,
                       const uint8_t* data, size_t size) {
  assert(data != NULL);
  if (bw->nb_bits_ != -8) return 0;   // Flush() must have been called
  if (!BitWriterResize(bw, size)) return 0;
  memcpy(bw->buf_ + bw->pos_, data, size);
  bw->pos_ += size;
  return 1;
}