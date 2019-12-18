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
struct TYPE_9__ {int y_stride; int u_stride; int v_stride; int /*<<< orphan*/ * v; int /*<<< orphan*/ * u; int /*<<< orphan*/ * y; } ;
typedef  TYPE_2__ WebPYUVABuffer ;
struct TYPE_10__ {TYPE_4__* output; } ;
typedef  TYPE_3__ WebPDecParams ;
struct TYPE_8__ {TYPE_2__ YUVA; } ;
struct TYPE_11__ {TYPE_1__ u; } ;
typedef  TYPE_4__ WebPDecBuffer ;
struct TYPE_12__ {int mb_y; int mb_w; int mb_h; int y_stride; int uv_stride; scalar_t__ v; scalar_t__ u; scalar_t__ y; } ;
typedef  TYPE_5__ VP8Io ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ * const,scalar_t__,int const) ; 

__attribute__((used)) static int EmitYUV(const VP8Io* const io, WebPDecParams* const p) {
  WebPDecBuffer* output = p->output;
  const WebPYUVABuffer* const buf = &output->u.YUVA;
  uint8_t* const y_dst = buf->y + io->mb_y * buf->y_stride;
  uint8_t* const u_dst = buf->u + (io->mb_y >> 1) * buf->u_stride;
  uint8_t* const v_dst = buf->v + (io->mb_y >> 1) * buf->v_stride;
  const int mb_w = io->mb_w;
  const int mb_h = io->mb_h;
  const int uv_w = (mb_w + 1) / 2;
  const int uv_h = (mb_h + 1) / 2;
  int j;
  for (j = 0; j < mb_h; ++j) {
    memcpy(y_dst + j * buf->y_stride, io->y + j * io->y_stride, mb_w);
  }
  for (j = 0; j < uv_h; ++j) {
    memcpy(u_dst + j * buf->u_stride, io->u + j * io->uv_stride, uv_w);
    memcpy(v_dst + j * buf->v_stride, io->v + j * io->uv_stride, uv_w);
  }
  return io->mb_h;
}