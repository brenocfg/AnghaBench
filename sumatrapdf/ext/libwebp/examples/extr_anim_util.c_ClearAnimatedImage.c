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
struct TYPE_3__ {int /*<<< orphan*/ * raw_mem; int /*<<< orphan*/ * frames; scalar_t__ num_frames; } ;
typedef  TYPE_1__ AnimatedImage ;

/* Variables and functions */
 int /*<<< orphan*/  WebPFree (int /*<<< orphan*/ *) ; 

void ClearAnimatedImage(AnimatedImage* const image) {
  if (image != NULL) {
    WebPFree(image->raw_mem);
    WebPFree(image->frames);
    image->num_frames = 0;
    image->frames = NULL;
    image->raw_mem = NULL;
  }
}