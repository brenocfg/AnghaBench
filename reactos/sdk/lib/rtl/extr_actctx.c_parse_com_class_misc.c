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
struct TYPE_3__ {char* ptr; int len; } ;
typedef  TYPE_1__ xmlstr_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  get_olemisc_value (char const*,int) ; 

__attribute__((used)) static DWORD parse_com_class_misc(const xmlstr_t *value)
{
    const WCHAR *str = value->ptr, *start;
    DWORD flags = 0;
    int i = 0;

    /* it's comma separated list of flags */
    while (i < value->len)
    {
        start = str;
        while (*str != ',' && (i++ < value->len)) str++;

        flags |= get_olemisc_value(start, str-start);

        /* skip separator */
        str++;
        i++;
    }

    return flags;
}