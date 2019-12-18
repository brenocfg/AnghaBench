#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {scalar_t__ const y_size; scalar_t__ const u_size; scalar_t__ const v_size; scalar_t__ const a_size; int /*<<< orphan*/ * a; int /*<<< orphan*/ * v; int /*<<< orphan*/ * u; int /*<<< orphan*/ * y; int /*<<< orphan*/  a_stride; int /*<<< orphan*/  v_stride; int /*<<< orphan*/  u_stride; int /*<<< orphan*/  y_stride; } ;
typedef  TYPE_2__ WebPYUVABuffer ;
struct TYPE_8__ {scalar_t__ const size; int /*<<< orphan*/ * rgba; int /*<<< orphan*/  stride; } ;
typedef  TYPE_3__ WebPRGBABuffer ;
struct TYPE_6__ {TYPE_3__ RGBA; TYPE_2__ YUVA; } ;
struct TYPE_9__ {size_t colorspace; int width; int height; TYPE_1__ u; } ;
typedef  TYPE_4__ WebPDecBuffer ;
typedef  size_t WEBP_CSP_MODE ;
typedef  int /*<<< orphan*/  VP8StatusCode ;

/* Variables and functions */
 int /*<<< orphan*/  IsValidColorspace (size_t const) ; 
 scalar_t__ MIN_BUFFER_SIZE (int const,int const,int const) ; 
 size_t const MODE_YUVA ; 
 int /*<<< orphan*/  VP8_STATUS_INVALID_PARAM ; 
 int /*<<< orphan*/  VP8_STATUS_OK ; 
 int /*<<< orphan*/  WebPIsRGBMode (size_t const) ; 
 int abs (int /*<<< orphan*/ ) ; 
 int const* kModeBpp ; 

__attribute__((used)) static VP8StatusCode CheckDecBuffer(const WebPDecBuffer* const buffer) {
  int ok = 1;
  const WEBP_CSP_MODE mode = buffer->colorspace;
  const int width = buffer->width;
  const int height = buffer->height;
  if (!IsValidColorspace(mode)) {
    ok = 0;
  } else if (!WebPIsRGBMode(mode)) {   // YUV checks
    const WebPYUVABuffer* const buf = &buffer->u.YUVA;
    const int uv_width  = (width  + 1) / 2;
    const int uv_height = (height + 1) / 2;
    const int y_stride = abs(buf->y_stride);
    const int u_stride = abs(buf->u_stride);
    const int v_stride = abs(buf->v_stride);
    const int a_stride = abs(buf->a_stride);
    const uint64_t y_size = MIN_BUFFER_SIZE(width, height, y_stride);
    const uint64_t u_size = MIN_BUFFER_SIZE(uv_width, uv_height, u_stride);
    const uint64_t v_size = MIN_BUFFER_SIZE(uv_width, uv_height, v_stride);
    const uint64_t a_size = MIN_BUFFER_SIZE(width, height, a_stride);
    ok &= (y_size <= buf->y_size);
    ok &= (u_size <= buf->u_size);
    ok &= (v_size <= buf->v_size);
    ok &= (y_stride >= width);
    ok &= (u_stride >= uv_width);
    ok &= (v_stride >= uv_width);
    ok &= (buf->y != NULL);
    ok &= (buf->u != NULL);
    ok &= (buf->v != NULL);
    if (mode == MODE_YUVA) {
      ok &= (a_stride >= width);
      ok &= (a_size <= buf->a_size);
      ok &= (buf->a != NULL);
    }
  } else {    // RGB checks
    const WebPRGBABuffer* const buf = &buffer->u.RGBA;
    const int stride = abs(buf->stride);
    const uint64_t size =
        MIN_BUFFER_SIZE(width * kModeBpp[mode], height, stride);
    ok &= (size <= buf->size);
    ok &= (stride >= width * kModeBpp[mode]);
    ok &= (buf->rgba != NULL);
  }
  return ok ? VP8_STATUS_OK : VP8_STATUS_INVALID_PARAM;
}