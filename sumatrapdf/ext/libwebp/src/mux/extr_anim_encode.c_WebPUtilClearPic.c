#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_7__ {int /*<<< orphan*/  height_; int /*<<< orphan*/  width_; int /*<<< orphan*/  y_offset_; int /*<<< orphan*/  x_offset_; } ;
typedef  TYPE_2__ FrameRectangle ;

/* Variables and functions */
 int /*<<< orphan*/  ClearRectangle (TYPE_1__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void WebPUtilClearPic(WebPPicture* const picture,
                             const FrameRectangle* const rect) {
  if (rect != NULL) {
    ClearRectangle(picture, rect->x_offset_, rect->y_offset_,
                   rect->width_, rect->height_);
  } else {
    ClearRectangle(picture, 0, 0, picture->width, picture->height);
  }
}