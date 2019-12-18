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

/* Variables and functions */
 int asprintf (char**,char*,char const*,int,char const*,char*,char*,char*) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* httpd_ReasonFromCode (int) ; 
 char* vlc_xml_encode (char const*) ; 

__attribute__((used)) static size_t httpd_HtmlError (char **body, int code, const char *url)
{
    const char *errname = httpd_ReasonFromCode (code);
    assert (errname);

    char *url_Encoded = vlc_xml_encode (url ? url : "");

    int res = asprintf (body,
        "<?xml version=\"1.0\" encoding=\"ascii\" ?>\n"
        "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\""
        " \"http://www.w3.org/TR/xhtml10/DTD/xhtml10strict.dtd\">\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "<title>%s</title>\n"
        "</head>\n"
        "<body>\n"
        "<h1>%d %s%s%s%s</h1>\n"
        "<hr />\n"
        "<a href=\"http://www.videolan.org\">VideoLAN</a>\n"
        "</body>\n"
        "</html>\n", errname, code, errname,
        (url_Encoded ? " (" : ""), (url_Encoded ? url_Encoded : ""), (url_Encoded ? ")" : ""));

    free (url_Encoded);

    if (res == -1) {
        *body = NULL;
        return 0;
    }

    return (size_t)res;
}