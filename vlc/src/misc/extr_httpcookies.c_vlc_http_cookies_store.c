#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cookies; } ;
typedef  TYPE_1__ vlc_http_cookie_jar_t ;
struct TYPE_10__ {int /*<<< orphan*/  psz_name; int /*<<< orphan*/  psz_path; int /*<<< orphan*/  psz_domain; } ;
typedef  TYPE_2__ http_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cookie_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  cookie_domain_matches (TYPE_2__*,char const*) ; 
 TYPE_2__* cookie_parse (char const*,char const*,char const*) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_array_append (int /*<<< orphan*/ *,TYPE_2__*) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 TYPE_2__* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_array_remove (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ vlc_ascii_strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

bool vlc_http_cookies_store(vlc_http_cookie_jar_t *p_jar, const char *cookies,
                            const char *host, const char *path)
{
    assert(host != NULL);
    assert(path != NULL);

    http_cookie_t *cookie = cookie_parse(cookies, host, path);
    if (cookie == NULL)
        return false;

    /* Check if a cookie from host should be added to the cookie jar */
    // FIXME: should check if domain is one of "public suffixes" at
    // http://publicsuffix.org/. The purpose of this check is to
    // prevent a host from setting a "too wide" cookie, for example
    // "example.com" should not be able to set a cookie for "com".
    // The current implementation prevents all top-level domains.
    if (strchr(cookie->psz_domain, '.') == NULL
     || !cookie_domain_matches(cookie, host))
    {
        cookie_destroy(cookie);
        return false;
    }

    vlc_mutex_lock( &p_jar->lock );

    for( size_t i = 0; i < vlc_array_count( &p_jar->cookies ); i++ )
    {
        http_cookie_t *iter = vlc_array_item_at_index( &p_jar->cookies, i );

        assert( iter->psz_name );
        assert( iter->psz_domain );
        assert( iter->psz_path );

        bool domains_match =
            vlc_ascii_strcasecmp( cookie->psz_domain, iter->psz_domain ) == 0;
        bool paths_match = strcmp( cookie->psz_path, iter->psz_path ) == 0;
        bool names_match = strcmp( cookie->psz_name, iter->psz_name ) == 0;
        if( domains_match && paths_match && names_match )
        {
            /* Remove previous value for this cookie */
            vlc_array_remove( &p_jar->cookies, i );
            cookie_destroy(iter);
            break;
        }
    }

    bool b_ret = (vlc_array_append( &p_jar->cookies, cookie ) == 0);
    if( !b_ret )
        cookie_destroy( cookie );

    vlc_mutex_unlock( &p_jar->lock );

    return b_ret;
}