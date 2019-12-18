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
struct vlc_http_msg {unsigned int status; int /*<<< orphan*/ * payload; int /*<<< orphan*/ * headers; scalar_t__ count; int /*<<< orphan*/ * path; int /*<<< orphan*/ * authority; int /*<<< orphan*/ * scheme; int /*<<< orphan*/ * method; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct vlc_http_msg* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct vlc_http_msg *vlc_http_resp_create(unsigned status)
{
    struct vlc_http_msg *m = malloc(sizeof (*m));
    if (unlikely(m == NULL))
        return NULL;

    assert(status < 1000);
    m->status = status;
    m->method = NULL;
    m->scheme = NULL;
    m->authority = NULL;
    m->path = NULL;
    m->count = 0;
    m->headers = NULL;
    m->payload = NULL;
    return m;
}