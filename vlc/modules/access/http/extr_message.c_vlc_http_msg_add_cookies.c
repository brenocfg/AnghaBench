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
struct vlc_http_msg {char* authority; int /*<<< orphan*/ * path; int /*<<< orphan*/ * scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcspn (char*,char*) ; 
 char* strndup (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 char* vlc_http_cookies_fetch (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 int vlc_http_msg_add_header (struct vlc_http_msg*,char*,char*,char*) ; 

int vlc_http_msg_add_cookies(struct vlc_http_msg *m,
                             vlc_http_cookie_jar_t *jar)
{
    char *host, *cookies;
    int val = 0;
    bool secure;

    if (m->scheme == NULL || m->authority == NULL || m->path == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    if (!strcasecmp(m->scheme, "https"))
        secure = true;
    else if (!strcasecmp(m->scheme, "http"))
        secure = false;
    else
        return 0;

    if (jar == NULL)
        return 0;

    if (m->authority[0] == '[')
        host = strndup(m->authority + 1, strcspn(m->authority + 1, "]"));
    else
        host = strndup(m->authority, strcspn(m->authority, ":"));
    if (unlikely(host == NULL))
        return -1;

    cookies = vlc_http_cookies_fetch(jar, secure, host, m->path);
    free(host);

    if (cookies != NULL)
    {
        val = vlc_http_msg_add_header(m, "Cookie", "%s", cookies);
        free(cookies);
    }
    return val;
}