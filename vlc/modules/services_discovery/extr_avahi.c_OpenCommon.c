#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ renderer; int /*<<< orphan*/ * poll; int /*<<< orphan*/ * client; int /*<<< orphan*/  parent; int /*<<< orphan*/  services_name_to_input_item; } ;
typedef  TYPE_1__ discovery_sys_t ;
struct TYPE_7__ {scalar_t__ b_renderer; int /*<<< orphan*/  psz_service_name; } ;
typedef  int /*<<< orphan*/  AvahiServiceBrowser ;

/* Variables and functions */
 int /*<<< orphan*/  AVAHI_IF_UNSPEC ; 
 int /*<<< orphan*/  AVAHI_PROTO_UNSPEC ; 
 unsigned int NB_PROTOCOLS ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int avahi_client_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avahi_client_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avahi_client_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * avahi_service_browser_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  avahi_strerror (int) ; 
 int /*<<< orphan*/  avahi_threaded_poll_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avahi_threaded_poll_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avahi_threaded_poll_new () ; 
 int /*<<< orphan*/  avahi_threaded_poll_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  browse_callback ; 
 int /*<<< orphan*/  client_callback ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* protocols ; 
 int /*<<< orphan*/  vlc_dictionary_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int OpenCommon( discovery_sys_t *p_sys )
{
    int err;

    vlc_dictionary_init( &p_sys->services_name_to_input_item, 1 );

    p_sys->poll = avahi_threaded_poll_new();
    if( p_sys->poll == NULL )
    {
        msg_Err( p_sys->parent, "failed to create Avahi threaded poll" );
        goto error;
    }

    p_sys->client = avahi_client_new( avahi_threaded_poll_get(p_sys->poll),
                                      0, client_callback, p_sys, &err );
    if( p_sys->client == NULL )
    {
        msg_Err( p_sys->parent, "failed to create avahi client: %s",
                 avahi_strerror( err ) );
        goto error;
    }

    for( unsigned i = 0; i < NB_PROTOCOLS; i++ )
    {
        if( protocols[i].b_renderer != p_sys->renderer )
            continue;

        AvahiServiceBrowser *sb;
        sb = avahi_service_browser_new( p_sys->client, AVAHI_IF_UNSPEC,
                AVAHI_PROTO_UNSPEC,
                protocols[i].psz_service_name, NULL,
                0, browse_callback, p_sys );
        if( sb == NULL )
        {
            msg_Err( p_sys->parent, "failed to create avahi service browser %s", avahi_strerror( avahi_client_errno(p_sys->client) ) );
            goto error;
        }
    }

    avahi_threaded_poll_start( p_sys->poll );

    return VLC_SUCCESS;

error:
    if( p_sys->client != NULL )
        avahi_client_free( p_sys->client );
    if( p_sys->poll != NULL )
        avahi_threaded_poll_free( p_sys->poll );

    return VLC_EGENERIC;
}