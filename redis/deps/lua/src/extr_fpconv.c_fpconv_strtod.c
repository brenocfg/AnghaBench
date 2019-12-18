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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char locale_decimal_point ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 double strtod (char const*,char**) ; 
 int strtod_buffer_size (char const*) ; 

double fpconv_strtod(const char *nptr, char **endptr)
{
    char localbuf[FPCONV_G_FMT_BUFSIZE];
    char *buf, *endbuf, *dp;
    int buflen;
    double value;

    /* System strtod() is fine when decimal point is '.' */
    if (locale_decimal_point == '.')
        return strtod(nptr, endptr);

    buflen = strtod_buffer_size(nptr);
    if (!buflen) {
        /* No valid characters found, standard strtod() return */
        *endptr = (char *)nptr;
        return 0;
    }

    /* Duplicate number into buffer */
    if (buflen >= FPCONV_G_FMT_BUFSIZE) {
        /* Handle unusually large numbers */
        buf = malloc(buflen + 1);
        if (!buf) {
            fprintf(stderr, "Out of memory");
            abort();
        }
    } else {
        /* This is the common case.. */
        buf = localbuf;
    }
    memcpy(buf, nptr, buflen);
    buf[buflen] = 0;

    /* Update decimal point character if found */
    dp = strchr(buf, '.');
    if (dp)
        *dp = locale_decimal_point;

    value = strtod(buf, &endbuf);
    *endptr = (char *)&nptr[endbuf - buf];
    if (buflen >= FPCONV_G_FMT_BUFSIZE)
        free(buf);

    return value;
}