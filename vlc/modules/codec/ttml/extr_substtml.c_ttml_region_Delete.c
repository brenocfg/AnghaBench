#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_bytes; } ;
struct TYPE_6__ {TYPE_1__ bgbitmap; int /*<<< orphan*/  updt; } ;
typedef  TYPE_2__ ttml_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  SubpictureUpdaterSysRegionClean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void ttml_region_Delete( ttml_region_t *p_region )
{
    SubpictureUpdaterSysRegionClean( &p_region->updt );
    free( p_region->bgbitmap.p_bytes );
    free( p_region );
}