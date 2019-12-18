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
typedef  int /*<<< orphan*/  vlc_renderer_item_t ;
typedef  int /*<<< orphan*/  vlc_renderer_discovery_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  services_name_to_input_item; scalar_t__ parent; } ;
typedef  TYPE_1__ discovery_sys_t ;
typedef  int /*<<< orphan*/  AvahiStringList ;

/* Variables and functions */
 int VLC_RENDERER_CAN_AUDIO ; 
 int VLC_RENDERER_CAN_VIDEO ; 
 scalar_t__ asprintf (char**,char*,char const*,char const*,...) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  avahi_free (void*) ; 
 int /*<<< orphan*/ * avahi_string_list_find (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ avahi_string_list_get_pair (int /*<<< orphan*/ *,char**,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  vlc_dictionary_insert (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_rd_add_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_renderer_item_new (char const*,char*,char*,char const*,char const*,char*,int) ; 

__attribute__((used)) static void add_renderer( const char *psz_protocol, const char *psz_name,
                          const char *psz_addr, uint16_t i_port,
                          AvahiStringList *txt, discovery_sys_t *p_sys )
{
    vlc_renderer_discovery_t *p_rd = ( vlc_renderer_discovery_t* )(p_sys->parent);
    AvahiStringList *asl = NULL;
    char *friendly_name = NULL;
    char *icon_uri = NULL;
    char *uri = NULL;
    const char *demux = NULL;
    const char *extra_uri = NULL;
    int renderer_flags = 0;

    if( !strcmp( "chromecast", psz_protocol ) ) {
        int ret = 0;

        /* Capabilities */
        asl = avahi_string_list_find( txt, "ca" );
        if( asl != NULL ) {
            char *key = NULL;
            char *value = NULL;
            if( avahi_string_list_get_pair( asl, &key, &value, NULL ) == 0 &&
                value != NULL )
            {
                int ca = atoi( value );

                if( ( ca & 0x01 ) != 0 )
                    renderer_flags |= VLC_RENDERER_CAN_VIDEO;
                if( ( ca & 0x04 ) != 0 )
                    renderer_flags |= VLC_RENDERER_CAN_AUDIO;
            }

            if( key != NULL )
                avahi_free( (void *)key );
            if( value != NULL )
                avahi_free( (void *)value );
        }

        /* Friendly name */
        asl = avahi_string_list_find( txt, "fn" );
        if( asl != NULL )
        {
            char *key = NULL;
            char *value = NULL;
            if( avahi_string_list_get_pair( asl, &key, &value, NULL ) == 0 &&
                value != NULL )
            {
                friendly_name = strdup( value );
                if( !friendly_name )
                    ret = -1;
            }

            if( key != NULL )
                avahi_free( (void *)key );
            if( value != NULL )
                avahi_free( (void *)value );
        }
        if( ret < 0 )
            goto error;

        /* Icon */
        asl = avahi_string_list_find( txt, "ic" );
        if( asl != NULL ) {
            char *key = NULL;
            char *value = NULL;
            if( avahi_string_list_get_pair( asl, &key, &value, NULL ) == 0 &&
                value != NULL )
                ret = asprintf( &icon_uri, "http://%s:8008%s", psz_addr, value);

            if( key != NULL )
                avahi_free( (void *)key );
            if( value != NULL )
                avahi_free( (void *)value );
        }
        if( ret < 0 )
            goto error;

        if( asprintf( &uri, "%s://%s:%u", psz_protocol, psz_addr, i_port ) < 0 )
            goto error;

        extra_uri = renderer_flags & VLC_RENDERER_CAN_VIDEO ? NULL : "no-video";
        demux = "cc_demux";
    }

    vlc_renderer_item_t *p_renderer_item =
        vlc_renderer_item_new( psz_protocol, friendly_name ? friendly_name : psz_name, uri, extra_uri,
                               demux, icon_uri, renderer_flags );
    if( p_renderer_item == NULL )
        goto error;

    vlc_dictionary_insert( &p_sys->services_name_to_input_item,
        psz_name, p_renderer_item);
    vlc_rd_add_item( p_rd, p_renderer_item );

error:
    free( friendly_name );
    free( icon_uri );
    free( uri );
}