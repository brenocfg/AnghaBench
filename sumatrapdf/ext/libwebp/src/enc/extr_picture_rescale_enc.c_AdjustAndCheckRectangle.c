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
struct TYPE_4__ {int width; int height; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  SnapTopLeftPosition (TYPE_1__ const* const,int* const,int* const) ; 

__attribute__((used)) static int AdjustAndCheckRectangle(const WebPPicture* const pic,
                                   int* const left, int* const top,
                                   int width, int height) {
  SnapTopLeftPosition(pic, left, top);
  if ((*left) < 0 || (*top) < 0) return 0;
  if (width <= 0 || height <= 0) return 0;
  if ((*left) + width > pic->width) return 0;
  if ((*top) + height > pic->height) return 0;
  return 1;
}