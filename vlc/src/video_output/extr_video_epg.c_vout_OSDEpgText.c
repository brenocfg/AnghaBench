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
typedef  int /*<<< orphan*/  subpicture_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  vout_OSDSegment (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vout_OSDTextRegion (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static subpicture_region_t * vout_OSDEpgText(const char *text,
                                             int x, int y,
                                             int size, uint32_t color)
{
    return vout_OSDTextRegion(vout_OSDSegment(text, size, color), x, y);
}