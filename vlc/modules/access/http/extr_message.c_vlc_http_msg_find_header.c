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
struct vlc_http_msg {unsigned int count; int /*<<< orphan*/ ** headers; } ;
typedef  unsigned int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static ssize_t vlc_http_msg_find_header(const struct vlc_http_msg *m,
                                        const char *name)
{
    for (unsigned i = 0; i < m->count; i++)
        if (!strcasecmp(m->headers[i][0], name))
            return i;
    return -1;
}