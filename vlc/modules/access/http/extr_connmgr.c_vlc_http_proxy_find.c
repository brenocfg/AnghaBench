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

/* Variables and functions */
 scalar_t__ asprintf (char**,char const*,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 char* vlc_getProxyUrl (char*) ; 

__attribute__((used)) static char *vlc_http_proxy_find(const char *hostname, unsigned port,
                                 bool secure)
{
    const char *fmt;
    char *url, *proxy = NULL;

    if (strchr(hostname, ':') != NULL)
        fmt = port ? "http%s://[%s]:%u" : "http%s://[%s]";
    else
        fmt = port ? "http%s://%s:%u" : "http%s://%s";

    if (likely(asprintf(&url, fmt, secure ? "s" : "", hostname, port) >= 0))
    {
        proxy = vlc_getProxyUrl(url);
        free(url);
    }
    return proxy;
}