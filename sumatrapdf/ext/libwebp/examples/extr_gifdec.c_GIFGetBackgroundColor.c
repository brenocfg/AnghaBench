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
typedef  int /*<<< orphan*/  uint32_t ;
struct ColorMapObject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ErrorGIFNotAvailable () ; 

void GIFGetBackgroundColor(const struct ColorMapObject* const color_map,
                           int bgcolor_index, int transparent_index,
                           uint32_t* const bgcolor) {
  (void)color_map;
  (void)bgcolor_index;
  (void)transparent_index;
  (void)bgcolor;
  ErrorGIFNotAvailable();
}