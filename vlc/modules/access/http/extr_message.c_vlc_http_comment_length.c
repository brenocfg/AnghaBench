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
 int /*<<< orphan*/  vlc_http_isctext (unsigned char) ; 

__attribute__((used)) static size_t vlc_http_comment_length(const char *str)
{   /* IETF RFC7230 §3.2.6 */
    if (*str != '(')
        return 0;

    size_t i = 1;

    for (size_t nested = 1; nested > 0; i++)
    {
        unsigned char c = str[i];

        if (c == ')')
            nested--;
        else
        if (c == '(') /* Nested comment */
            nested++;
        else
        if (c == '\\') /* Quoted pair */
        {
            i++;
            if (str[i] < 32)
                return 0;
        }
        else
        if (!vlc_http_isctext(c))
            return 0;
    }
    return i;
}