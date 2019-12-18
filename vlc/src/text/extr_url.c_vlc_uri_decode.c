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
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int) ; 

char *vlc_uri_decode (char *str)
{
    char *in = str, *out = str;
    if (in == NULL)
        return NULL;

    char c;
    while ((c = *(in++)) != '\0')
    {
        if (c == '%')
        {
            char hex[3];

            if (!(hex[0] = *(in++)) || !(hex[1] = *(in++)))
                return NULL;
            hex[2] = '\0';
            *(out++) = strtoul (hex, NULL, 0x10);
        }
        else
            *(out++) = c;
    }
    *out = '\0';
    return str;
}