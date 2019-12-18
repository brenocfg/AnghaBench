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

__attribute__((used)) static size_t vlc_http_quoted_length(const char *str)
{
    size_t i = 0;
    unsigned char c;

    if (str[i++] != '"')
        return 0;

    do
    {
        c = str[i++];

        if (c == '\0')
            return 0;

        if (c == '\\') /* Quoted pair */
        {
            unsigned char q = str[i++];
            if (q < 32 && q != '\t')
                return 0;
        }
    }
    while (c != '"');

    return i;
}