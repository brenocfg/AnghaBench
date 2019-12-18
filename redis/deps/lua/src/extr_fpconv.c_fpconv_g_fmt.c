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
 int FPCONV_G_FMT_BUFSIZE ; 
 char locale_decimal_point ; 
 int /*<<< orphan*/  set_number_format (char*,int) ; 
 int snprintf (char*,int,char*,double) ; 

int fpconv_g_fmt(char *str, double num, int precision)
{
    char buf[FPCONV_G_FMT_BUFSIZE];
    char fmt[6];
    int len;
    char *b;

    set_number_format(fmt, precision);

    /* Pass through when decimal point character is dot. */
    if (locale_decimal_point == '.')
        return snprintf(str, FPCONV_G_FMT_BUFSIZE, fmt, num);

    /* snprintf() to a buffer then translate for other decimal point characters */
    len = snprintf(buf, FPCONV_G_FMT_BUFSIZE, fmt, num);

    /* Copy into target location. Translate decimal point if required */
    b = buf;
    do {
        *str++ = (*b == locale_decimal_point ? '.' : *b);
    } while(*b++);

    return len;
}