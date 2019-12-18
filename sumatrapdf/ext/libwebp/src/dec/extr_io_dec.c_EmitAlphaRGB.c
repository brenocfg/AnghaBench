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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int const stride; int /*<<< orphan*/ * rgba; } ;
typedef  TYPE_3__ WebPRGBABuffer ;
struct TYPE_12__ {TYPE_2__* output; } ;
typedef  TYPE_4__ WebPDecParams ;
typedef  scalar_t__ WEBP_CSP_MODE ;
struct TYPE_13__ {int mb_w; int /*<<< orphan*/  width; int /*<<< orphan*/ * a; } ;
typedef  TYPE_5__ VP8Io ;
struct TYPE_9__ {TYPE_3__ RGBA; } ;
struct TYPE_10__ {scalar_t__ colorspace; TYPE_1__ u; } ;

/* Variables and functions */
 int GetAlphaSourceRow (TYPE_5__ const* const,int /*<<< orphan*/  const**,int*) ; 
 scalar_t__ const MODE_ARGB ; 
 scalar_t__ const MODE_Argb ; 
 int /*<<< orphan*/  WebPApplyAlphaMultiply (int /*<<< orphan*/ * const,int const,int const,int,int const) ; 
 int WebPDispatchAlpha (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int const,int,int /*<<< orphan*/ * const,int const) ; 
 scalar_t__ WebPIsPremultipliedMode (scalar_t__ const) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int EmitAlphaRGB(const VP8Io* const io, WebPDecParams* const p,
                        int expected_num_lines_out) {
  const uint8_t* alpha = io->a;
  if (alpha != NULL) {
    const int mb_w = io->mb_w;
    const WEBP_CSP_MODE colorspace = p->output->colorspace;
    const int alpha_first =
        (colorspace == MODE_ARGB || colorspace == MODE_Argb);
    const WebPRGBABuffer* const buf = &p->output->u.RGBA;
    int num_rows;
    const int start_y = GetAlphaSourceRow(io, &alpha, &num_rows);
    uint8_t* const base_rgba = buf->rgba + start_y * buf->stride;
    uint8_t* const dst = base_rgba + (alpha_first ? 0 : 3);
    const int has_alpha = WebPDispatchAlpha(alpha, io->width, mb_w,
                                            num_rows, dst, buf->stride);
    (void)expected_num_lines_out;
    assert(expected_num_lines_out == num_rows);
    // has_alpha is true if there's non-trivial alpha to premultiply with.
    if (has_alpha && WebPIsPremultipliedMode(colorspace)) {
      WebPApplyAlphaMultiply(base_rgba, alpha_first,
                             mb_w, num_rows, buf->stride);
    }
  }
  return 0;
}