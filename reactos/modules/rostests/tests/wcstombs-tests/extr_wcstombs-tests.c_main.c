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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_Tests () ; 
 int /*<<< orphan*/  Win32_Tests (int /*<<< orphan*/ *) ; 

int main()
{
    BOOL UsedDefaultChar;

    CRT_Tests();

    /* There are two code pathes in WideCharToMultiByte, one when Flags || DefaultChar || UsedDefaultChar is set and one when it's not.
       Test both here. */
    Win32_Tests(NULL);
    Win32_Tests(&UsedDefaultChar);

    return 0;
}