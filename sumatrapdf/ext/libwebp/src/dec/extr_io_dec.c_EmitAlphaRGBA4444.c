#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_11__ {int* rgba; int const stride; } ;
typedef  TYPE_3__ WebPRGBABuffer ;
struct TYPE_12__ {TYPE_2__* output; } ;
typedef  TYPE_4__ WebPDecParams ;
typedef  int /*<<< orphan*/  WEBP_CSP_MODE ;
struct TYPE_13__ {int* a; int mb_w; int /*<<< orphan*/  width; } ;
typedef  TYPE_5__ VP8Io ;
struct TYPE_9__ {TYPE_3__ RGBA; } ;
struct TYPE_10__ {TYPE_1__ u; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int GetAlphaSourceRow (TYPE_5__ const* const,int const**,int*) ; 
 int /*<<< orphan*/  WebPApplyAlphaMultiply4444 (int* const,int const,int,int const) ; 
 scalar_t__ WebPIsPremultipliedMode (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int EmitAlphaRGBA4444(const VP8Io* const io, WebPDecParams* const p,
                             int expected_num_lines_out) {
  const uint8_t* alpha = io->a;
  if (alpha != NULL) {
    const int mb_w = io->mb_w;
    const WEBP_CSP_MODE colorspace = p->output->colorspace;
    const WebPRGBABuffer* const buf = &p->output->u.RGBA;
    int num_rows;
    const int start_y = GetAlphaSourceRow(io, &alpha, &num_rows);
    uint8_t* const base_rgba = buf->rgba + start_y * buf->stride;
#if (WEBP_SWAP_16BIT_CSP == 1)
    uint8_t* alpha_dst = base_rgba;
#else
    uint8_t* alpha_dst = base_rgba + 1;
#endif
    uint32_t alpha_mask = 0x0f;
    int i, j;
    for (j = 0; j < num_rows; ++j) {
      for (i = 0; i < mb_w; ++i) {
        // Fill in the alpha value (converted to 4 bits).
        const uint32_t alpha_value = alpha[i] >> 4;
        alpha_dst[2 * i] = (alpha_dst[2 * i] & 0xf0) | alpha_value;
        alpha_mask &= alpha_value;
      }
      alpha += io->width;
      alpha_dst += buf->stride;
    }
    (void)expected_num_lines_out;
    assert(expected_num_lines_out == num_rows);
    if (alpha_mask != 0x0f && WebPIsPremultipliedMode(colorspace)) {
      WebPApplyAlphaMultiply4444(base_rgba, mb_w, num_rows, buf->stride);
    }
  }
  return 0;
}