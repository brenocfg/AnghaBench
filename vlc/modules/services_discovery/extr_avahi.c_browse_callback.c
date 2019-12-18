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
typedef  int /*<<< orphan*/  vlc_renderer_discovery_t ;
typedef  int /*<<< orphan*/  services_discovery_t ;
struct TYPE_2__ {int /*<<< orphan*/  services_name_to_input_item; scalar_t__ parent; scalar_t__ renderer; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ discovery_sys_t ;
typedef  int /*<<< orphan*/  AvahiServiceBrowser ;
typedef  int /*<<< orphan*/  AvahiProtocol ;
typedef  int /*<<< orphan*/ * AvahiLookupResultFlags ;
typedef  int /*<<< orphan*/  AvahiIfIndex ;
typedef  scalar_t__ AvahiBrowserEvent ;

/* Variables and functions */
 scalar_t__ AVAHI_BROWSER_NEW ; 
 scalar_t__ AVAHI_BROWSER_REMOVE ; 
 int /*<<< orphan*/  AVAHI_PROTO_UNSPEC ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avahi_client_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * avahi_service_resolver_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  avahi_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_Release (void*) ; 
 int /*<<< orphan*/  msg_Err (scalar_t__,char*,char const*,...) ; 
 int /*<<< orphan*/  resolve_callback ; 
 int /*<<< orphan*/  services_discovery_RemoveItem (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  vlc_dictionary_remove_value_for_key (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlc_rd_remove_item (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  vlc_renderer_item_release (void*) ; 

__attribute__((used)) static void browse_callback(
    AvahiServiceBrowser *b,
    AvahiIfIndex interface,
    AvahiProtocol protocol,
    AvahiBrowserEvent event,
    const char *name,
    const char *type,
    const char *domain,
    AvahiLookupResultFlags flags,
    void* userdata )
{
    VLC_UNUSED(b);
    VLC_UNUSED(flags);
    discovery_sys_t *p_sys = userdata;
    if( event == AVAHI_BROWSER_NEW )
    {
        if( avahi_service_resolver_new( p_sys->client, interface, protocol,
                                        name, type, domain, AVAHI_PROTO_UNSPEC,
                                        0,
                                        resolve_callback, userdata ) == NULL )
        {
            msg_Err( p_sys->parent, "failed to resolve service '%s': %s", name,
                     avahi_strerror( avahi_client_errno( p_sys->client ) ) );
        }
    }
    else if( event == AVAHI_BROWSER_REMOVE && name )
    {
        /** \todo Store the input id and search it, rather than searching the items */
        void *p_item;
        p_item = vlc_dictionary_value_for_key(
                        &p_sys->services_name_to_input_item,
                        name );
        if( !p_item )
            msg_Err( p_sys->parent, "failed to find service '%s' in playlist", name );
        else
        {
            if( p_sys->renderer )
            {
                vlc_renderer_discovery_t *p_rd = ( vlc_renderer_discovery_t* )(p_sys->parent);
                vlc_rd_remove_item( p_rd, p_item );
                vlc_renderer_item_release( p_item );
            }
            else
            {
                services_discovery_t *p_sd = ( services_discovery_t* )(p_sys->parent);
                services_discovery_RemoveItem( p_sd, p_item );
                input_item_Release( p_item );
            }
            vlc_dictionary_remove_value_for_key(
                        &p_sys->services_name_to_input_item,
                        name, NULL, NULL );
        }
    }
}