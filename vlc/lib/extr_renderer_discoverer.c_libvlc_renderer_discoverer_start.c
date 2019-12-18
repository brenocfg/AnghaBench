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
struct vlc_renderer_discovery_owner {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; TYPE_1__* member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/ * p_rd; int /*<<< orphan*/  name; int /*<<< orphan*/  p_object; } ;
typedef  TYPE_1__ libvlc_renderer_discoverer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  renderer_discovery_item_added ; 
 int /*<<< orphan*/  renderer_discovery_item_removed ; 
 int /*<<< orphan*/ * vlc_rd_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vlc_renderer_discovery_owner*) ; 

int
libvlc_renderer_discoverer_start( libvlc_renderer_discoverer_t *p_lrd )
{
    assert( p_lrd->p_rd == NULL );

    struct vlc_renderer_discovery_owner owner =
    {
        p_lrd,
        renderer_discovery_item_added,
        renderer_discovery_item_removed,
    };

    p_lrd->p_rd = vlc_rd_new( p_lrd->p_object, p_lrd->name, &owner );
    return p_lrd->p_rd != NULL ? 0 : -1;
}