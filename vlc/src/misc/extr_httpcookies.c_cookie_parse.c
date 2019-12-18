#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* psz_name; int b_host_only; int /*<<< orphan*/  b_secure; int /*<<< orphan*/ * psz_path; int /*<<< orphan*/ * psz_domain; int /*<<< orphan*/ * psz_value; } ;
typedef  TYPE_1__ http_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cookie_default_path (char const*) ; 
 int /*<<< orphan*/  cookie_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/ * cookie_get_domain (char const*) ; 
 int /*<<< orphan*/ * cookie_get_path (char const*) ; 
 int /*<<< orphan*/  cookie_has_attribute (char const*,char*) ; 
 TYPE_1__* malloc (int) ; 
 char* memchr (char const*,char,size_t) ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 void* strndup (char const*,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static http_cookie_t *cookie_parse(const char *value,
                                   const char *host, const char *path)
{
    http_cookie_t *cookie = malloc(sizeof (*cookie));
    if (unlikely(cookie == NULL))
        return NULL;

    cookie->psz_domain = NULL;
    cookie->psz_path = NULL;

    /* Get the NAME=VALUE part of the Cookie */
    size_t value_length = strcspn(value, ";");
    const char *p = memchr(value, '=', value_length);

    if (p != NULL)
    {
        cookie->psz_name = strndup(value, p - value);
        p++;
        cookie->psz_value = strndup(p, value_length - (p - value));
        if (unlikely(cookie->psz_value == NULL))
            goto error;
    }
    else
    {
        cookie->psz_name = strndup(value, value_length);
        cookie->psz_value = NULL;
    }

    if (unlikely(cookie->psz_name == NULL))
        goto error;

    /* Cookie name is a token; it cannot be empty. */
    if (cookie->psz_name[0] == '\0')
        goto error;

    /* Get domain */
    cookie->psz_domain = cookie_get_domain(value);
    if (cookie->psz_domain == NULL)
    {
        cookie->psz_domain = strdup(host);
        if (unlikely(cookie->psz_domain == NULL))
            goto error;

        cookie->b_host_only = true;
    }
    else
        cookie->b_host_only = false;

    /* Get path */
    cookie->psz_path = cookie_get_path(value);
    if (cookie->psz_path == NULL)
    {
        cookie->psz_path = cookie_default_path(path);
        if (unlikely(cookie->psz_path == NULL))
            goto error;
    }

    /* Get secure flag */
    cookie->b_secure = cookie_has_attribute(value, "secure");

    return cookie;

error:
    cookie_destroy(cookie);
    return NULL;
}