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
 int /*<<< orphan*/  CSIDL_COMMON_PROGRAMS ; 
 int /*<<< orphan*/  CSIDL_PROGRAMS ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ProgramsDir ; 
 int /*<<< orphan*/  SHGetSpecialFolderPathA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ use_common () ; 

__attribute__((used)) static void init_strings(void)
{
    char commonprograms[MAX_PATH];
    char programs[MAX_PATH];

    SHGetSpecialFolderPathA(NULL, programs, CSIDL_PROGRAMS, FALSE);
    SHGetSpecialFolderPathA(NULL, commonprograms, CSIDL_COMMON_PROGRAMS, FALSE);

    /* ProgramsDir on Vista+ is always the users one (CSIDL_PROGRAMS). Before Vista
     * it depends on whether the user is an administrator (CSIDL_COMMON_PROGRAMS) or
     * not (CSIDL_PROGRAMS).
     */
    if (use_common())
        lstrcpyA(ProgramsDir, commonprograms);
    else
        lstrcpyA(ProgramsDir, programs);
}