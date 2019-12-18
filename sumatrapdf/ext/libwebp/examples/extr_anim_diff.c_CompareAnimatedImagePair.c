#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  format ;
struct TYPE_6__ {int num_frames; int canvas_width; int canvas_height; scalar_t__ format; int loop_count; TYPE_1__* frames; int /*<<< orphan*/  bgcolor; } ;
struct TYPE_5__ {int duration; int /*<<< orphan*/ * rgba; } ;
typedef  TYPE_2__ AnimatedImage ;

/* Variables and functions */
 scalar_t__ ANIM_GIF ; 
 scalar_t__ ANIM_WEBP ; 
 scalar_t__ CompareBackgroundColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CompareValues (int,int,char*) ; 
 int /*<<< orphan*/  GetDiffAndPSNR (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const,int,int,int,int*,double*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t,int,...) ; 
 scalar_t__ snprintf (char*,int,char const*,size_t) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int CompareAnimatedImagePair(const AnimatedImage* const img1,
                                    const AnimatedImage* const img2,
                                    int premultiply,
                                    double min_psnr) {
  int ok = 1;
  const int is_multi_frame_image = (img1->num_frames > 1);
  uint32_t i;

  ok = CompareValues(img1->canvas_width, img2->canvas_width,
                     "Canvas width mismatch") && ok;
  ok = CompareValues(img1->canvas_height, img2->canvas_height,
                     "Canvas height mismatch") && ok;
  ok = CompareValues(img1->num_frames, img2->num_frames,
                     "Frame count mismatch") && ok;
  if (!ok) return 0;  // These are fatal failures, can't proceed.

  if (is_multi_frame_image) {  // Checks relevant for multi-frame images only.
    int max_loop_count_workaround = 0;
    // Transcodes to webp increase the gif loop count by 1 for compatibility.
    // When the gif has the maximum value the webp value will be off by one.
    if ((img1->format == ANIM_GIF && img1->loop_count == 65536 &&
         img2->format == ANIM_WEBP && img2->loop_count == 65535) ||
        (img1->format == ANIM_WEBP && img1->loop_count == 65535 &&
         img2->format == ANIM_GIF && img2->loop_count == 65536)) {
      max_loop_count_workaround = 1;
    }
    ok = (max_loop_count_workaround ||
          CompareValues(img1->loop_count, img2->loop_count,
                        "Loop count mismatch")) && ok;
    ok = CompareBackgroundColor(img1->bgcolor, img2->bgcolor,
                                premultiply) && ok;
  }

  for (i = 0; i < img1->num_frames; ++i) {
    // Pixel-by-pixel comparison.
    const uint8_t* const rgba1 = img1->frames[i].rgba;
    const uint8_t* const rgba2 = img2->frames[i].rgba;
    int max_diff;
    double psnr;
    if (is_multi_frame_image) {  // Check relevant for multi-frame images only.
      const char format[] = "Frame #%d, duration mismatch";
      char tmp[sizeof(format) + 8];
      ok = ok && (snprintf(tmp, sizeof(tmp), format, i) >= 0);
      ok = ok && CompareValues(img1->frames[i].duration,
                               img2->frames[i].duration, tmp);
    }
    GetDiffAndPSNR(rgba1, rgba2, img1->canvas_width, img1->canvas_height,
                   premultiply, &max_diff, &psnr);
    if (min_psnr > 0.) {
      if (psnr < min_psnr) {
        fprintf(stderr, "Frame #%d, psnr = %.2lf (min_psnr = %f)\n", i,
                psnr, min_psnr);
        ok = 0;
      }
    } else {
      if (max_diff != 0) {
        fprintf(stderr, "Frame #%d, max pixel diff: %d\n", i, max_diff);
        ok = 0;
      }
    }
  }
  return ok;
}