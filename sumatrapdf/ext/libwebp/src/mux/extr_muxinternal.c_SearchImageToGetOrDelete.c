#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {struct TYPE_6__* next_; } ;
typedef  TYPE_1__ WebPMuxImage ;

/* Variables and functions */
 scalar_t__ MuxImageCount (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEBP_CHUNK_NIL ; 
 int /*<<< orphan*/  assert (TYPE_1__**) ; 

__attribute__((used)) static int SearchImageToGetOrDelete(WebPMuxImage** wpi_list, uint32_t nth,
                                    WebPMuxImage*** const location) {
  uint32_t count = 0;
  assert(wpi_list);
  *location = wpi_list;

  if (nth == 0) {
    nth = MuxImageCount(*wpi_list, WEBP_CHUNK_NIL);
    if (nth == 0) return 0;  // Not found.
  }

  while (*wpi_list != NULL) {
    WebPMuxImage* const cur_wpi = *wpi_list;
    ++count;
    if (count == nth) return 1;  // Found.
    wpi_list = &cur_wpi->next_;
    *location = wpi_list;
  }
  return 0;  // Not found.
}