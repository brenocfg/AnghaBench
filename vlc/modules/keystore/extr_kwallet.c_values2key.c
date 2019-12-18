#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct vlc_memstream {char* ptr; } ;

/* Variables and functions */
 size_t KEY_AUTHTYPE ; 
 size_t KEY_PATH ; 
 size_t KEY_PORT ; 
 size_t KEY_PROTOCOL ; 
 size_t KEY_REALM ; 
 size_t KEY_SERVER ; 
 size_t KEY_USER ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strlen (char const* const) ; 
 char* vlc_b64_encode_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 scalar_t__ vlc_memstream_flush (struct vlc_memstream*) ; 
 scalar_t__ vlc_memstream_open (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_printf (struct vlc_memstream*,char*,...) ; 
 int /*<<< orphan*/  vlc_memstream_putc (struct vlc_memstream*,char) ; 
 int /*<<< orphan*/  vlc_memstream_puts (struct vlc_memstream*,char const* const) ; 

__attribute__((used)) static char*
values2key( const char* const* ppsz_values, bool b_search )
{
    char* psz_b64_realm = NULL;
    char* psz_b64_auth = NULL;
    bool b_state = false;

    if ( ( !ppsz_values[KEY_PROTOCOL] || !ppsz_values[KEY_SERVER] )
         && !b_search )
        return NULL;

    struct vlc_memstream ms;
    if ( vlc_memstream_open( &ms ) )
        return NULL;

    /* Protocol section */
    if ( ppsz_values[KEY_PROTOCOL] )
        vlc_memstream_printf( &ms, "%s://", ppsz_values[KEY_PROTOCOL] );
    else if ( b_search )
        vlc_memstream_printf( &ms, "*://" );

    /* User section */
    if ( ppsz_values[KEY_USER] )
        vlc_memstream_printf( &ms, "%s@", ppsz_values[KEY_USER] );
    else if ( b_search )
        vlc_memstream_printf( &ms, "*" );

    /* Server section */
    if ( ppsz_values[KEY_SERVER] )
        vlc_memstream_printf( &ms, "%s", ppsz_values[KEY_SERVER] );
    else if ( b_search )
        vlc_memstream_printf( &ms, "*" );

    /* Port section */
    if ( ppsz_values[KEY_PORT] )
        vlc_memstream_printf( &ms, ":%s", ppsz_values[KEY_PORT] );
    else if ( b_search )
        vlc_memstream_printf( &ms, "*" );

    /* Path section */
    if( ppsz_values[KEY_PATH] )
    {
        if( ppsz_values[KEY_PATH][0] != '/' )
            vlc_memstream_putc( &ms, '/' );

        vlc_memstream_puts( &ms, ppsz_values[KEY_PATH] );
    }
    else if ( b_search )
        vlc_memstream_printf( &ms, "*" );

    /* Realm and authtype section */
    if ( ppsz_values[KEY_REALM] || ppsz_values[KEY_AUTHTYPE] || b_search )
    {
        vlc_memstream_printf( &ms, "?" );

        /* Realm section */
        if ( ppsz_values[KEY_REALM] || b_search )
        {
            if ( ppsz_values[KEY_REALM] )
            {
                psz_b64_realm = vlc_b64_encode_binary( ( uint8_t* )ppsz_values[KEY_REALM],
                                                       strlen(ppsz_values[KEY_REALM] ) );
                if ( !psz_b64_realm )
                    goto end;
                vlc_memstream_printf( &ms, "realm=%s", psz_b64_realm );
            }
            else
                vlc_memstream_printf( &ms, "*" );

            if ( ppsz_values[KEY_AUTHTYPE] )
                vlc_memstream_printf( &ms, "&" );
        }

        /* Authtype section */
        if ( ppsz_values[KEY_AUTHTYPE] || b_search )
        {

            if ( ppsz_values[KEY_AUTHTYPE] )
            {
                psz_b64_auth = vlc_b64_encode_binary( ( uint8_t* )ppsz_values[KEY_AUTHTYPE],
                                                      strlen(ppsz_values[KEY_AUTHTYPE] ) );
                if ( !psz_b64_auth )
                    goto end;
                vlc_memstream_printf( &ms, "authtype=%s", psz_b64_auth );
            }
            else
                vlc_memstream_printf( &ms, "*" );
        }

    }

    b_state = true;

end:
    free( psz_b64_realm );
    free( psz_b64_auth );
    if ( vlc_memstream_flush( &ms ) != 0 )
        b_state = false;
    char *psz_key = vlc_memstream_close( &ms ) == 0 ? ms.ptr : NULL;
    if ( !b_state )
    {
        free( psz_key );
        psz_key = NULL;
    }
    return psz_key;
}