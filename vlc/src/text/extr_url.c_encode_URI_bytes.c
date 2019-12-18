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
 scalar_t__ isurisafe (unsigned char) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 char* realloc (char*,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 void** urihex ; 

__attribute__((used)) static char *encode_URI_bytes (const char *str, size_t *restrict lenp)
{
    char *buf = malloc (3 * *lenp + 1);
    if (unlikely(buf == NULL))
        return NULL;

    char *out = buf;
    for (size_t i = 0; i < *lenp; i++)
    {
        unsigned char c = str[i];

        if (isurisafe (c))
            *(out++) = c;
        /* This is URI encoding, not HTTP forms:
         * Space is encoded as '%20', not '+'. */
        else
        {
            *(out++) = '%';
            *(out++) = urihex[c >> 4];
            *(out++) = urihex[c & 0xf];
        }
    }

    *lenp = out - buf;
    out = realloc (buf, *lenp + 1);
    return likely(out != NULL) ? out : buf;
}