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
struct vlc_http_resource {int /*<<< orphan*/  path; int /*<<< orphan*/  authority; scalar_t__ secure; int /*<<< orphan*/  response; } ;

/* Variables and functions */
 int asprintf (char**,char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 size_t strcspn (char*,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_ascii_strcasecmp (char const*,char*) ; 
 char* vlc_http_msg_get_header (int /*<<< orphan*/ ,char*) ; 
 int vlc_http_res_get_status (struct vlc_http_resource*) ; 
 char* vlc_uri_fixup (char const*) ; 
 char* vlc_uri_resolve (char*,char const*) ; 

char *vlc_http_res_get_redirect(struct vlc_http_resource *restrict res)
{
    int status = vlc_http_res_get_status(res);
    if (status < 0)
        return NULL;

    if ((status / 100) == 2 && !res->secure)
    {
        char *url;

        /* HACK: Seems like an MMS server. Redirect to MMSH scheme. */
        const char *pragma = vlc_http_msg_get_header(res->response, "Pragma");
        if (pragma != NULL && !vlc_ascii_strcasecmp(pragma, "features")
         && asprintf(&url, "mmsh://%s%s", res->authority, res->path) >= 0)
            return url;

        /* HACK: Seems like an ICY server. Redirect to ICYX scheme. */
        if ((vlc_http_msg_get_header(res->response, "Icy-Name") != NULL
          || vlc_http_msg_get_header(res->response, "Icy-Genre") != NULL)
         && asprintf(&url, "icyx://%s%s", res->authority, res->path) >= 0)
            return url;
    }

    /* TODO: if (status == 426 Upgrade Required) */

    /* Location header is only meaningful for 201 and 3xx */
    if (status != 201 && (status / 100) != 3)
        return NULL;
    if (status == 304 /* Not Modified */
     || status == 305 /* Use Proxy (deprecated) */
     || status == 306 /* Switch Proxy (former) */)
        return NULL;

    const char *location = vlc_http_msg_get_header(res->response, "Location");
    if (location == NULL)
        return NULL;

    /* TODO: if status is 3xx, check for Retry-After and wait */

    char *base;

    if (unlikely(asprintf(&base, "http%s://%s%s", res->secure ? "s" : "",
                          res->authority, res->path) == -1))
        return NULL;

    char *fixed = vlc_uri_fixup(location);
    if (fixed != NULL)
        location = fixed;

    char *abs = vlc_uri_resolve(base, location);

    free(fixed);
    free(base);

    if (likely(abs != NULL))
    {
        /* NOTE: The anchor is discarded if it is present as VLC does not support
         * HTML anchors so far. */
        size_t len = strcspn(abs, "#");
        abs[len] = '\0';
    }
    return abs;
}