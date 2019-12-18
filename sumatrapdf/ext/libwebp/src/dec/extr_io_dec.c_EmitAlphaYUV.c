#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int a_stride; int /*<<< orphan*/ * a; } ;
typedef  TYPE_3__ WebPYUVABuffer ;
struct TYPE_11__ {TYPE_2__* output; } ;
typedef  TYPE_4__ WebPDecParams ;
struct TYPE_12__ {int mb_w; int mb_h; int mb_y; int /*<<< orphan*/  width; int /*<<< orphan*/ * a; } ;
typedef  TYPE_5__ VP8Io ;
struct TYPE_8__ {TYPE_3__ YUVA; } ;
struct TYPE_9__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  FillAlphaPlane (int /*<<< orphan*/ *,int const,int const,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int const) ; 

__attribute__((used)) static int EmitAlphaYUV(const VP8Io* const io, WebPDecParams* const p,
                        int expected_num_lines_out) {
  const uint8_t* alpha = io->a;
  const WebPYUVABuffer* const buf = &p->output->u.YUVA;
  const int mb_w = io->mb_w;
  const int mb_h = io->mb_h;
  uint8_t* dst = buf->a + io->mb_y * buf->a_stride;
  int j;
  (void)expected_num_lines_out;
  assert(expected_num_lines_out == mb_h);
  if (alpha != NULL) {
    for (j = 0; j < mb_h; ++j) {
      memcpy(dst, alpha, mb_w * sizeof(*dst));
      alpha += io->width;
      dst += buf->a_stride;
    }
  } else if (buf->a != NULL) {
    // the user requested alpha, but there is none, set it to opaque.
    FillAlphaPlane(dst, mb_w, mb_h, buf->a_stride);
  }
  return 0;
}