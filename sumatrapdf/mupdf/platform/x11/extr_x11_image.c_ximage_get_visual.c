#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Visual ;
struct TYPE_3__ {int /*<<< orphan*/ * visual; } ;
struct TYPE_4__ {TYPE_1__ visual; } ;

/* Variables and functions */
 TYPE_2__ info ; 

Visual *
ximage_get_visual(void)
{
	return info.visual.visual;
}