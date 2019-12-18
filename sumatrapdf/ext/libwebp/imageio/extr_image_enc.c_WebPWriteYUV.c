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
struct TYPE_6__ {int /*<<< orphan*/  a_stride; int /*<<< orphan*/  v_stride; int /*<<< orphan*/  u_stride; int /*<<< orphan*/  y_stride; int /*<<< orphan*/ * a; int /*<<< orphan*/ * v; int /*<<< orphan*/ * u; int /*<<< orphan*/ * y; } ;
typedef  TYPE_2__ WebPYUVABuffer ;
struct TYPE_5__ {TYPE_2__ YUVA; } ;
struct TYPE_7__ {int width; int height; TYPE_1__ u; } ;
typedef  TYPE_3__ WebPDecBuffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fwrite (int /*<<< orphan*/  const*,int const,int,int /*<<< orphan*/ *) ; 

int WebPWriteYUV(FILE* fout, const WebPDecBuffer* const buffer) {
  if (fout == NULL || buffer == NULL) {
    return 0;
  } else {
    const int width = buffer->width;
    const int height = buffer->height;
    const WebPYUVABuffer* const yuv = &buffer->u.YUVA;
    const uint8_t* src_y = yuv->y;
    const uint8_t* src_u = yuv->u;
    const uint8_t* src_v = yuv->v;
    const uint8_t* src_a = yuv->a;
    const int uv_width = (width + 1) / 2;
    const int uv_height = (height + 1) / 2;
    const int a_height = (src_a != NULL) ? height : 0;
    int ok = 1;
    int y;

    if (src_y == NULL || src_u == NULL || src_v == NULL) return 0;

    for (y = 0; ok && y < height; ++y) {
      ok &= (fwrite(src_y, width, 1, fout) == 1);
      src_y += yuv->y_stride;
    }
    for (y = 0; ok && y < uv_height; ++y) {
      ok &= (fwrite(src_u, uv_width, 1, fout) == 1);
      src_u += yuv->u_stride;
    }
    for (y = 0; ok && y < uv_height; ++y) {
      ok &= (fwrite(src_v, uv_width, 1, fout) == 1);
      src_v += yuv->v_stride;
    }
    for (y = 0; ok && y < a_height; ++y) {
      ok &= (fwrite(src_a, width, 1, fout) == 1);
      src_a += yuv->a_stride;
    }
    return ok;
  }
}