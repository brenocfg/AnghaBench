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
struct WebPPicture {int dummy; } ;
typedef  int /*<<< orphan*/  GIFFrameRect ;

/* Variables and functions */
 int /*<<< orphan*/  ErrorGIFNotAvailable () ; 

void GIFBlendFrames(const struct WebPPicture* const src,
                    const GIFFrameRect* const rect,
                    struct WebPPicture* const dst) {
  (void)src;
  (void)rect;
  (void)dst;
  ErrorGIFNotAvailable();
}