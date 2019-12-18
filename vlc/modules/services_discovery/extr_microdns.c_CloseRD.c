#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct discovery_sys* p_sys; } ;
typedef  TYPE_1__ vlc_renderer_discovery_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct discovery_sys {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CleanCommon (struct discovery_sys*) ; 

__attribute__((used)) static void
CloseRD( vlc_object_t *p_this )
{
    vlc_renderer_discovery_t *p_rd = (vlc_renderer_discovery_t *) p_this;
    struct discovery_sys *p_sys = p_rd->p_sys;

    CleanCommon( p_sys );
}