#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ptr; } ;
typedef  TYPE_1__ json_parse_t ;

/* Variables and functions */
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static int json_is_invalid_number(json_parse_t *json)
{
    const char *p = json->ptr;

    /* Reject numbers starting with + */
    if (*p == '+')
        return 1;

    /* Skip minus sign if it exists */
    if (*p == '-')
        p++;

    /* Reject numbers starting with 0x, or leading zeros */
    if (*p == '0') {
        int ch2 = *(p + 1);

        if ((ch2 | 0x20) == 'x' ||          /* Hex */
            ('0' <= ch2 && ch2 <= '9'))     /* Leading zero */
            return 1;

        return 0;
    } else if (*p <= '9') {
        return 0;                           /* Ordinary number */
    }

    /* Reject inf/nan */
    if (!strncasecmp(p, "inf", 3))
        return 1;
    if (!strncasecmp(p, "nan", 3))
        return 1;

    /* Pass all other numbers which may still be invalid, but
     * strtod() will catch them. */
    return 0;
}