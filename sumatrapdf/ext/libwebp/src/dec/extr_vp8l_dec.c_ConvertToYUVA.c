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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int y_stride; int u_stride; int v_stride; int a_stride; int /*<<< orphan*/ * a; int /*<<< orphan*/ * v; int /*<<< orphan*/ * u; scalar_t__ y; } ;
typedef  TYPE_2__ WebPYUVABuffer ;
struct TYPE_5__ {TYPE_2__ YUVA; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
typedef  TYPE_3__ WebPDecBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  WebPConvertARGBToUV (int /*<<< orphan*/  const* const,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int,int) ; 
 int /*<<< orphan*/  WebPConvertARGBToY (int /*<<< orphan*/  const* const,scalar_t__,int) ; 
 int /*<<< orphan*/  WebPExtractAlpha (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ConvertToYUVA(const uint32_t* const src, int width, int y_pos,
                          const WebPDecBuffer* const output) {
  const WebPYUVABuffer* const buf = &output->u.YUVA;

  // first, the luma plane
  WebPConvertARGBToY(src, buf->y + y_pos * buf->y_stride, width);

  // then U/V planes
  {
    uint8_t* const u = buf->u + (y_pos >> 1) * buf->u_stride;
    uint8_t* const v = buf->v + (y_pos >> 1) * buf->v_stride;
    // even lines: store values
    // odd lines: average with previous values
    WebPConvertARGBToUV(src, u, v, width, !(y_pos & 1));
  }
  // Lastly, store alpha if needed.
  if (buf->a != NULL) {
    uint8_t* const a = buf->a + y_pos * buf->a_stride;
#if defined(WORDS_BIGENDIAN)
    WebPExtractAlpha((uint8_t*)src + 0, 0, width, 1, a, 0);
#else
    WebPExtractAlpha((uint8_t*)src + 3, 0, width, 1, a, 0);
#endif
  }
}