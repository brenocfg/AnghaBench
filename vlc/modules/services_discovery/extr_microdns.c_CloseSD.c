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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct discovery_sys {int dummy; } ;
struct TYPE_2__ {struct discovery_sys* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;

/* Variables and functions */
 int /*<<< orphan*/  CleanCommon (struct discovery_sys*) ; 

__attribute__((used)) static void
CloseSD( vlc_object_t *p_this )
{
    services_discovery_t *p_sd = (services_discovery_t *) p_this;
    struct discovery_sys *p_sys = p_sd->p_sys;

    CleanCommon( p_sys );
}