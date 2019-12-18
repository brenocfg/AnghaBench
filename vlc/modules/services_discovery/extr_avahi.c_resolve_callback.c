#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  services_discovery_t ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_4__ {int /*<<< orphan*/  services_name_to_input_item; scalar_t__ parent; } ;
typedef  TYPE_1__ discovery_sys_t ;
typedef  int /*<<< orphan*/  a ;
struct TYPE_5__ {char* psz_protocol; int b_renderer; int /*<<< orphan*/  psz_service_name; } ;
typedef  int /*<<< orphan*/  AvahiStringList ;
typedef  int /*<<< orphan*/  AvahiServiceResolver ;
typedef  scalar_t__ AvahiResolverEvent ;
typedef  scalar_t__ AvahiProtocol ;
typedef  char const* AvahiLookupResultFlags ;
typedef  char const* AvahiIfIndex ;
typedef  int /*<<< orphan*/  AvahiAddress ;

/* Variables and functions */
 scalar_t__ AVAHI_PROTO_INET6 ; 
 scalar_t__ AVAHI_RESOLVER_FAILURE ; 
 scalar_t__ AVAHI_RESOLVER_FOUND ; 
 int /*<<< orphan*/  ITEM_NET ; 
 unsigned int NB_PROTOCOLS ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int /*<<< orphan*/  add_renderer (char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int asprintf (char**,char*,char const*,...) ; 
 int /*<<< orphan*/  avahi_address_snprint (char*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  avahi_free (void*) ; 
 int /*<<< orphan*/  avahi_service_resolver_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avahi_string_list_find (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ avahi_string_list_get_pair (int /*<<< orphan*/ *,char**,char**,size_t*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * input_item_NewDirectory (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (scalar_t__,char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  msg_Info (scalar_t__,char*,char const*,char const*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* protocols ; 
 int /*<<< orphan*/  services_discovery_AddItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_dictionary_insert (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resolve_callback(
    AvahiServiceResolver *r,
    AvahiIfIndex interface,
    AvahiProtocol protocol,
    AvahiResolverEvent event,
    const char *name,
    const char *type,
    const char *domain,
    const char *host_name,
    const AvahiAddress *address,
    uint16_t port,
    AvahiStringList *txt,
    AvahiLookupResultFlags flags,
    void* userdata )
{
    discovery_sys_t *p_sys = userdata;

    VLC_UNUSED(interface); VLC_UNUSED(host_name);
    VLC_UNUSED(flags);

    if( event == AVAHI_RESOLVER_FAILURE )
    {
        msg_Err( p_sys->parent,
                 "failed to resolve service '%s' of type '%s' in domain '%s'",
                 name, type, domain );
    }
    else if( event == AVAHI_RESOLVER_FOUND )
    {
        char a[128];
        char *psz_uri = NULL;
        char *psz_addr = NULL;
        AvahiStringList *asl = NULL;
        input_item_t *p_input = NULL;

        msg_Info( p_sys->parent, "service '%s' of type '%s' in domain '%s' port %i",
                  name, type, domain, port );

        avahi_address_snprint(a, (sizeof(a)/sizeof(a[0]))-1, address);
        if( protocol == AVAHI_PROTO_INET6 )
            if( asprintf( &psz_addr, "[%s]", a ) == -1 )
            {
                avahi_service_resolver_free( r );
                return;
            }

        const char *psz_protocol = NULL;
        bool is_renderer = false;
        for( unsigned int i = 0; i < NB_PROTOCOLS; i++ )
        {
            if( !strcmp(type, protocols[i].psz_service_name) )
            {
                psz_protocol = protocols[i].psz_protocol;
                is_renderer = protocols[i].b_renderer;
                break;
            }
        }
        if( psz_protocol == NULL )
        {
            free( psz_addr );
            avahi_service_resolver_free( r );
            return;
        }

        if( txt != NULL && is_renderer )
        {
            const char* addr_v4v6 = psz_addr != NULL ? psz_addr : a;
            add_renderer( psz_protocol, name, addr_v4v6, port, txt, p_sys );
            free( psz_addr );
            avahi_service_resolver_free( r );
            return;
        }

        if( txt != NULL )
            asl = avahi_string_list_find( txt, "path" );
        if( asl != NULL )
        {
            size_t size;
            char *key = NULL;
            char *value = NULL;
            if( avahi_string_list_get_pair( asl, &key, &value, &size ) == 0 &&
                value != NULL )
            {
                if( asprintf( &psz_uri, "%s://%s:%d%s",
                          psz_protocol,
                          psz_addr != NULL ? psz_addr : a,
                          port, value ) == -1 )
                {
                    free( psz_addr );
                    avahi_service_resolver_free( r );
                    return;
                }
            }
            if( key != NULL )
                avahi_free( (void *)key );
            if( value != NULL )
                avahi_free( (void *)value );
        }
        else
        {
            if( asprintf( &psz_uri, "%s://%s:%d",
                      psz_protocol,
                      psz_addr != NULL ? psz_addr : a, port ) == -1 )
            {
                free( psz_addr );
                avahi_service_resolver_free( r );
                return;
            }
        }

        free( psz_addr );

        if( psz_uri != NULL )
        {
            p_input = input_item_NewDirectory( psz_uri, name, ITEM_NET );
            free( psz_uri );
        }
        if( p_input != NULL )
        {
            services_discovery_t *p_sd = ( services_discovery_t* )(p_sys->parent);
            vlc_dictionary_insert( &p_sys->services_name_to_input_item,
                name, p_input );
            services_discovery_AddItem( p_sd, p_input );
       }
    }

    avahi_service_resolver_free( r );
}