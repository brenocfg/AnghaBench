#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int int64_t ;
struct TYPE_5__ {int y_stride; int uv_stride; int a_stride; int /*<<< orphan*/ * a; int /*<<< orphan*/ * v; int /*<<< orphan*/ * u; int /*<<< orphan*/ * y; void* memory_; scalar_t__ colorspace; } ;
typedef  TYPE_1__ WebPPicture ;
typedef  scalar_t__ WebPEncCSP ;

/* Variables and functions */
 int /*<<< orphan*/  VP8_ENC_ERROR_BAD_DIMENSION ; 
 int /*<<< orphan*/  VP8_ENC_ERROR_INVALID_CONFIGURATION ; 
 int /*<<< orphan*/  VP8_ENC_ERROR_OUT_OF_MEMORY ; 
 int WEBP_CSP_ALPHA_BIT ; 
 int WEBP_CSP_UV_MASK ; 
 scalar_t__ const WEBP_YUV420 ; 
 int WebPEncodingSetError (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPPictureResetBufferYUVA (TYPE_1__* const) ; 
 int /*<<< orphan*/  WebPSafeFree (void*) ; 
 scalar_t__ WebPSafeMalloc (int,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int WebPPictureAllocYUVA(WebPPicture* const picture, int width, int height) {
  const WebPEncCSP uv_csp =
      (WebPEncCSP)((int)picture->colorspace & WEBP_CSP_UV_MASK);
  const int has_alpha = (int)picture->colorspace & WEBP_CSP_ALPHA_BIT;
  const int y_stride = width;
  const int uv_width = (int)(((int64_t)width + 1) >> 1);
  const int uv_height = (int)(((int64_t)height + 1) >> 1);
  const int uv_stride = uv_width;
  int a_width, a_stride;
  uint64_t y_size, uv_size, a_size, total_size;
  uint8_t* mem;

  assert(picture != NULL);

  WebPSafeFree(picture->memory_);
  WebPPictureResetBufferYUVA(picture);

  if (uv_csp != WEBP_YUV420) {
    return WebPEncodingSetError(picture, VP8_ENC_ERROR_INVALID_CONFIGURATION);
  }

  // alpha
  a_width = has_alpha ? width : 0;
  a_stride = a_width;
  y_size = (uint64_t)y_stride * height;
  uv_size = (uint64_t)uv_stride * uv_height;
  a_size =  (uint64_t)a_stride * height;

  total_size = y_size + a_size + 2 * uv_size;

  // Security and validation checks
  if (width <= 0 || height <= 0 ||           // luma/alpha param error
      uv_width <= 0 || uv_height <= 0) {     // u/v param error
    return WebPEncodingSetError(picture, VP8_ENC_ERROR_BAD_DIMENSION);
  }
  // allocate a new buffer.
  mem = (uint8_t*)WebPSafeMalloc(total_size, sizeof(*mem));
  if (mem == NULL) {
    return WebPEncodingSetError(picture, VP8_ENC_ERROR_OUT_OF_MEMORY);
  }

  // From now on, we're in the clear, we can no longer fail...
  picture->memory_ = (void*)mem;
  picture->y_stride  = y_stride;
  picture->uv_stride = uv_stride;
  picture->a_stride  = a_stride;

  // TODO(skal): we could align the y/u/v planes and adjust stride.
  picture->y = mem;
  mem += y_size;

  picture->u = mem;
  mem += uv_size;
  picture->v = mem;
  mem += uv_size;

  if (a_size > 0) {
    picture->a = mem;
    mem += a_size;
  }
  (void)mem;  // makes the static analyzer happy
  return 1;
}