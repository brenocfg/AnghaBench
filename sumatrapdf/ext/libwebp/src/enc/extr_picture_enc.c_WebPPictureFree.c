#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  memory_argb_; int /*<<< orphan*/  memory_; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  WebPPictureResetBuffers (TYPE_1__*) ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ ) ; 

void WebPPictureFree(WebPPicture* picture) {
  if (picture != NULL) {
    WebPSafeFree(picture->memory_);
    WebPSafeFree(picture->memory_argb_);
    WebPPictureResetBuffers(picture);
  }
}