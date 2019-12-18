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
struct vlc_http_msg {int status; int /*<<< orphan*/ * path; int /*<<< orphan*/ * authority; int /*<<< orphan*/ * scheme; int /*<<< orphan*/ * method; int /*<<< orphan*/ * payload; int /*<<< orphan*/ * headers; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct vlc_http_msg* malloc (int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_http_msg_destroy (struct vlc_http_msg*) ; 

struct vlc_http_msg *
vlc_http_req_create(const char *method, const char *scheme,
                    const char *authority, const char *path)
{
    struct vlc_http_msg *m = malloc(sizeof (*m));
    if (unlikely(m == NULL))
        return NULL;

    assert(method != NULL);
    m->status = -1;
    m->method = strdup(method);
    m->scheme = (scheme != NULL) ? strdup(scheme) : NULL;
    m->authority = (authority != NULL) ? strdup(authority) : NULL;
    m->path = (path != NULL) ? strdup(path) : NULL;
    m->count = 0;
    m->headers = NULL;
    m->payload = NULL;

    if (unlikely(m->method == NULL
              || (scheme != NULL && m->scheme == NULL)
              || (authority != NULL && m->authority == NULL)
              || (path != NULL && m->path == NULL)))
    {
        vlc_http_msg_destroy(m);
        m = NULL;
    }
    return m;
}