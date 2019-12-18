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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {int stride; int /*<<< orphan*/ * rgba; } ;
typedef  TYPE_3__ WebPRGBABuffer ;
struct TYPE_11__ {TYPE_5__* scaler_a; TYPE_2__* output; } ;
typedef  TYPE_4__ WebPDecParams ;
typedef  scalar_t__ WEBP_CSP_MODE ;
struct TYPE_12__ {int dst_width; int /*<<< orphan*/  dst; } ;
struct TYPE_8__ {TYPE_3__ RGBA; } ;
struct TYPE_9__ {scalar_t__ colorspace; int height; TYPE_1__ u; } ;

/* Variables and functions */
 scalar_t__ const MODE_ARGB ; 
 scalar_t__ const MODE_Argb ; 
 int /*<<< orphan*/  WebPApplyAlphaMultiply (int /*<<< orphan*/ * const,int const,int const,int,int) ; 
 int /*<<< orphan*/  WebPDispatchAlpha (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int WebPIsPremultipliedMode (scalar_t__ const) ; 
 int /*<<< orphan*/  WebPRescalerExportRow (TYPE_5__*) ; 
 scalar_t__ WebPRescalerHasPendingOutput (TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int ExportAlpha(WebPDecParams* const p, int y_pos, int max_lines_out) {
  const WebPRGBABuffer* const buf = &p->output->u.RGBA;
  uint8_t* const base_rgba = buf->rgba + y_pos * buf->stride;
  const WEBP_CSP_MODE colorspace = p->output->colorspace;
  const int alpha_first =
      (colorspace == MODE_ARGB || colorspace == MODE_Argb);
  uint8_t* dst = base_rgba + (alpha_first ? 0 : 3);
  int num_lines_out = 0;
  const int is_premult_alpha = WebPIsPremultipliedMode(colorspace);
  uint32_t non_opaque = 0;
  const int width = p->scaler_a->dst_width;

  while (WebPRescalerHasPendingOutput(p->scaler_a) &&
         num_lines_out < max_lines_out) {
    assert(y_pos + num_lines_out < p->output->height);
    WebPRescalerExportRow(p->scaler_a);
    non_opaque |= WebPDispatchAlpha(p->scaler_a->dst, 0, width, 1, dst, 0);
    dst += buf->stride;
    ++num_lines_out;
  }
  if (is_premult_alpha && non_opaque) {
    WebPApplyAlphaMultiply(base_rgba, alpha_first,
                           width, num_lines_out, buf->stride);
  }
  return num_lines_out;
}