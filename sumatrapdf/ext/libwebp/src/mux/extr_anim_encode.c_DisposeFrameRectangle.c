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
typedef  int /*<<< orphan*/  WebPPicture ;
typedef  int /*<<< orphan*/  FrameRectangle ;

/* Variables and functions */
 int WEBP_MUX_DISPOSE_BACKGROUND ; 
 int /*<<< orphan*/  WebPUtilClearPic (int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DisposeFrameRectangle(int dispose_method,
                                  const FrameRectangle* const rect,
                                  WebPPicture* const curr_canvas) {
  assert(rect != NULL);
  if (dispose_method == WEBP_MUX_DISPOSE_BACKGROUND) {
    WebPUtilClearPic(curr_canvas, rect);
  }
}