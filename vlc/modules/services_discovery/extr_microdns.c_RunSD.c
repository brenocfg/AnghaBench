#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct discovery_sys {int /*<<< orphan*/  i_nb_service_names; int /*<<< orphan*/  ppsz_service_names; int /*<<< orphan*/  p_microdns; } ;
struct TYPE_4__ {struct discovery_sys* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;

/* Variables and functions */
 int /*<<< orphan*/  LISTEN_INTERVAL ; 
 int /*<<< orphan*/  RR_PTR ; 
 int /*<<< orphan*/  SEC_FROM_VLC_TICK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int mdns_listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  new_entries_sd_cb ; 
 int /*<<< orphan*/  print_error (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stop_sd_cb ; 

__attribute__((used)) static void *
RunSD( void *p_this )
{
    services_discovery_t *p_sd = ( services_discovery_t* )p_this;
    struct discovery_sys *p_sys = p_sd->p_sys;

    int i_status = mdns_listen( p_sys->p_microdns,
                                p_sys->ppsz_service_names,
                                p_sys->i_nb_service_names,
                                RR_PTR, SEC_FROM_VLC_TICK(LISTEN_INTERVAL),
                                stop_sd_cb, new_entries_sd_cb, p_sd );

    if( i_status < 0 )
        print_error( VLC_OBJECT( p_sd ), "listen", i_status );

    return NULL;
}