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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 scalar_t__ vlc_http_msg_add_header (struct vlc_http_msg*,char*,char*,char const*) ; 
 int /*<<< orphan*/  vlc_http_msg_destroy (struct vlc_http_msg*) ; 
 char* vlc_http_msg_get_basic_realm (struct vlc_http_msg*) ; 
 struct vlc_http_msg* vlc_http_resp_create (int) ; 

__attribute__((used)) static const char *check_realm(const char *line, const char *realm)
{
    struct vlc_http_msg *m;
    char *value;

    m = vlc_http_resp_create(401);
    assert(m != NULL);
    assert(vlc_http_msg_add_header(m, "WWW-Authenticate", "%s", line) == 0);
    value = vlc_http_msg_get_basic_realm(m);
    if (realm == NULL)
        assert(value == NULL);
    else
    {
        assert(value != NULL);
        assert(!strcmp(value, realm));
        free(value);
    }
    vlc_http_msg_destroy(m);
    return realm;
}