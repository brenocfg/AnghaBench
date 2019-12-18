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
struct TYPE_4__ {char* psz_host; scalar_t__ i_port; char* psz_path; } ;
typedef  TYPE_1__ vlc_url_t ;
typedef  enum tls_mode_e { ____Placeholder_tls_mode_e } tls_mode_e ;

/* Variables and functions */
 int IMPLICIT ; 
 scalar_t__ IPPORT_FTP ; 
 scalar_t__ IPPORT_FTPS ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  vlc_UrlParseFixup (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  vlc_uri_decode (char*) ; 

__attribute__((used)) static int parseURL( vlc_url_t *url, const char *path, enum tls_mode_e mode )
{
    if( path == NULL )
        return VLC_EGENERIC;

    /* *** Parse URL and get server addr/port and path *** */
    while( *path == '/' )
        path++;

    vlc_UrlParseFixup( url, path );

    if( url->psz_host == NULL || *url->psz_host == '\0' )
        return VLC_EGENERIC;

    if( url->i_port <= 0 )
    {
        if( mode == IMPLICIT )
            url->i_port = IPPORT_FTPS;
        else
            url->i_port = IPPORT_FTP; /* default port */
    }

    if( url->psz_path == NULL )
        return VLC_SUCCESS;
    /* FTP URLs are relative to user's default directory (RFC1738 §3.2)
    For absolute path use ftp://foo.bar//usr/local/etc/filename */
    /* FIXME: we should issue a series of CWD, one per slash */
    if( url->psz_path )
    {
        assert( url->psz_path[0] == '/' );
        url->psz_path++;
    }

    char *type = strstr( url->psz_path, ";type=" );
    if( type )
    {
        *type = '\0';
        if( strchr( "iI", type[6] ) == NULL )
            return VLC_EGENERIC; /* ASCII and directory not supported */
    }
    vlc_uri_decode( url->psz_path );
    return VLC_SUCCESS;
}