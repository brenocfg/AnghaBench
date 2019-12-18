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
typedef  int uint8_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int hexdigit (char const) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static ssize_t hexstring (const char *in, uint8_t *out, size_t outlen)
{
    size_t inlen = strlen (in);

    if ((inlen > (2 * outlen)) || (inlen & 1))
        return -1;

    for (size_t i = 0; i < inlen; i += 2)
    {
        int a = hexdigit (in[i]), b = hexdigit (in[i + 1]);
        if ((a == -1) || (b == -1))
            return -1;
        out[i / 2] = (a << 4) | b;
    }
    return inlen / 2;
}