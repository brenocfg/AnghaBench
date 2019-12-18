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
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strconcat (char const*,char*,int /*<<< orphan*/ *) ; 
 char* g_strdup (char const*) ; 
 char* g_strndup (char const*,int) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static char *
http_fileserver_url (const char *url)
{
    const char *host;
    char *colon;
    char *url_no_port;
    char *ret = NULL;

    /* Just return the url itself if it's invalid. */
    if (strlen(url) <= strlen("http://"))
        return g_strdup(url);

    /* Skip protocol schem. */
    host = url + strlen("http://");

    colon = strrchr (host, ':');
    if (colon) {
        url_no_port = g_strndup(url, colon - url);
        ret = g_strconcat(url_no_port, ":8082", NULL);
        g_free (url_no_port);
    } else {
        ret = g_strconcat(url, ":8082", NULL);
    }

    return ret;
}