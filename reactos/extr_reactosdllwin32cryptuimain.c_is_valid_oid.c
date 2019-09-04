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
typedef  char* LPCSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  isdigit (char const) ; 

__attribute__((used)) static BOOL is_valid_oid(LPCSTR oid)
{
    BOOL ret;

    if (oid[0] != '0' && oid[0] != '1' && oid[0] != '2')
        ret = FALSE;
    else if (oid[1] != '.')
        ret = FALSE;
    else if (!oid[2])
        ret = FALSE;
    else
    {
        const char *ptr;
        BOOL expectNum = TRUE;

        for (ptr = oid + 2, ret = TRUE; ret && *ptr; ptr++)
        {
            if (expectNum)
            {
                if (!isdigit(*ptr))
                    ret = FALSE;
                else if (*(ptr + 1) == '.')
                    expectNum = FALSE;
            }
            else
            {
                if (*ptr != '.')
                    ret = FALSE;
                else if (!(*(ptr + 1)))
                    ret = FALSE;
                else
                    expectNum = TRUE;
            }
        }
    }
    return ret;
}