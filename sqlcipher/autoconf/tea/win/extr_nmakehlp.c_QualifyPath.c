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
 int /*<<< orphan*/  GetCurrentDirectory (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  PathCanonicalize (char*,char*) ; 
 int /*<<< orphan*/  PathCombine (char*,char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int
QualifyPath(
    const char *szPath)
{
    char szCwd[MAX_PATH + 1];
    char szTmp[MAX_PATH + 1];
    char *p;
    GetCurrentDirectory(MAX_PATH, szCwd);
    while ((p = strchr(szPath, '/')) && *p)
	*p = '\\';
    PathCombine(szTmp, szCwd, szPath);
    PathCanonicalize(szCwd, szTmp);
    printf("%s\n", szCwd);
    return 0;
}