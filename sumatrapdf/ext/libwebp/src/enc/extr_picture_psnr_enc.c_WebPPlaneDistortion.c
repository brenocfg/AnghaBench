#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ (* AccumulateFunc ) (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int,int) ;

/* Variables and functions */
 scalar_t__ AccumulateLSIM (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int,int) ; 
 scalar_t__ AccumulateSSE (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int,int) ; 
 scalar_t__ AccumulateSSIM (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int,int) ; 
 scalar_t__ GetLogSSIM (float,double) ; 
 scalar_t__ GetPSNR (float,double) ; 
 int /*<<< orphan*/  VP8SSIMDspInit () ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ *) ; 
 scalar_t__ WebPSafeMalloc (unsigned long long,int) ; 

int WebPPlaneDistortion(const uint8_t* src, size_t src_stride,
                        const uint8_t* ref, size_t ref_stride,
                        int width, int height, size_t x_step,
                        int type, float* distortion, float* result) {
  uint8_t* allocated = NULL;
  const AccumulateFunc metric = (type == 0) ? AccumulateSSE :
                                (type == 1) ? AccumulateSSIM :
                                              AccumulateLSIM;
  if (src == NULL || ref == NULL ||
      src_stride < x_step * width || ref_stride < x_step * width ||
      result == NULL || distortion == NULL) {
    return 0;
  }

  VP8SSIMDspInit();
  if (x_step != 1) {   // extract a packed plane if needed
    int x, y;
    uint8_t* tmp1;
    uint8_t* tmp2;
    allocated =
        (uint8_t*)WebPSafeMalloc(2ULL * width * height, sizeof(*allocated));
    if (allocated == NULL) return 0;
    tmp1 = allocated;
    tmp2 = tmp1 + (size_t)width * height;
    for (y = 0; y < height; ++y) {
      for (x = 0; x < width; ++x) {
        tmp1[x + y * width] = src[x * x_step + y * src_stride];
        tmp2[x + y * width] = ref[x * x_step + y * ref_stride];
      }
    }
    src = tmp1;
    ref = tmp2;
  }
  *distortion = (float)metric(src, width, ref, width, width, height);
  WebPSafeFree(allocated);

  *result = (type == 1) ? (float)GetLogSSIM(*distortion, (double)width * height)
                        : (float)GetPSNR(*distortion, (double)width * height);
  return 1;
}