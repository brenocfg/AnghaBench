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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_tracks_num; } ;
typedef  TYPE_2__ services_discovery_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int CountTracks( uint64_t const sent, uint64_t const total,
                        void const * const data )
{
    VLC_UNUSED( sent );
    services_discovery_t *p_sd = (services_discovery_t *)data;
    services_discovery_sys_t *p_sys = p_sd->p_sys;
    p_sys->i_tracks_num = total;
    return 0;
}