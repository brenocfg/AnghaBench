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
struct TYPE_5__ {char const* psz_protocol; char const* psz_username; char const* psz_password; char const* psz_host; unsigned int i_port; char const* psz_path; char const* psz_option; } ;
typedef  TYPE_1__ vlc_url_t ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int exitcode ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_compare (char const*,char const*,char const*) ; 
 int /*<<< orphan*/  vlc_UrlClean (TYPE_1__*) ; 
 int vlc_UrlParse (TYPE_1__*,char const*) ; 
 int vlc_UrlParseFixup (TYPE_1__*,char const*) ; 

__attribute__((used)) static void test_url_parse_internal(const char *in, bool fixup,
                                    const char *protocol,
                                    const char *user, const char *pass,
                                    const char *host, unsigned port,
                                    const char *path, const char *option)
{
    vlc_url_t url;
    int ret = fixup ? vlc_UrlParseFixup(&url, in) : vlc_UrlParse(&url, in);

    /* XXX: only checking that the port-part is parsed correctly, and
     *      equal to 0, is currently not supported due to the below. */
    if (protocol == NULL && user == NULL && pass == NULL && host == NULL
     && port == 0 && path == NULL && option == NULL)
    {
        vlc_UrlClean(&url);

        if (ret != -1)
        {
            fprintf(stderr, "\"%s\" accepted, expected rejection\n", in);
            exit(2);
        }
        return;
    }

    test_compare(in, protocol, url.psz_protocol);
    test_compare(in, user, url.psz_username);
    test_compare(in, pass, url.psz_password);

    if (ret != 0 && errno == ENOSYS)
    {
        test_compare(in, NULL, url.psz_host);
        exitcode = 77;
    }
    else
        test_compare(in, url.psz_host, host);

    if (url.i_port != port)
    {
        fprintf(stderr, "\"%s\" returned %u, expected %u\n", in, url.i_port,
                port);
        exit(2);
    }

    test_compare(in, path, url.psz_path);
    test_compare(in, option, url.psz_option);
    vlc_UrlClean(&url);
}