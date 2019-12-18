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
struct TYPE_3__ {char* psz_protocol; char* psz_username; char* psz_password; unsigned long i_port; char* psz_path; char* psz_option; char* psz_fragment; char* psz_buffer; int /*<<< orphan*/ * psz_host; int /*<<< orphan*/ * psz_pathbuffer; } ;
typedef  TYPE_1__ vlc_url_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 unsigned long UINT_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ isurialnum (char) ; 
 int /*<<< orphan*/ * memchr (char*,char,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 unsigned long strtoul (char*,char**,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_idna_to_ascii (char const*) ; 
 char* vlc_iri2uri (char const*) ; 
 scalar_t__ vlc_uri_component_validate (char*,char*) ; 
 char* vlc_uri_decode (char*) ; 
 int /*<<< orphan*/  vlc_uri_host_validate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlc_UrlParseInner(vlc_url_t *restrict url, const char *str)
{
    url->psz_protocol = NULL;
    url->psz_username = NULL;
    url->psz_password = NULL;
    url->psz_host = NULL;
    url->i_port = 0;
    url->psz_path = NULL;
    url->psz_option = NULL;
    url->psz_fragment = NULL;
    url->psz_buffer = NULL;
    url->psz_pathbuffer = NULL;

    if (str == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    char *buf = vlc_iri2uri(str);
    if (unlikely(buf == NULL))
        return -1;
    url->psz_buffer = buf;

    char *cur = buf, *next;
    int ret = 0;

    /* URI scheme */
    next = buf;
    while (isurialnum(*next) || memchr ("+-.", *next, 3) != NULL)
        next++;

    if (*next == ':')
    {
        *(next++) = '\0';
        url->psz_protocol = cur;
        cur = next;
    }

    /* Fragment */
    next = strchr(cur, '#');
    if (next != NULL)
    {
       *(next++) = '\0';
       if (vlc_uri_component_validate(next, "/?"))
           url->psz_fragment = next;
    }

    /* Query parameters */
    next = strchr(cur, '?');
    if (next != NULL)
    {
        *(next++) = '\0';
        url->psz_option = next;
    }

    /* Authority */
    if (strncmp(cur, "//", 2) == 0)
    {
        cur += 2;

        /* Path */
        next = strchr(cur, '/');
        if (next != NULL)
        {
            *next = '\0'; /* temporary nul, reset to slash later */
            url->psz_path = next;
        }
        /*else
            url->psz_path = "/";*/

        /* User name */
        next = strrchr(cur, '@');
        if (next != NULL)
        {
            *(next++) = '\0';
            url->psz_username = cur;
            cur = next;

            /* Password (obsolete) */
            next = strchr(url->psz_username, ':');
            if (next != NULL)
            {
                *(next++) = '\0';
                url->psz_password = next;
                vlc_uri_decode(url->psz_password);
            }
            vlc_uri_decode(url->psz_username);
        }

        /* Host name */
        if (*cur == '[' && (next = strrchr(cur, ']')) != NULL)
        {   /* Try IPv6 numeral within brackets */
            *(next++) = '\0';
            url->psz_host = strdup(cur + 1);

            if (*next == ':')
                next++;
            else
                next = NULL;
        }
        else
        {
            next = strchr(cur, ':');
            if (next != NULL)
                *(next++) = '\0';

            const char *host = vlc_uri_decode(cur);
            url->psz_host = (host != NULL) ? vlc_idna_to_ascii(host) : NULL;
        }

        if (url->psz_host == NULL)
            ret = -1;
        else
        if (!vlc_uri_host_validate(url->psz_host))
        {
            free(url->psz_host);
            url->psz_host = NULL;
            errno = EINVAL;
            ret = -1;
        }

        /* Port number */
        if (next != NULL && *next)
        {
            char* end;
            unsigned long port = strtoul(next, &end, 10);

            if (strchr("0123456789", *next) == NULL || *end || port > UINT_MAX)
            {
                errno = EINVAL;
                ret = -1;
            }

            url->i_port = port;
        }

        if (url->psz_path != NULL)
            *url->psz_path = '/'; /* restore leading slash */
    }
    else
    {
        url->psz_path = cur;
    }

    return ret;
}