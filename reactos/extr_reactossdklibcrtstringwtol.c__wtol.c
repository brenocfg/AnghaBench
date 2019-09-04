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
typedef  int wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  _SPACE ; 
 scalar_t__ iswctype (int const,int /*<<< orphan*/ ) ; 

long
_wtol(const wchar_t *str)
{
    unsigned long RunningTotal = 0;
    char bMinus = 0;

    if (str == NULL)
        return 0;

    while (iswctype(*str, _SPACE) ) {
        str++;
    } /* while */

    if (*str == L'+') {
        str++;
    } else if (*str == L'-') {
        bMinus = 1;
        str++;
    } /* if */

    while (*str >= L'0' && *str <= L'9') {
        RunningTotal = RunningTotal * 10 + *str - L'0';
        str++;
    } /* while */

    return bMinus ? 0-RunningTotal : RunningTotal;
}