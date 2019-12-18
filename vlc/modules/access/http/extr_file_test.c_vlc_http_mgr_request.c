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
typedef  int time_t ;
struct vlc_http_msg {int dummy; } ;
struct vlc_http_mgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ etags ; 
 scalar_t__ lang ; 
 scalar_t__ offset ; 
 int secure ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stream ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 
 char* ua ; 
 char* vlc_http_msg_get_agent (struct vlc_http_msg const*) ; 
 char* vlc_http_msg_get_authority (struct vlc_http_msg const*) ; 
 char* vlc_http_msg_get_header (struct vlc_http_msg const*,char*) ; 
 struct vlc_http_msg* vlc_http_msg_get_initial (int /*<<< orphan*/ *) ; 
 char* vlc_http_msg_get_method (struct vlc_http_msg const*) ; 
 char* vlc_http_msg_get_path (struct vlc_http_msg const*) ; 
 char* vlc_http_msg_get_scheme (struct vlc_http_msg const*) ; 
 int vlc_http_msg_get_time (struct vlc_http_msg const*,char*) ; 

struct vlc_http_msg *vlc_http_mgr_request(struct vlc_http_mgr *mgr, bool https,
                                          const char *host, unsigned port,
                                          const struct vlc_http_msg *req)
{
    const char *str;
    char *end;

    assert(https == secure);
    assert(mgr == NULL);
    assert(!strcmp(host, "www.example.com"));
    assert(port == 8443);

    str = vlc_http_msg_get_method(req);
    assert(!strcmp(str, "GET"));
    str = vlc_http_msg_get_scheme(req);
    assert(!strcmp(str, secure ? "https" : "http"));
    str = vlc_http_msg_get_authority(req);
    assert(!strcmp(str, "www.example.com:8443"));
    str = vlc_http_msg_get_path(req);
    assert(!strcmp(str, "/dir/file.ext?a=b"));
    str = vlc_http_msg_get_agent(req);
    assert(!strcmp(str, ua));
    str = vlc_http_msg_get_header(req, "Referer");
    assert(str == NULL);
    str = vlc_http_msg_get_header(req, "Accept");
    assert(str == NULL || strstr(str, "*/*") != NULL);

    str = vlc_http_msg_get_header(req, "Accept-Language");
    /* This test case does not call setlocale(), so en_US can be assumed. */
    if (lang != 0)
    {
        assert(str != NULL && strncmp(str, "en_US", 5) == 0);
        if (lang > 0)
            lang--;
    }
    else
        assert(str == NULL);

    str = vlc_http_msg_get_header(req, "Range");
    assert(str != NULL && !strncmp(str, "bytes=", 6)
        && strtoul(str + 6, &end, 10) == offset && *end == '-');

    time_t mtime = vlc_http_msg_get_time(req, "If-Unmodified-Since");
    str = vlc_http_msg_get_header(req, "If-Match");

    if (etags)
    {
        if (offset != 0)
            assert(str != NULL && !strcmp(str, "\"foobar42\""));
        else
        if (str != NULL)
            assert(strcmp(str, "*") || strcmp(str, "\"foobar42\""));
    }
    else
    {
        if (offset != 0)
            assert(mtime == 1382386402);
    }

    return vlc_http_msg_get_initial(&stream);
}