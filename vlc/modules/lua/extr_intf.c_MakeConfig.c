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
struct TYPE_4__ {unsigned int i_port; char* psz_host; } ;
typedef  TYPE_1__ vlc_url_t ;
typedef  int /*<<< orphan*/  intf_thread_t ;

/* Variables and functions */
 unsigned int TELNETPORT_DEFAULT ; 
 int asprintf (char**,char*,char*,...) ; 
 char* config_StringEscape (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 unsigned int var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_UrlClean (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_UrlParse (TYPE_1__*,char*) ; 

__attribute__((used)) static char *MakeConfig( intf_thread_t *p_intf, const char *name )
{
    char *psz_config = NULL;

    if( !strcmp( name, "http" ) )
    {
        char *psz_http_src = var_InheritString( p_intf, "http-src" );
        bool b_http_index = var_InheritBool( p_intf, "http-index" );
        if( psz_http_src )
        {
            char *psz_esc = config_StringEscape( psz_http_src );

            if( asprintf( &psz_config, "http={dir='%s',no_index=%s}", psz_esc,
                          b_http_index ? "true" : "false" ) == -1 )
                psz_config = NULL;
            free( psz_esc );
            free( psz_http_src );
        }
        else
        {
            if( asprintf( &psz_config, "http={no_index=%s}",
                          b_http_index ? "true" : "false" ) == -1 )
                psz_config = NULL;
        }
    }
    else if( !strcmp( name, "telnet" ) )
    {
        char *psz_host = var_InheritString( p_intf, "telnet-host" );
        if( !strcmp( psz_host, "*console" ) )
            ;
        else
        {
            vlc_url_t url;
            vlc_UrlParse( &url, psz_host );
            unsigned i_port = var_InheritInteger( p_intf, "telnet-port" );
            if ( url.i_port != 0 )
            {
                if ( i_port == TELNETPORT_DEFAULT )
                    i_port = url.i_port;
                else if ( url.i_port != i_port )
                    msg_Warn( p_intf, "ignoring port %d (using %d)",
                              url.i_port, i_port );
            }

            char *psz_esc_host = config_StringEscape( url.psz_host );
            free( psz_host );
            vlc_UrlClean( &url );

            if( asprintf( &psz_host, "telnet://%s:%d",
                          psz_esc_host ? psz_esc_host : "", i_port ) == -1 )
                psz_host = NULL;
            free( psz_esc_host );
        }

        char *psz_passwd = var_InheritString( p_intf, "telnet-password" );

        char *psz_esc_passwd = config_StringEscape( psz_passwd );

        if( asprintf( &psz_config, "telnet={host='%s',password='%s'}",
                      psz_host, psz_esc_passwd ) == -1 )
            psz_config = NULL;

        free( psz_esc_passwd );
        free( psz_passwd );
        free( psz_host );
    }

    return psz_config;
}