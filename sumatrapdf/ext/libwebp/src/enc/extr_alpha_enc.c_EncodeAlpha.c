#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int const uint64_t ;
struct TYPE_5__ {int width; int height; int const a_stride; TYPE_4__* stats; int /*<<< orphan*/ * a; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_6__ {int* sse_; TYPE_1__* pic_; } ;
typedef  TYPE_2__ VP8Encoder ;
struct TYPE_7__ {int coded_size; } ;

/* Variables and functions */
 int ALPHA_LOSSLESS_COMPRESSION ; 
 int ALPHA_NO_COMPRESSION ; 
 int ApplyFiltersAndEncode (int /*<<< orphan*/ *,int const,int const,size_t const,int,int,int const,int,int /*<<< orphan*/ ** const,size_t* const,TYPE_4__*) ; 
 int QuantizeLevels (int /*<<< orphan*/ *,int const,int const,int const,int const*) ; 
 int /*<<< orphan*/  VP8FiltersInit () ; 
 int WEBP_FILTER_FAST ; 
 int WEBP_FILTER_NONE ; 
 int /*<<< orphan*/  WebPCopyPlane (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const,int const,int const) ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ *) ; 
 scalar_t__ WebPSafeMalloc (unsigned long long,size_t const) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int EncodeAlpha(VP8Encoder* const enc,
                       int quality, int method, int filter,
                       int effort_level,
                       uint8_t** const output, size_t* const output_size) {
  const WebPPicture* const pic = enc->pic_;
  const int width = pic->width;
  const int height = pic->height;

  uint8_t* quant_alpha = NULL;
  const size_t data_size = width * height;
  uint64_t sse = 0;
  int ok = 1;
  const int reduce_levels = (quality < 100);

  // quick sanity checks
  assert((uint64_t)data_size == (uint64_t)width * height);  // as per spec
  assert(enc != NULL && pic != NULL && pic->a != NULL);
  assert(output != NULL && output_size != NULL);
  assert(width > 0 && height > 0);
  assert(pic->a_stride >= width);
  assert(filter >= WEBP_FILTER_NONE && filter <= WEBP_FILTER_FAST);

  if (quality < 0 || quality > 100) {
    return 0;
  }

  if (method < ALPHA_NO_COMPRESSION || method > ALPHA_LOSSLESS_COMPRESSION) {
    return 0;
  }

  if (method == ALPHA_NO_COMPRESSION) {
    // Don't filter, as filtering will make no impact on compressed size.
    filter = WEBP_FILTER_NONE;
  }

  quant_alpha = (uint8_t*)WebPSafeMalloc(1ULL, data_size);
  if (quant_alpha == NULL) {
    return 0;
  }

  // Extract alpha data (width x height) from raw_data (stride x height).
  WebPCopyPlane(pic->a, pic->a_stride, quant_alpha, width, width, height);

  if (reduce_levels) {  // No Quantization required for 'quality = 100'.
    // 16 alpha levels gives quite a low MSE w.r.t original alpha plane hence
    // mapped to moderate quality 70. Hence Quality:[0, 70] -> Levels:[2, 16]
    // and Quality:]70, 100] -> Levels:]16, 256].
    const int alpha_levels = (quality <= 70) ? (2 + quality / 5)
                                             : (16 + (quality - 70) * 8);
    ok = QuantizeLevels(quant_alpha, width, height, alpha_levels, &sse);
  }

  if (ok) {
    VP8FiltersInit();
    ok = ApplyFiltersAndEncode(quant_alpha, width, height, data_size, method,
                               filter, reduce_levels, effort_level, output,
                               output_size, pic->stats);
#if !defined(WEBP_DISABLE_STATS)
    if (pic->stats != NULL) {  // need stats?
      pic->stats->coded_size += (int)(*output_size);
      enc->sse_[3] = sse;
    }
#endif
  }

  WebPSafeFree(quant_alpha);
  return ok;
}