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
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * hex2bin ; 

__attribute__((used)) static BOOL validate_indices(LPCWSTR s, int min, int max)
{
    int i;

    for (i = min; i <= max; i++)
    {
        if (!s[i])
            return FALSE;

        if (i == 0)
        {
            if (s[i] != '{')
                return FALSE;
        }
        else if (i == 9 || i == 14 || i == 19 || i == 24)
        {
            if (s[i] != '-')
                return FALSE;
        }
        else if (i == 37)
        {
            if (s[i] != '}')
                return FALSE;
        }
        else
        {
            if (s[i] > 'f' || (!hex2bin[s[i]] && s[i] != '0'))
                return FALSE;
        }
    }

    return TRUE;
}