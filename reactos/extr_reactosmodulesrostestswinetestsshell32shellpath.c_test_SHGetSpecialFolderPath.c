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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 char* getFolderName (int) ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 
 scalar_t__ pSHGetSpecialFolderPathA (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_SHGetSpecialFolderPath(BOOL optional, int folder)
{
    char path[MAX_PATH];
    BOOL ret;

    if (!pSHGetSpecialFolderPathA) return;

    ret = pSHGetSpecialFolderPathA(NULL, path, folder, FALSE);
    if (ret && winetest_interactive)
        printf("%s: %s\n", getFolderName(folder), path);
    ok(ret || optional,
     "SHGetSpecialFolderPathA(NULL, path, %s, FALSE) failed\n",
     getFolderName(folder));
}