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
typedef  int ld2string_mode ;

/* Variables and functions */
#define  LD_STR_AUTO 130 
#define  LD_STR_HEX 129 
#define  LD_STR_HUMAN 128 
 scalar_t__ isinf (long double) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 size_t snprintf (char*,size_t,char*,long double) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

int ld2string(char *buf, size_t len, long double value, ld2string_mode mode) {
    size_t l = 0;

    if (isinf(value)) {
        /* Libc in odd systems (Hi Solaris!) will format infinite in a
         * different way, so better to handle it in an explicit way. */
        if (len < 5) return 0; /* No room. 5 is "-inf\0" */
        if (value > 0) {
            memcpy(buf,"inf",3);
            l = 3;
        } else {
            memcpy(buf,"-inf",4);
            l = 4;
        }
    } else {
        switch (mode) {
        case LD_STR_AUTO:
            l = snprintf(buf,len,"%.17Lg",value);
            if (l+1 > len) return 0; /* No room. */
            break;
        case LD_STR_HEX:
            l = snprintf(buf,len,"%La",value);
            if (l+1 > len) return 0; /* No room. */
            break;
        case LD_STR_HUMAN:
            /* We use 17 digits precision since with 128 bit floats that precision
             * after rounding is able to represent most small decimal numbers in a
             * way that is "non surprising" for the user (that is, most small
             * decimal numbers will be represented in a way that when converted
             * back into a string are exactly the same as what the user typed.) */
            l = snprintf(buf,len,"%.17Lf",value);
            if (l+1 > len) return 0; /* No room. */
            /* Now remove trailing zeroes after the '.' */
            if (strchr(buf,'.') != NULL) {
                char *p = buf+l-1;
                while(*p == '0') {
                    p--;
                    l--;
                }
                if (*p == '.') l--;
            }
            break;
        default: return 0; /* Invalid mode. */
        }
    }
    buf[l] = '\0';
    return l;
}