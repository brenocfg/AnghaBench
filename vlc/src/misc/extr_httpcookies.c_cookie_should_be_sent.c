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
struct TYPE_5__ {int /*<<< orphan*/  b_secure; } ;
typedef  TYPE_1__ http_cookie_t ;

/* Variables and functions */
 int cookie_domain_matches (TYPE_1__ const*,char const*) ; 
 int cookie_path_matches (TYPE_1__ const*,char const*) ; 

__attribute__((used)) static bool cookie_should_be_sent(const http_cookie_t *cookie, bool secure,
                                  const char *host, const char *path)
{
    bool protocol_ok = secure || !cookie->b_secure;
    bool domain_ok = cookie_domain_matches(cookie, host);
    bool path_ok = cookie_path_matches(cookie, path);
    return protocol_ok && domain_ok && path_ok;
}