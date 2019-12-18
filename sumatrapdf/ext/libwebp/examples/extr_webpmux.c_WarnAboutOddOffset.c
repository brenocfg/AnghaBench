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
struct TYPE_3__ {int x_offset; int y_offset; } ;
typedef  TYPE_1__ WebPMuxFrameInfo ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void WarnAboutOddOffset(const WebPMuxFrameInfo* const info) {
  if ((info->x_offset | info->y_offset) & 1) {
    fprintf(stderr, "Warning: odd offsets will be snapped to even values"
            " (%d, %d) -> (%d, %d)\n", info->x_offset, info->y_offset,
            info->x_offset & ~1, info->y_offset & ~1);
  }
}