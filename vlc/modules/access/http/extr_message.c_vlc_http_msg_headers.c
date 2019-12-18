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
 int /*<<< orphan*/  free (char*) ; 
 char* memchr (char const*,char,int) ; 
 int sscanf (char const*,char*,unsigned short*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strndup (char const*,int) ; 
 int /*<<< orphan*/  strspn (char const*,char*) ; 
 char* strstr (char const*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_http_msg_add_header (struct vlc_http_msg*,char*,char*,int,char const*) ; 
 int /*<<< orphan*/  vlc_http_msg_destroy (struct vlc_http_msg*) ; 
 struct vlc_http_msg* vlc_http_resp_create (unsigned short) ; 

struct vlc_http_msg *vlc_http_msg_headers(const char *msg)
{
    struct vlc_http_msg *m;
    unsigned short code;

    if (sscanf(msg, "HTTP/1.%*1u %3hu %*s", &code) == 1)
    {
        m = vlc_http_resp_create(code);
        if (unlikely(m == NULL))
            return NULL;
    }
    else
        return NULL; /* TODO: request support */

    msg = strstr(msg, "\r\n");
    if (msg == NULL)
        goto error;

    while (strcmp(msg + 2, "\r\n"))
    {
        const char *eol = msg;

        do
        {
            eol = strstr(eol + 2, "\r\n");
            if (eol == NULL)
                goto error;
        }   /* Deal with legacy obs-fold (i.e. multi-line header) */
        while (eol[2] == ' ' || eol[2] == '\t');

        msg += 2; /* skip CRLF */

        const char *colon = memchr(msg, ':', eol - msg);
        if (colon == NULL || colon == msg)
            goto error;

        char *name = strndup(msg, colon - msg);
        if (unlikely(name == NULL))
            goto error;

        colon++;
        colon += strspn(colon, " \t");

        if (unlikely(vlc_http_msg_add_header(m, name, "%.*s",
                                             (int)(eol - colon), colon)))
        {
            free(name);
            goto error;
        }
        free(name);
        msg = eol;
    }

    return m;
error:
    vlc_http_msg_destroy(m);
    return NULL;
}