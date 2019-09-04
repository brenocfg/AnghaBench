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
 int /*<<< orphan*/  CSIDL_APPDATA ; 
 int /*<<< orphan*/  CSIDL_PROFILE ; 
 int /*<<< orphan*/  CSIDL_PROGRAM_FILES ; 
 int /*<<< orphan*/  CSIDL_PROGRAM_FILES_COMMON ; 
 int /*<<< orphan*/  CSIDL_SYSTEM ; 
 int /*<<< orphan*/  CSIDL_WINDOWS ; 
 int /*<<< orphan*/  matchSpecialFolderPathToEnv (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_EnvVars(void)
{
    matchSpecialFolderPathToEnv(CSIDL_PROGRAM_FILES, "ProgramFiles");
    matchSpecialFolderPathToEnv(CSIDL_APPDATA, "APPDATA");
    matchSpecialFolderPathToEnv(CSIDL_PROFILE, "USERPROFILE");
    matchSpecialFolderPathToEnv(CSIDL_WINDOWS, "SystemRoot");
    matchSpecialFolderPathToEnv(CSIDL_WINDOWS, "windir");
    matchSpecialFolderPathToEnv(CSIDL_PROGRAM_FILES_COMMON, "CommonProgramFiles");
    /* this is only set on Wine, but can't hurt to verify it: */
    matchSpecialFolderPathToEnv(CSIDL_SYSTEM, "winsysdir");
}