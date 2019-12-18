#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* psz_password; } ;
typedef  TYPE_1__ vlc_url_t ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  unsigned char BYTE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 char* config_GetPsz (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  vlc_UrlClean (TYPE_1__*) ; 
 scalar_t__ vlc_UrlParse (TYPE_1__*,char*) ; 
 char* vlc_uri_compose (TYPE_1__*) ; 

char *vlc_getProxyUrl(const char *psz_url)
{
    VLC_UNUSED(psz_url);

    char *proxy = config_GetPsz( "http-proxy" );
    if (proxy == NULL)
        return NULL;

    char *proxy_pwd = config_GetPsz( "http-proxy-pwd" );
    if (proxy_pwd == NULL)
        return proxy;

    vlc_url_t url;
    if (vlc_UrlParse(&url, proxy) < 0) {
        vlc_UrlClean(&url);
        free (proxy);
        free (proxy_pwd);
        return NULL;
    }

    if (url.psz_password == NULL )
        url.psz_password = proxy_pwd;

    char *proxy_url = vlc_uri_compose (&url);
    vlc_UrlClean (&url);

    free (proxy_pwd);
    free (proxy);

#if 0
    /* Try to get the proxy server address from Windows internet settings. */
    HKEY h_key;

    /* Open the key */
    if( RegOpenKeyEx( HKEY_CURRENT_USER, "Software\\Microsoft"
                      "\\Windows\\CurrentVersion\\Internet Settings",
                      0, KEY_READ, &h_key ) == ERROR_SUCCESS )
        return NULL;

    DWORD len = sizeof( DWORD );
    BYTE proxyEnable;

    /* Get the proxy enable value */
    if( RegQueryValueEx( h_key, "ProxyEnable", NULL, NULL,
                         &proxyEnable, &len ) != ERROR_SUCCESS
     || !proxyEnable )
        goto out;

    /* Proxy is enabled */
    /* Get the proxy URL :
       Proxy server value in the registry can be something like "address:port"
       or "ftp=address1:port1;http=address2:port2 ..."
       depending of the configuration. */
    unsigned char key[256];

    len = sizeof( key );
    if( RegQueryValueEx( h_key, "ProxyServer", NULL, NULL,
                         key, &len ) == ERROR_SUCCESS )
    {
        /* FIXME: This is lame. The string should be tokenized. */
#warning FIXME.
        char *psz_proxy = strstr( (char *)key, "http=" );
        if( psz_proxy != NULL )
        {
            psz_proxy += 5;
            char *end = strchr( psz_proxy, ';' );
            if( end != NULL )
                *end = '\0';
        }
        else
            psz_proxy = (char *)key;
        proxy_url = strdup( psz_proxy );
    }

out:
    RegCloseKey( h_key );
#endif
    return proxy_url;
}