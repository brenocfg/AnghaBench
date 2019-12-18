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
typedef  int /*<<< orphan*/  vlc_http_cookie_jar_t ;
struct vlc_http_msg {unsigned int count; int /*<<< orphan*/ ** headers; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_http_cookies_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 

void vlc_http_msg_get_cookies(const struct vlc_http_msg *m,
                              vlc_http_cookie_jar_t *jar,
                              const char *host, const char *path)
{
    if (jar == NULL)
        return;

    for (unsigned i = 0; i < m->count; i++)
        if (!strcasecmp(m->headers[i][0], "Set-Cookie"))
            vlc_http_cookies_store(jar, m->headers[i][1], host, path);
}