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
struct vlc_http_msg {unsigned long status; int /*<<< orphan*/ * method; int /*<<< orphan*/ * path; int /*<<< orphan*/ * authority; int /*<<< orphan*/ * scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 void* strdup (char const*) ; 
 unsigned long strtoul (char const*,char**,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_http_msg_add_header (struct vlc_http_msg*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  vlc_http_msg_destroy (struct vlc_http_msg*) ; 
 struct vlc_http_msg* vlc_http_resp_create (int /*<<< orphan*/ ) ; 

struct vlc_http_msg *vlc_http_msg_h2_headers(unsigned n,
                                             const char *const hdrs[][2])
{
    struct vlc_http_msg *m = vlc_http_resp_create(0);
    if (unlikely(m == NULL))
        return NULL;

    for (unsigned i = 0; i < n; i++)
    {
        const char *name = hdrs[i][0];
        const char *value = hdrs[i][1];

        /* NOTE: HPACK always returns lower-case names, so strcmp() is fine. */
        if (!strcmp(name, ":status"))
        {
            char *end;
            unsigned long status = strtoul(value, &end, 10);

            if (m->status != 0 || status > 999 || *end != '\0')
                goto error; /* Not a three decimal digits status! */

            m->status = status;
            continue;
        }

        if (!strcmp(name, ":method"))
        {
            if (m->method != NULL)
                goto error;

            m->method = strdup(value);
            if (unlikely(m->method == NULL))
                goto error;

            m->status = -1; /* this is a request */
            continue;
        }

        if (!strcmp(name, ":scheme"))
        {
            if (m->scheme != NULL)
                goto error;

            m->scheme = strdup(value);
            if (unlikely(m->scheme == NULL))
                goto error;
            continue;
        }

        if (!strcmp(name, ":authority"))
        {
            if (m->authority != NULL)
                goto error;

            m->authority = strdup(value);
            if (unlikely(m->authority == NULL))
                goto error;
            continue;
        }

        if (!strcmp(name, ":path"))
        {
            if (m->path != NULL)
                goto error;

            m->path = strdup(value);
            if (unlikely(m->path == NULL))
                goto error;
            continue;
        }

        if (vlc_http_msg_add_header(m, name, "%s", value))
            goto error;
    }

    if ((m->status < 0) == (m->method == NULL))
    {   /* Must be either a request or response. Not both, not neither. */
error:
        vlc_http_msg_destroy(m);
        m = NULL;
    }
    return m;
}