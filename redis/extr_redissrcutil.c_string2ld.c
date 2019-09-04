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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 long double HUGE_VAL ; 
 int MAX_LONG_DOUBLE_CHARS ; 
 scalar_t__ errno ; 
 scalar_t__ isnan (long double) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 long double strtold (char*,char**) ; 

int string2ld(const char *s, size_t slen, long double *dp) {
    char buf[MAX_LONG_DOUBLE_CHARS];
    long double value;
    char *eptr;

    if (slen >= sizeof(buf)) return 0;
    memcpy(buf,s,slen);
    buf[slen] = '\0';

    errno = 0;
    value = strtold(buf, &eptr);
    if (isspace(buf[0]) || eptr[0] != '\0' ||
        (errno == ERANGE &&
            (value == HUGE_VAL || value == -HUGE_VAL || value == 0)) ||
        errno == EINVAL ||
        isnan(value))
        return 0;

    if (dp) *dp = value;
    return 1;
}