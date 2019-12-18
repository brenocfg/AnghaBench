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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int CSIDL_FLAG_CREATE ; 
 char* FromWide (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SHGFP_TYPE_CURRENT ; 
 scalar_t__ SHGetFolderPathW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 

__attribute__((used)) static char *config_GetShellDir (int csidl)
{
    wchar_t wdir[MAX_PATH];

    if (SHGetFolderPathW (NULL, csidl | CSIDL_FLAG_CREATE,
                          NULL, SHGFP_TYPE_CURRENT, wdir ) == S_OK)
        return FromWide (wdir);
    return NULL;
}