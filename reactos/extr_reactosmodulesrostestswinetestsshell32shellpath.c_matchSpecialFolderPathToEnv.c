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
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 char* getenv (char const*) ; 
 int /*<<< orphan*/  lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,char const*,char const*,char*,char*) ; 
 scalar_t__ pSHGetSpecialFolderPathA (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void matchSpecialFolderPathToEnv(int folder, const char *envVar)
{
    char path[MAX_PATH];

    if (!pSHGetSpecialFolderPathA) return;

    if (pSHGetSpecialFolderPathA(NULL, path, folder, FALSE))
    {
        char *envVal = getenv(envVar);

        ok(!envVal || !lstrcmpiA(envVal, path),
         "%%%s%% does not match SHGetSpecialFolderPath:\n"
         "%%%s%% is %s\nSHGetSpecialFolderPath returns %s\n",
         envVar, envVar, envVal, path);
    }
}