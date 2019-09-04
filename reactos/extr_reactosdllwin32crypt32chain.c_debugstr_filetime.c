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
typedef  int /*<<< orphan*/  LPFILETIME ;
typedef  char* LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  filetime_to_str (int /*<<< orphan*/ ) ; 
 char* wine_dbg_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPCSTR debugstr_filetime(LPFILETIME pTime)
{
    if (!pTime)
        return "(nil)";
    return wine_dbg_sprintf("%p (%s)", pTime, filetime_to_str(pTime));
}