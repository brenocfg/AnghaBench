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
 int /*<<< orphan*/  GetTempPathA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 char* szTempPath ; 

__attribute__((used)) static const char* tmpdir()
{
    if (szTempPath[0] == '\0')
    {
        GetTempPathA(MAX_PATH, szTempPath);
        lstrcatA(szTempPath, "dbghelp_tst");
    }
    return szTempPath;
}