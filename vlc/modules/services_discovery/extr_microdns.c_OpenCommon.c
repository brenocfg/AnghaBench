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
struct discovery_sys {scalar_t__ i_nb_service_names; int /*<<< orphan*/ * p_microdns; int /*<<< orphan*/  thread; int /*<<< orphan*/ * ppsz_service_names; int /*<<< orphan*/  items; int /*<<< orphan*/  stop; } ;
struct TYPE_2__ {int b_renderer; int /*<<< orphan*/  psz_service_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDNS_ADDR_IPV4 ; 
 int /*<<< orphan*/  MDNS_PORT ; 
 unsigned int NB_PROTOCOLS ; 
 int /*<<< orphan*/  RunRD ; 
 int /*<<< orphan*/  RunSD ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct discovery_sys*) ; 
 int /*<<< orphan*/  mdns_destroy (int /*<<< orphan*/ *) ; 
 int mdns_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_error (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_1__* protocols ; 
 int /*<<< orphan*/  vlc_array_init (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
OpenCommon( vlc_object_t *p_obj, struct discovery_sys *p_sys, bool b_renderer )
{
    int i_ret = VLC_EGENERIC;
    atomic_init( &p_sys->stop, false );
    vlc_array_init( &p_sys->items );

    /* Listen to protocols that are handled by VLC */
    for( unsigned int i = 0; i < NB_PROTOCOLS; ++i )
    {
        if( protocols[i].b_renderer == b_renderer )
            p_sys->ppsz_service_names[p_sys->i_nb_service_names++] =
                protocols[i].psz_service_name;
    }

    if( p_sys->i_nb_service_names == 0 )
    {
        msg_Err( p_obj, "no services found" );
        goto error;
    }
    for( unsigned int i = 0; i < p_sys->i_nb_service_names; ++i )
        msg_Dbg( p_obj, "mDNS: listening to %s %s", p_sys->ppsz_service_names[i],
                 b_renderer ? "renderer" : "service" );

    int i_status;
    if( ( i_status = mdns_init( &p_sys->p_microdns, MDNS_ADDR_IPV4,
                                MDNS_PORT ) ) < 0 )
    {
        print_error( p_obj, "init", i_status );
        goto error;
    }

    if( vlc_clone( &p_sys->thread, b_renderer ? RunRD : RunSD, p_obj,
                   VLC_THREAD_PRIORITY_LOW) )
    {
        msg_Err( p_obj, "Can't run the lookup thread" );
        goto error;
    }

    return VLC_SUCCESS;
error:
    if( p_sys->p_microdns != NULL )
        mdns_destroy( p_sys->p_microdns );
    free( p_sys );
    return i_ret;
}