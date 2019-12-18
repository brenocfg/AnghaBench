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
 size_t strspn (char const*,char*) ; 
 size_t vlc_http_comment_length (char const*) ; 
 int /*<<< orphan*/  vlc_http_istoken (char const) ; 
 size_t vlc_http_token_length (char const*) ; 

__attribute__((used)) static bool vlc_http_is_agent(const char *s)
{   /* IETF RFC7231 §5.5.3 and §7.4.2 */
    if (!vlc_http_istoken(*s))
        return false;

    for (;;)
    {
        size_t l = vlc_http_token_length(s);
        if (l != 0) /* product */
        {
            if (s[l] == '/') /* product version */
            {
                s += l + 1;
                l = vlc_http_token_length(s);
            }
        }
        else
            l = vlc_http_comment_length(s);

        if (l == 0)
            break;

        s += l;

        if (*s == '\0')
            return true;

        l = strspn(s, "\t "); /* RWS */

        if (l == 0)
            break;

        s += l;
    }

    return false;
}