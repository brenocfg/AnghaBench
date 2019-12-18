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
struct TYPE_3__ {int /*<<< orphan*/  p_region_style; int /*<<< orphan*/  p_segments; } ;
typedef  TYPE_1__ substext_updater_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  text_segment_ChainDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_style_Delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void SubpictureUpdaterSysRegionClean(substext_updater_region_t *p_updtregion)
{
    text_segment_ChainDelete( p_updtregion->p_segments );
    text_style_Delete( p_updtregion->p_region_style );
}