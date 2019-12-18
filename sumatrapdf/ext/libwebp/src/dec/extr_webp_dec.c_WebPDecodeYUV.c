#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int y_stride; int u_stride; int v_stride; int /*<<< orphan*/ * v; int /*<<< orphan*/ * u; } ;
typedef  TYPE_2__ WebPYUVABuffer ;
struct TYPE_5__ {TYPE_2__ YUVA; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
typedef  TYPE_3__ WebPDecBuffer ;

/* Variables and functions */
 int /*<<< orphan*/ * Decode (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int*,int*,TYPE_3__*) ; 
 int /*<<< orphan*/  MODE_YUV ; 
 int /*<<< orphan*/  assert (int) ; 

uint8_t* WebPDecodeYUV(const uint8_t* data, size_t data_size,
                       int* width, int* height, uint8_t** u, uint8_t** v,
                       int* stride, int* uv_stride) {
  WebPDecBuffer output;   // only to preserve the side-infos
  uint8_t* const out = Decode(MODE_YUV, data, data_size,
                              width, height, &output);

  if (out != NULL) {
    const WebPYUVABuffer* const buf = &output.u.YUVA;
    *u = buf->u;
    *v = buf->v;
    *stride = buf->y_stride;
    *uv_stride = buf->u_stride;
    assert(buf->u_stride == buf->v_stride);
  }
  return out;
}