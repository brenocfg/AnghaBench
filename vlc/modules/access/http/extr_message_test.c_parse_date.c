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
typedef  scalar_t__ time_t ;
struct vlc_http_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ vlc_http_msg_add_header (struct vlc_http_msg*,char*,char*,char const*) ; 
 int /*<<< orphan*/  vlc_http_msg_destroy (struct vlc_http_msg*) ; 
 scalar_t__ vlc_http_msg_get_atime (struct vlc_http_msg*) ; 
 scalar_t__ vlc_http_msg_get_mtime (struct vlc_http_msg*) ; 
 scalar_t__ vlc_http_msg_get_retry_after (struct vlc_http_msg*) ; 
 struct vlc_http_msg* vlc_http_req_create (char*,char*,char*,char*) ; 

__attribute__((used)) static time_t parse_date(const char *str)
{
    struct vlc_http_msg *m;
    time_t t1, t2;

    m = vlc_http_req_create("GET", "http", "www.example.com", "/");
    assert(m != NULL);
    assert(vlc_http_msg_add_header(m, "Date", "%s", str) == 0);
    t1 = vlc_http_msg_get_atime(m);
    assert(vlc_http_msg_add_header(m, "Last-Modified", "%s", str) == 0);
    t2 = vlc_http_msg_get_mtime(m);
    assert(vlc_http_msg_get_retry_after(m) == 0);
    assert(vlc_http_msg_add_header(m, "Retry-After", "%s", str) == 0);
    vlc_http_msg_get_retry_after(m);
    vlc_http_msg_destroy(m);

    assert(t1 == t2);
    return t1;
}