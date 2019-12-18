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

/* Variables and functions */
 int /*<<< orphan*/  WebPPictureResetBuffers (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void PictureGrabSpecs(const WebPPicture* const src,
                             WebPPicture* const dst) {
  assert(src != NULL && dst != NULL);
  *dst = *src;
  WebPPictureResetBuffers(dst);
}