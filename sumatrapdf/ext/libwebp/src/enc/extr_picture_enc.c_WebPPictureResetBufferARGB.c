#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ argb_stride; int /*<<< orphan*/ * argb; int /*<<< orphan*/ * memory_argb_; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */

__attribute__((used)) static void WebPPictureResetBufferARGB(WebPPicture* const picture) {
  picture->memory_argb_ = NULL;
  picture->argb = NULL;
  picture->argb_stride = 0;
}