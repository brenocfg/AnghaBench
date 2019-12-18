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
struct TYPE_9__ {int stride; int /*<<< orphan*/ * rgba; } ;
typedef  TYPE_2__ WebPRGBABuffer ;
struct TYPE_10__ {TYPE_4__* output; } ;
typedef  TYPE_3__ WebPDecParams ;
struct TYPE_8__ {TYPE_2__ RGBA; } ;
struct TYPE_11__ {size_t colorspace; TYPE_1__ u; } ;
typedef  TYPE_4__ WebPDecBuffer ;
struct TYPE_12__ {int mb_y; int mb_h; int /*<<< orphan*/  mb_w; int /*<<< orphan*/  uv_stride; int /*<<< orphan*/  v; int /*<<< orphan*/  u; int /*<<< orphan*/  y_stride; int /*<<< orphan*/  y; } ;
typedef  TYPE_5__ VP8Io ;

/* Variables and functions */
 int /*<<< orphan*/  WebPSamplerProcessPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ * const,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WebPSamplers ; 

__attribute__((used)) static int EmitSampledRGB(const VP8Io* const io, WebPDecParams* const p) {
  WebPDecBuffer* const output = p->output;
  WebPRGBABuffer* const buf = &output->u.RGBA;
  uint8_t* const dst = buf->rgba + io->mb_y * buf->stride;
  WebPSamplerProcessPlane(io->y, io->y_stride,
                          io->u, io->v, io->uv_stride,
                          dst, buf->stride, io->mb_w, io->mb_h,
                          WebPSamplers[output->colorspace]);
  return io->mb_h;
}