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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ ar_conv_rune_to_utf8 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * gCp437 ; 
 char* malloc (size_t) ; 

char *ar_conv_dos_to_utf8(const char *astr)
{
    char *str, *out;
    const char *in;
    size_t size;

    size = 0;
    for (in = astr; *in; in++) {
        char buf[4];
        size += ar_conv_rune_to_utf8(gCp437[(uint8_t)*in], buf, sizeof(buf));
    }

    if (size == (size_t)-1)
        return NULL;
    str = malloc(size + 1);
    if (!str)
        return NULL;

    for (in = astr, out = str; *in; in++) {
        out += ar_conv_rune_to_utf8(gCp437[(uint8_t)*in], out, str + size - out);
    }
    *out = '\0';

    return str;
}