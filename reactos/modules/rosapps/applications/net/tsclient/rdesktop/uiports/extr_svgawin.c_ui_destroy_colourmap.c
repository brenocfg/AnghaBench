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
typedef  scalar_t__ HCOLOURMAP ;

/* Variables and functions */
 scalar_t__ colmap ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

void ui_destroy_colourmap(HCOLOURMAP map)
{
  if (colmap == map)
    colmap = 0;
  xfree(map);
}