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
struct vlc_http_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strspn (char const*,char*) ; 
 char* vlc_http_get_token_value (char const*,char*) ; 
 char* vlc_http_msg_get_token (struct vlc_http_msg const*,char*,char*) ; 

char *vlc_http_msg_get_basic_realm(const struct vlc_http_msg *m)
{
    const char *auth;

    /* TODO: Support other authentication schemes. */
    /* NOTE: In principles, RFC7235 allows for multiple authentication schemes,
     * including multiple times Basic with a different realm each. There are no
     * UI paradigms though. */
    auth = vlc_http_msg_get_token(m, "WWW-Authenticate", "Basic");
    if (auth == NULL)
        return NULL;

    auth += 5;
    auth += strspn(auth, " "); /* 1*SP */

    return vlc_http_get_token_value(auth, "realm");
}