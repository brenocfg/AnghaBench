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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int argb_stride; int /*<<< orphan*/ * argb; void* memory_argb_; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  VP8_ENC_ERROR_BAD_DIMENSION ; 
 int /*<<< orphan*/  VP8_ENC_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ WEBP_ALIGN (void*) ; 
 int const WEBP_ALIGN_CST ; 
 int WebPEncodingSetError (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPPictureResetBufferARGB (TYPE_1__* const) ; 
 int /*<<< orphan*/  WebPSafeFree (void*) ; 
 void* WebPSafeMalloc (int const,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int WebPPictureAllocARGB(WebPPicture* const picture, int width, int height) {
  void* memory;
  const uint64_t argb_size = (uint64_t)width * height;

  assert(picture != NULL);

  WebPSafeFree(picture->memory_argb_);
  WebPPictureResetBufferARGB(picture);

  if (width <= 0 || height <= 0) {
    return WebPEncodingSetError(picture, VP8_ENC_ERROR_BAD_DIMENSION);
  }
  // allocate a new buffer.
  memory = WebPSafeMalloc(argb_size + WEBP_ALIGN_CST, sizeof(*picture->argb));
  if (memory == NULL) {
    return WebPEncodingSetError(picture, VP8_ENC_ERROR_OUT_OF_MEMORY);
  }
  picture->memory_argb_ = memory;
  picture->argb = (uint32_t*)WEBP_ALIGN(memory);
  picture->argb_stride = width;
  return 1;
}